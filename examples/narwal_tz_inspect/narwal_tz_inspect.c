#include <stdio.h>
#include <string.h>

#include "narwal_thermal_zones.h"

int print_thermal_zones_info()
{
  NarwalThermalZone tz_p = {0};
  char *type;

  while (narwal_thermal_zones_fill_next(&tz_p) == NARWAL_THERMAL_ZONE_SUCESS){
    type = narwal_thermal_zones_get_type(&tz_p);
    if (type == NULL){
      printf("error: %s\n", strerror(tz_p.error));
      return -1;
    }

    printf("path: %s\n", tz_p.path);
    printf("type: %s\n", type);
    printf("\n");
  }

  return 0;
}


int main(int argc, char *argv[]){
  if (argc > 1){
    if (strcmp(argv[1], "-t") == 0){
      print_thermal_zones_info(); 
    }
    goto print_help;
  }
  goto print_help;

print_help:
  printf("Provide one of the following options\n-t: See the types of all the thermal zones avilable in the system\n"); 
  
  return 0;
}
