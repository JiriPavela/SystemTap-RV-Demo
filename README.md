SystemTap Runtime Verification Demo
===================================

Includes 2 example problems: 
 - Resources cleanup checking
 - Task priority checking (TODO)


Resources cleanup checking
--------------------------

Consists of corresponding pairs of (sources/simple_resourcesX.c, cleanup_checkX.stp)
and 2 hello world examples.

### The checked properties:
1. Each `prepare` function call should have a corresponding `cleanup` call before the process ends.
2. Opened files should be properly closed before the process ends.

### Steps
* hello_world.stp: simple hello world introduction.
* process_hello.stp: shows binding to specific processes and some built-in SystemTap functions.
1. First attempt at solving the 1. property (contains errors).
2. Attempted fix of the `simple_resources` program.
 * The check actually passes although the program is not satisfying the 1. property.
3. Shows usage of `target variables`, i.e., accessing the local variables of a function.
4. Shows usage of `associative arrays` to implement a monitor and precisely locate the errors.
5. Second attempted fix of the program. Should not produce errors when supplied two valid files.
6. Third attempted fix. The 1. property should correctly hold now.
7. Shows usage of `syscalls` probes to evaluate the 2. property.
8. Fix of the 2. property.
 * However, the properties do not always hold, e.g., unhandled signal still breaks it.
 * Feel free to fix it!

### Used commands
* Correct files: `sudo stap cleanup_checkX.stp -c "./simple_resourcesX input/file1 input/file2"`
* One non-existent file: `sudo stap cleanup_checkX.stp -c "./simple_resourcesX input/file1 input/file3"`

### Additional commands
* Show how to list probe locations: e.g., `stap -l 'process("simple_resources").function("*")'`.
* Show how to also list target variables: e.g, `stap -L 'process("simple_resources").function("*")'`
* Show how to list available syscalls and their variables: e.g., `stap -L 'syscall.*'` 


Task priority checking
----------------------

Simple C++ skeleton of a Mars rover that has limited resources (antenna, communicator, camera, etc.,)
and various tasks that request the resources with different priorities. Show that proper instrumentation
(and monitor) can check that the resources are allocated according to the priorities (or not)!

### The checked properties:
1. A Task with higher priority should always get the requested resource from any other Task with lower
priority. Task with lower or equal priority than the Task currently assigned to a Resource should wait 
until the resource is made available. 

### Steps
1. resource_allocation.stp: run on `resource_allocation`.
* Note the USDT probe `AVAILABLE_FALSE`.
* Also note the different ways of specifying C++ function names.

### Used commands
* To stdout: `sudo stap resource_allocation.stp -c "./resource_allocation"`
* To output file: `sudo stap resource_allocation.stp -c "./resource_allocation" -o output.log`

### Additional commands
* Show how to list USDT locations: e.g., `stap -L 'process("resource_allocation").mark("*")'`.


Additional (and used) resources
-------------------------------
* https://sourceware.org/systemtap/SystemTap_Beginners_Guide/index.html
* https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/pdf/systemtap_beginners_guide/Red_Hat_Enterprise_Linux-7-SystemTap_Beginners_Guide-en-US.pdf
* https://sourceware.org/systemtap/examples/
* The second example is inspired by: https://www.researchgate.net/publication/303161021_A_Tutorial_on_Runtime_Verification