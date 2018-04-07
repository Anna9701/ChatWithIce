CC = g++
CFLAGS = -g -Wall -Werror -Wpedantic -Wextra
TARGETDIR = Debug/
TARGETCLIENT = Debug/client
TARGETSERVER = Debug/server

INCLUDES = -I ./src/client/ -I ./ice/ -I ./src/libsIce/ -I ./src/server/
LIBS = -pthread -lIce -lIceUtil
SRCICE = ice/chat.cpp src/libsIce/UserImpl.cpp src/libsIce/ServerImpl.cpp
SRCSCLIENT = $(SRCICE) src/client/Client.cpp  src/client/clientMain.cpp
SRCSSERVER = $(SRCICE) src/server/server.cpp
SRC = $(SRCSCLIENT) $(SRCSSERVER)
OBJS = $(SRC:.cpp=.o)
.PHONY: clean All

All: $(TARGETCLIENT) $(TARGETSERVER)
        @echo "----------Building project:[ Zadanie 2 Chat - Debug ]----------"

$(TARGETCLIENT):
		mkdir -p $(TARGETDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGETCLIENT) $(SRCSCLIENT) $(LIBS)
		

$(TARGETSERVER):
		mkdir -p $(TARGETDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGETSERVER) $(SRCSSERVER) $(LIBS)

.cpp.o:
		$(CC) $(CFLAGS) $(INCLUDES) -o $< -o $@

clean:
		@echo "----------Cleaning project:[ Zadanie 2 Chat - Debug ]----------"
		$(RM) *.o *~ $(TARGETCLIENT)
		$(RM) *.o *~ $(TARGETSERVER)
