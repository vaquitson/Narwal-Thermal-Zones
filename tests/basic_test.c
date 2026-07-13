#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "narwal_thermal_zones.h"

int print_thermal_zones_info()
{
  NarwalThermalZone tz_p = {0};
  DIR *dp;
  char *type;
  float temp;

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

    temp = narwal_thermal_zones_get_temp(&tz_p); 
    printf("path: %s\n", tz_p.path);
    printf("type: %s\n", type);
    printf("temp: %f\n", temp);
    printf("\n");
  }
  return 0;
}
  //narwal_thermal_zones_get_next(dp, &tz_p); 



int main(void){
  print_thermal_zones_info();
  return 0;
}
