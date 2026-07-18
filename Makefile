CC = gcc
CFLAGS = -Wall -Wextra
CPPFLAGS = -I./src/

test: ./src/narwal_thermal_zones.c  ./tests/basic_test.c 
	mkdir -p ./build/tests/
	$(CC) $(CPPFLAGS) $(CPPFLAGS) -o ./build/tests/basic_test ./src/narwal_thermal_zones.c  ./tests/basic_test.c 


tz_inspect: ./examples/narwal_tz_inspect/narwal_tz_inspect.c ./src/narwal_thermal_zones.c
	mkdir -p ./build/tests/examples/
	$(CC) $(CPPFLAGS) $(CPPFLAGS) -o ./build/tests/examples/tz_inspect ./src/narwal_thermal_zones.c ./examples/narwal_tz_inspect/narwal_tz_inspect.c

