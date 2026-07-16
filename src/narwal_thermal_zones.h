#ifndef NARWAL_THERMAL_ZONE_H
#define NARWAL_THERMAL_ZONE_H

#include <dirent.h>
#include <stddef.h>


// configs
#define NARWAL_THERMAL_ZONES_CONFIG_H

#define NARWAL_THERMAL_ZONE_PATH_MAX 100
#define NARWAL_THERMAL_ZONE_THERMAL_DIR "/sys/class/thermal/"

#define NARWAL_THERMAL_ZONE_TYPE_MAX 20
#define NARWAL_THERMAL_ZONE_TEMP_MAX 6
#define NARWAL_THERMAL_ZONE_TEMPERATURE_CELCIUS
// end configs



typedef struct  {
  char path[NARWAL_THERMAL_ZONE_PATH_MAX];
  size_t path_len;
  char type[NARWAL_THERMAL_ZONE_TYPE_MAX]; 
  size_t type_len;
  int error;
} NarwalThermalZone;


int narwal_thermal_zones_get_next(NarwalThermalZone *tz_p);
char *narwal_thermal_zones_get_type(NarwalThermalZone *tz_p);
float narwal_thermal_zones_get_temp(NarwalThermalZone *tz_p);

#endif
