#include <stddef.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 
#include "narwal_ram.h"


int meminfo_fd = -1;


long int priv_narwal_ram_parse_line(char *str){
  char buf[NARWAL_RAM_ENTRY_VALUE_MAX] = {0};
  size_t i = 0;

  while (*str != '\0' && *str != '\n'){
    if (i > NARWAL_RAM_ENTRY_VALUE_MAX-1){
      return NARWAL_RAM_TO_LARGE_ENTRY;
    }

    if (isdigit((unsigned char)*str)){
      buf[i] = *str;
      i++;
    }
    str++; 
  }
  buf[i] = '\0';

  return strtol(buf, NULL, 10);
}


long int priv_narwal_ram_get_entry(char *str, char *key){
  char *entry_p;
  
  if (str == NULL || key == NULL){
    return NARWAL_READ_SIZE;
  }

  entry_p = strstr(str, key);
  if (entry_p == NULL)
    // key does not exist
    return NARWAL_RAM_ARGUMENT_ERR; 

  //printf("%s\n", entry_p);
  return priv_narwal_ram_parse_line(entry_p);
}


long int narwal_ram_size(void){
  static long int ram_size = 0;
  
  if (ram_size == 0){
    long int rc;
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

    ram_size = priv_narwal_ram_get_entry(buf, "MemTotal");
    if (ram_size < 0){
      rc = ram_size;
      ram_size = 0;
      return rc;
    } 
  }
  return ram_size;
}
