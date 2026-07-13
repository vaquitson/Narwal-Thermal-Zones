#ifndef NARWAL_THERMAL_ZONE_H
#define NARWAL_THERMAL_ZONE_H

#include <dirent.h>
#include "narwal_thermal_zones_config.h"

typedef struct  {
  char path[NARWAL_THERMAL_ZONE_PATH_MAX];
  size_t path_len;
  int type; 
} NarwalThermalZone;


int narwal_thermal_zones_get_next(DIR *dp, NarwalThermalZone *tzp);
int narwal_thermal_zones_get_type(NarwalThermalZone *tz_p);

#endif
