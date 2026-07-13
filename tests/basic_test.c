#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "narwal_thermal_zones.h"

int print_all_thermal_zones_types()
{
  NarwalThermalZone tz_p = {0};
  DIR *dp;
  int rc = 0;

  if ((dp = opendir("/sys/class/thermal/")) == NULL){
    printf("Error\n");
    return -1;
  }

  while (narwal_thermal_zones_get_next(dp, &tz_p) == 0){
    rc = narwal_thermal_zones_get_type(&tz_p);
    if (rc != 0){
      printf("error: %s\n", strerror(rc));
      return -1;
    }
  }

  //narwal_thermal_zones_get_next(dp, &tz_p); 
}


int main(void){
  print_all_thermal_zones_types();
  return 0;
}
