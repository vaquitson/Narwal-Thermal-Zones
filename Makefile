CC = gcc
CFLAGS = -Wall -Wextra
CPPFLAGS = -I./src/

test: ./src/narwal_thermal_zones.c  ./tests/basic_test.c 
	mkdir -p ./build/tests/
	$(CC) $(CPPFLAGS) $(CPPFLAGS) -o ./build/tests/basic_test ./src/narwal_thermal_zones.c  ./tests/basic_test.c 


