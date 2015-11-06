#include <stdint.h>

struct module {
    uint32_t type;
    void(*init)();
};

struct module_collection {
    uint32_t magic;
    uint32_t version_major;
    uint32_t version_minor;
    uint32_t num_modules;
    uint32_t checksum;

    struct module modules[1];
};
