#include <scheduler.h>
#include <lf_os.h>
#include <string.h>

Scheduler::Task* Scheduler::_firstTask = 0;
Scheduler::Task* Scheduler::_lastTask = 0;
Scheduler::Task* Scheduler::_currentTask = 0;
pid_t Scheduler::_lastPid = 0;
bool Scheduler::_initialized = false;

void Scheduler::idleTask() {
    while(true) {
        __asm__ __volatile__("hlt");
    }
}

void Scheduler::initialize() {
    Task* idleTask = createNewTask(Scheduler::idleTask, true);

    memcpy(idleTask->name, "idle", 4);

    _firstTask = idleTask;
    _lastTask = idleTask;
    _lastTask->next = _firstTask;
    _firstTask->prev = _lastTask;

    _initialized = true;
}

void Scheduler::sleep(uint32_t numInterrupts) {
    _currentTask->sleeping_counter = numInterrupts;
}

pid_t Scheduler::addTask(void(*task)(), bool kernel) {
    Task* newTask = createNewTask(task, kernel);
    insertTask(newTask);

    return newTask->pid;
}

struct cpu_state* Scheduler::nextTask(struct cpu_state* cpu) {
    if(!_initialized) {
        return cpu;
    }

    Task* current = _firstTask;
    do {
        // schlafende Prozesse haben wieder einen Interrupt länger geschlafen
        if(current->sleeping_counter) {
            current->sleeping_counter--;
        }

        current = current->next;
    } while(current != _firstTask);

    struct cpu_state* state = (struct cpu_state*)((char*)_currentTask + 4096 - sizeof(Task));

    if(_currentTask != 0) {
        // manche Tasks sind gleicher als andere
        _currentTask->priority_counter--;
        if(_currentTask->priority_counter) {
            *state = _currentTask->cpu;
            return state;
        }
  
        // wenn der aktuelle Task mal wieder dran kommt bleibt er so lange
        // aktiv wie seine Priorität sagt
        _currentTask->priority_counter = _currentTask->priority;

        memcpy((char*)&_currentTask->cpu, (char*)cpu, sizeof(struct cpu_state));
    }

    // neuen Task finden der aktiv ist und nicht schläft
    Task* newCurrent = _currentTask == 0 ? _firstTask : _currentTask->next;
    while(!newCurrent->active || newCurrent->sleeping_counter) {
        newCurrent = newCurrent->next;
    }

    _currentTask = newCurrent;

    *state = _currentTask->cpu;

    return state;
}

Scheduler::Task* Scheduler::getTaskForPid(pid_t pid) {
    Task* current = _firstTask;
    while(current->pid != pid) {
        current = current->next;
    }

    if(current->pid == pid) {
        return current;
    }
    
    return 0;
}

Scheduler::Task* Scheduler::createNewTask(void(*task)(), bool kernel) {
    Task* newTask = (Task*)pmm_alloc();
    memset((char*)newTask, 0, PAGESIZE);

    newTask->priority = 1;
    newTask->priority_counter = 1;

    memcpy(newTask->name, "[no name]", 9);
    newTask->pid = _lastPid++;

    newTask->active = true;

    newTask->cpu.esp = (uint32_t)pmm_alloc() + 4096;
    newTask->cpu.eip = (uint32_t)task;
    newTask->cpu.cs  = kernel ? 0x08 : (0x18 | 0x03);
    newTask->cpu.ss  = kernel ? 0x10 : (0x20 | 0x03);
    newTask->cpu.eflags = 0x202;

    return newTask;
}

void Scheduler::insertTask(Task* newTask) {
    Task* previous = _firstTask->prev;
    
    newTask->prev = previous;
    newTask->next = _firstTask;

    previous->next = newTask;
    _firstTask->prev = newTask;
}

void Scheduler::fork() {
    Task* newTask = (Task*)pmm_alloc();
    memcpy((char*)newTask, (char*)_currentTask, sizeof(Task));

    newTask->pid = _lastPid++;

    insertTask(newTask);
}
