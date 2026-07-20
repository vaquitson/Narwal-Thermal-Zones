CC = gcc
CFLAGS = -Wall -Wextra
NARWAL_TZ_DIR = ./src/narwal_thermal_zones

CPPFLAGS = -I./src/
CPPFLAGS_TZ = -I$(NARWAL_TZ_DIR) 

test: $(NARWAL_TZ_DIR)/narwal_thermal_zones.c  ./tests/basic_test.c 
	mkdir -p ./build/tests/
	$(CC) $(CPPFLAGS_TZ) -o ./build/tests/basic_test $(NARWAL_TZ_DIR)/narwal_thermal_zones.c  ./tests/basic_test.c 


tz_inspect: ./examples/narwal_tz_inspect/narwal_tz_inspect.c $(NARWAL_TZ_DIR)/narwal_thermal_zones.c
	mkdir -p ./build/tests/examples/
	$(CC) $(CPPFLAGS_TZ) -o ./build/tests/examples/tz_inspect $(NARWAL_TZ_DIR)/narwal_thermal_zones.c ./examples/narwal_tz_inspect/narwal_tz_inspect.c

