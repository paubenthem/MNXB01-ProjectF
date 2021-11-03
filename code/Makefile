CFLAGS = $(include_dirs) $(WFLAGS) 
WFLAGS = -Wall -Wextra -Werror
include_dirs = -Iinclude

all: 
	g++ -Iinclude src/* -c

debug: all
	g++ -Iinclude *.o main.cpp

clean:
	rm *.o
