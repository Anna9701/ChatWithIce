CC = g++
CFLAGS = -g #-Wall #-Werror -Wpedantic -Wextra
LIBSFLAGS = -pthread -lIce -lIceUtil
TARGETDIR = Debug/
TARGETCLIENT = Debug/client
TARGETSERVER = Debug/server
CLIENTSRCDIR = src/client
SERVERSRCDIR = src/server
LIBSICE = src/libsIce
ICEDIR = ice

INCLUDES = -I $(CLIENTSRCDIR) -I $(ICEDIR) -I $(LIBSICE) -I $(SERVERSRCDIR)
SRCICE = $(ICEDIR)/chat.cpp $(LIBSICE)/UserImpl.cpp $(LIBSICE)/ServerImpl.cpp $(LIBSICE)/RoomFactoryImpl.cpp $(LIBSICE)/RoomImpl.cpp
SRCSCLIENT = $(SRCICE) $(CLIENTSRCDIR)/Client.cpp  $(CLIENTSRCDIR)/clientMain.cpp
SRCSSERVER = $(SRCICE) $(SERVERSRCDIR)/server.cpp
SRC = $(SRCSCLIENT) $(SRCSSERVER)

OBJS = $(SRC:.cpp=.o)
.PHONY: clean All

All: $(TARGETCLIENT) $(TARGETSERVER)
        @echo "----------Building project:[ Zadanie 2 Chat - Debug ]----------"

$(TARGETCLIENT):
		mkdir -p $(TARGETDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGETCLIENT) $(SRCSCLIENT) $(LIBSFLAGS)
		

$(TARGETSERVER):
		mkdir -p $(TARGETDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGETSERVER) $(SRCSSERVER) $(LIBSFLAGS)

.cpp.o:
		$(CC) $(CFLAGS) $(INCLUDES) -o $< -o $@

clean:
		@echo "----------Cleaning project:[ Zadanie 2 Chat - Debug ]----------"
		$(RM) *.o *~ $(TARGETCLIENT)
		$(RM) *.o *~ $(TARGETSERVER)
