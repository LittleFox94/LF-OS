#include <stdint.h>
#include <lf_os.h>
 
#define STACK_CHK_GUARD 0xe2dee396
 
uint32_t __stack_chk_guard = STACK_CHK_GUARD;
 
extern "C" {
    __attribute__((noreturn))
    void __stack_chk_fail(void)
    {
        crash("Stack smashing detected");
    }
}
