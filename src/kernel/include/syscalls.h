#ifndef _SYSCALLS_H_INCLUDED
#define _SYSCALLS_H_INCLUDED

enum class SyscallGroup {
    ProcessManagement   = 1,
};

enum class Syscalls {
    Sleep = 1,
    Fork = 2,
};

static inline uint32_t make_syscall_code(SyscallGroup group, Syscalls syscall) {
    uint32_t ret = static_cast<uint32_t>(group) << 16 | static_cast<uint32_t>(syscall);
}

#endif
