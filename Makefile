CC = g++
CFLAGS = -g -Wall -Werror -Wpedantic -Wextra
TARGETDIR = Debug/
TARGETCLIENT = Debug/client
TARGETSERVER = Debug/server

INCLUDES = -I ./src/ -I ./ice/ -I ./src/libs/
LIBS = -pthread -lIce -lIceUtil
SCRSCLIENT = src/client.cpp ice/chat.cpp
SCRSSERVER = src/server.cpp ice/chat.cpp src/libs/UserI.cpp
OBJS = $(SCRS:.c=.o)

.PHONY: clean All

All: $(TARGETCLIENT) $(TARGETSERVER)
        @echo "----------Building project:[ Zadanie 2 Chat - Debug ]----------"

$(TARGETCLIENT):
		mkdir -p $(TARGETDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGETCLIENT) $(SCRSCLIENT) $(LIBS)
		

$(TARGETSERVER):
		mkdir -p $(TARGETDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGETSERVER) $(SCRSSERVER) $(LIBS)

.cpp.o:
		$(CC) $(CFLAGS) $(INCLUDES) -o $< -o $@

clean:
		@echo "----------Cleaning project:[ Zadanie 2 Chat - Debug ]----------"
		$(RM) *.o *~ $(TARGETCLIENT)
		$(RM) *.o *~ $(TARGETSERVER)
