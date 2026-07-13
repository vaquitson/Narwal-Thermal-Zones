#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "narwal_thermal_zones.h"

int narwal_thermal_zones_get_next(DIR *d_p, NarwalThermalZone *tz_p)
{
  struct dirent *dir_p = NULL;
  size_t path_len = 0;

  memset(tz_p, 0, sizeof(NarwalThermalZone));

  strncpy(tz_p->path, NARWAL_THERMAL_ZONE_THERMAL_DIR, NARWAL_THERMAL_ZONE_PATH_MAX);
  path_len = strlen(NARWAL_THERMAL_ZONE_THERMAL_DIR);

  while ((dir_p = readdir(d_p)) != NULL){
    if (strstr(dir_p->d_name, "thermal_zone") != NULL){

      strncat(tz_p->path, dir_p->d_name, NARWAL_THERMAL_ZONE_PATH_MAX - path_len); 
      path_len += strnlen(dir_p->d_name, NARWAL_THERMAL_ZONE_PATH_MAX);

      tz_p->path_len = path_len;
      return 0;
    }
  }
  return 1;
}



char *narwal_thermal_zones_get_type(NarwalThermalZone *tz_p)
{ 
  if (tz_p->type_len == 0){
    int fd;
    ssize_t read_s;
    char path[NARWAL_THERMAL_ZONE_PATH_MAX] = {0};

    strncpy(path, tz_p->path, tz_p->path_len);
    strcat(path, "/type");

    fd = open(path, O_RDONLY);
    if (fd < 0){
      tz_p->error = errno;
      return NULL;
    }

    read_s = read(fd, tz_p->type, NARWAL_THERMAL_ZONE_TYPE_MAX); 
    if (read_s < 0){
      tz_p->error = errno;
      return NULL;
    }
    tz_p->type[read_s] = '\0';
    tz_p->type_len = read_s - 1;
    close(fd);
  }

  return tz_p->type;
}


int narwal_thermal_zones_get_temp(NarwalThermalZone *tz_p)
{

  

}
