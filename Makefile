CC = g++
CFLAGS = -g -Wall #-Werror -Wpedantic -Wextra
LIBSFLAGS = -pthread -lIce -lIceUtil -std=c++0x
TARGETDIR = Debug/
TARGETCLIENT = Debug/client
TARGETSERVER = Debug/server
TARGETFACTORY = Debug/factory
CLIENTSRCDIR = src/client
SERVERSRCDIR = src/server
FACTORYSRCDIR = src/roomFactory
LIBSICE = src/libsIce
ICEDIR = ice

INCLUDES = -I $(CLIENTSRCDIR) -I $(ICEDIR) -I $(LIBSICE) -I $(SERVERSRCDIR) -I $(FACTORYSRCDIR)
SRCICE = $(ICEDIR)/chat.cpp $(LIBSICE)/UserImpl.cpp $(LIBSICE)/ServerImpl.cpp $(LIBSICE)/RoomFactoryImpl.cpp $(LIBSICE)/RoomImpl.cpp
SRCSCLIENT = $(SRCICE) $(CLIENTSRCDIR)/Client.cpp  $(CLIENTSRCDIR)/ClientMain.cpp $(CLIENTSRCDIR)/Menu.cpp
SRCSSERVER = $(SRCICE) $(SERVERSRCDIR)/Server.cpp
SRCFACTORY = $(SRCICE) $(FACTORYSRCDIR)/main.cpp $(FACTORYSRCDIR)/Factory.cpp
SRC = $(SRCSCLIENT) $(SRCSSERVER)

OBJS = $(SRC:.cpp=.o)
.PHONY: clean All

All: $(TARGETCLIENT) $(TARGETSERVER) $(TARGETFACTORY)
        @echo "----------Building project:[ Zadanie 2 Chat - Debug ]----------"

$(TARGETCLIENT):
		mkdir -p $(TARGETDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGETCLIENT) $(SRCSCLIENT) $(LIBSFLAGS)
		

$(TARGETSERVER):
		mkdir -p $(TARGETDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGETSERVER) $(SRCSSERVER) $(LIBSFLAGS)

$(TARGETFACTORY):
		mkdir -p $(TARGETDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGETFACTORY) $(SRCFACTORY) $(LIBSFLAGS)

.cpp.o:
		$(CC) $(CFLAGS) $(INCLUDES) -o $< -o $@

clean:
		@echo "----------Cleaning project:[ Zadanie 2 Chat - Debug ]----------"
		$(RM) *.o *~ $(TARGETCLIENT)
		$(RM) *.o *~ $(TARGETSERVER)
		$(RM) *.o *~ $(TARGETFACTORY)
