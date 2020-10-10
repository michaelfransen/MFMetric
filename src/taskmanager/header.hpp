//This is the place to declare every single function
//and global variable that is going to be reused between cpp files.


//We are going to use the TaskScheduler, but only the declarations part.
//Remember to put customization macros before the #include:
#define _TASK_SLEEP_ON_IDLE_RUN
#include <TaskSchedulerDeclarations.h>

//Let the runner object be a global, single instance shared between object files.
extern Scheduler taskManager;