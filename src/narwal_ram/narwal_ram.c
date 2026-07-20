#include <stddef.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "narwal_ram.h"


int meminfo_fd = -1;


int narwal_ram_usage(void){
  int ram_usage;
  char buf[NARWAL_READ_SIZE];
  ssize_t data_read;

  if (meminfo_fd < 0) {
    meminfo_fd = open(NARWAL_RAM_MEMINFO_PATH, O_RDONLY);
    if (meminfo_fd < 0) {
      return NARWAL_RAM_OPEN_ERR; 
    }
  }
  
  data_read = read(meminfo_fd, buf, NARWAL_READ_SIZE-1);
  if (data_read < 0)
    return NARWAL_RAM_READ_ERR;

  buf[data_read] = '\0'; 

  printf("Ram data: \n%s\n\n", buf);

  return 0; 
}
