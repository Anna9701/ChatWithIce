module Chat {

interface Room;
interface RoomFactory;

exception UserAlreadyExists {};
exception NoSuchUserExist {};
exception WrongPassword {};
exception NoSuchRoomExist {};
exception RoomAlreadyExist {};

interface User {
  void SendMessage(Room* where, User* who, string message);
  void SendPrivateMessage(User* who, string message);
  string getName();
};

sequence<Room*> RoomList;
sequence<RoomFactory*> RoomFactoryList;

interface Server {
  Room* CreateRoom(string name) throws RoomAlreadyExist;
  RoomList getRooms();
  Room* FindRoom(string name) throws NoSuchRoomExist;
  //void RegisterUser(string name, string password) throws UserAlreadyExists;
  //void ChangePassword(User* user, string oldpassword, string newpassword);
  void RegisterRoomFactory(RoomFactory* factory);
  void UnregisterRoomFactory(RoomFactory* factory);
};

sequence<User*> UserList;

interface Room {
  string getName();
  UserList getUsers();
  void AddUser(User* who, string password) throws UserAlreadyExists;
  void ChangePassword(User* user, string oldpassword, string newpassword) throws NoSuchUserExist, WrongPassword;
  void SendMessage(User* who, string message, string passwd);
  void Destroy();
  void LeaveRoom(User* who, string passwd);
};

interface RoomFactory
{
   Room* createRoom(string name);
   RoomList getRooms();
};

};
