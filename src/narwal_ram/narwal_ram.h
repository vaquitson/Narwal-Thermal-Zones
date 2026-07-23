#ifndef NARWAL_RAM_C
#define NARWAL_RAM_C

#define NARWAL_RAM_MEMINFO_PATH "/proc/meminfo"
#define NARWAL_RAM_ENTRY_VALUE_MAX 15

long int narwal_ram_size(void);

#define NARWAL_READ_SIZE 250
#define NARWAL_RAM_OPEN_ERR       -1
#define NARWAL_RAM_READ_ERR       -2
#define NARWAL_RAM_ARGUMENT_ERR   -3
#define NARWAL_RAM_TO_LARGE_ENTRY -4

#endif
