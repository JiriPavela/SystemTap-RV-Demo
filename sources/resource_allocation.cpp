#include <string>
#include <vector>
#include <iostream>
#include <sys/sdt.h>


// Resources used by the Rover
class Resource {
public:
    Resource(int id, std::string name);

    void allocate(int task_id);
    void yield();

    int id;
    std::string name;
    int allocated_task;
};

Resource::Resource(int id, std::string name)
    : id(id), name(name), allocated_task(-1) {}

void Resource::allocate(int task_id) {
    allocated_task = task_id;
}

void Resource::yield() {
    allocated_task = -1;
}


// Tasks assigned to the Rover
class Task {
public:
    Task(int id, int priority, int resource);

    void allocate_res();
    void yield_res();

    int id;
    int priority;
    int required_resource;
    bool has_resource;
};

Task::Task(int id, int priority, int resource)
    : id(id), priority(priority), required_resource(resource), has_resource(false) {}

void Task::allocate_res() {
    has_resource = true;
}

void Task::yield_res() {
    has_resource = false;
}



// The Rover itself
class Rover {
public:
    Rover();

    void new_task(Task t);
private:
    std::vector<Resource> resources;
    std::vector<Task> tasks;

    void update_tasks(Task &t);
    void update_res(Task t);

};

Rover::Rover() {
    resources.push_back(Resource(0, "Camera"));
    resources.push_back(Resource(1, "Antenna"));
    resources.push_back(Resource(2, "Communicator"));
    resources.push_back(Resource(3, "Robotic Arm"));
}

void Rover::new_task(Task t) {
    update_tasks(t);
    tasks.push_back(t);
}

void Rover::update_tasks(Task &t) {
    bool available = true;
    for (auto task: tasks) {
        if (task.required_resource == t.required_resource && task.has_resource) {
            if (t.priority >= task.priority) {
                task.yield_res();
            } else {
                STAP_PROBE(PROVIDER_NAME, AVAILABLE_FALSE);
                available = false;
            }
        }
    }
    if (available) {
        t.allocate_res();
        update_res(t);
    }
}

void Rover::update_res(Task t) {
    for (auto &res: resources) {
        if (t.required_resource == res.id) {
            res.yield();
            res.allocate(t.id);
            break;
        }
    }
}


int main() {
    Rover rover;
    rover.new_task(Task(0, 4, 0));
    rover.new_task(Task(1, 6, 1));
    rover.new_task(Task(2, 3, 2));
    rover.new_task(Task(3, 1, 1));
    rover.new_task(Task(4, 6, 0));
    rover.new_task(Task(5, 2, 0));
    rover.new_task(Task(6, 6, 0));

    return 0;
}