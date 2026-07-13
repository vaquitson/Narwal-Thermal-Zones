#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "narwal_thermal_zones.h"

int print_all_thermal_zones_types()
{
  NarwalThermalZone tz_p = {0};
  DIR *dp;
  char *type;

  if ((dp = opendir("/sys/class/thermal/")) == NULL){
    printf("Error\n");
    return -1;
  }

  while (narwal_thermal_zones_get_next(dp, &tz_p) == 0){
    type = narwal_thermal_zones_get_type(&tz_p);
    if (type == NULL){
      printf("error: %s\n", strerror(tz_p.error));
      return -1;
    }
    printf("path: %s\n", tz_p.path);
    printf("type: %s\n", type);
  }
  return 0;
}
  //narwal_thermal_zones_get_next(dp, &tz_p); 


int main(void){
  print_all_thermal_zones_types();
  return 0;
}
