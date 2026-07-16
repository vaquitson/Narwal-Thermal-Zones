#include <dirent.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "narwal_thermal_zones.h"



/*
 * Returns the length of a null-terminated string, up to a specified limit.
 *
 * This function examines at most `max_len` characters from `str`. If a null
 * terminator is found, its position is returned. Otherwise, `max_len` is
 * returned.
 *
 * This function is provided as a C99-compatible replacement for `strnlen()`,
 * which is not part of the C99 standard.
 *
 * @param str      Pointer to the string to examine.
 * @param max_len  Maximum number of characters to examine.
 *
 * @return The number of characters before the null terminator, excluding the
 *         null terminator itself, or `max_len` if no null terminator is found.
*/
size_t priv_narwal_thermal_zones_strnlen(const char *str, size_t max_len)
{
  size_t length = 0;

  while (length < max_len && str[length] != '\0'){
    ++length;
  }

  return length;
}

/*
 * Replaces the first newline character in a string.
 *
 * This function searches `str` for the first newline character (`'\n'`) and
 * replaces it with the character specified by `replacement`.
 *
 * @param str          Pointer to the null-terminated string to modify.
 * @param replacement  Character used to replace the first newline.
 *
 * @return The index of the replaced newline character. If no newline is found,
 *         the length of the string is returned.
*/
size_t priv_narwal_thermal_zones_strip_line_jump(char *ptr, char replacement)
{
  size_t i = 0; 
  while (ptr[i] != '\0'){
    if (ptr[i] == '\n') {
      ptr[i] = replacement;
      return i;
  }
    i++;
  }
  return i;
}

/*
 * Retrieves the next thermal zone available on the system.
 *
 * On each successful call, this function clears the structure pointed to by
 * `tz_p` and fills it with information about the next available thermal zone.
 * Successive calls iterate through all thermal zones detected on the system.
 *
 * @param tz_p  Pointer to the structure in which the thermal zone information
 *              will be stored.
 *
 * @return A status code indicating whether a thermal zone was retrieved,
 *         whether the iteration has finished, or whether an error occurred.
*/
int narwal_thermal_zones_get_next(NarwalThermalZone *tz_p)
{
  static DIR *d_p = NULL;

  struct dirent *dir_p = NULL;
  size_t path_len = 0;

  memset(tz_p, 0, sizeof(NarwalThermalZone));

  if (d_p == NULL){
    d_p = opendir(NARWAL_THERMAL_ZONE_THERMAL_DIR);
    if (d_p == NULL){
      tz_p->error = errno; 
      return errno;
    }
  }

  strncpy(tz_p->path, NARWAL_THERMAL_ZONE_THERMAL_DIR, NARWAL_THERMAL_ZONE_PATH_MAX);
  path_len = strlen(NARWAL_THERMAL_ZONE_THERMAL_DIR);

  while ((dir_p = readdir(d_p)) != NULL){
    if (strstr(dir_p->d_name, "thermal_zone") != NULL){

      strncat(tz_p->path, dir_p->d_name, NARWAL_THERMAL_ZONE_PATH_MAX - path_len); 
      path_len += priv_narwal_thermal_zones_strnlen(dir_p->d_name, NARWAL_THERMAL_ZONE_PATH_MAX);

      tz_p->path_len = path_len;
      return 0;
    }
  }

  rewinddir(d_p);
  d_p = NULL;

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
    priv_narwal_thermal_zones_strip_line_jump(tz_p->type, '\0');
    tz_p->type_len = read_s - 1;
    close(fd);
  }

  return tz_p->type;
}


float narwal_thermal_zones_get_temp(NarwalThermalZone *tz_p)
{
  int fd;
  ssize_t read_s;
  char path[NARWAL_THERMAL_ZONE_PATH_MAX] = {0};
  char temp_str[NARWAL_THERMAL_ZONE_TEMP_MAX];

  long long_temp;

  strncpy(path, tz_p->path, tz_p->path_len);
  strcat(path, "/temp");

  fd = open(path, O_RDONLY);
  if (fd < 0){
    tz_p->error = errno;
    return errno;
  }

  read_s = read(fd, temp_str, NARWAL_THERMAL_ZONE_TEMP_MAX); 
  if (read_s < 0){
    tz_p->error = errno;
    return errno;
  }
  tz_p->type[read_s] = '\0';
  long_temp = strtol(temp_str, NULL, 10);

  close(fd);
  return long_temp/1000.0;
}
