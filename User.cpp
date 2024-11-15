#include <iostream>
#include <vector>
#include <string>

using namespace std;

class User{
    public:
        int ID;
        string userName;
        string fullName;
        int connections;
        User* next;
        vector<User*> friends;

        User(int ID, string userName, string fullName);
        User();
        void print();
};



User::User(int ID, string userName, string fullName){
    this->ID = ID;
    this->userName = userName;
    this->fullName=fullName;
    next = nullptr;
    connections = 0;

}
User::User(){
    ID = -1;
    userName = "";
    fullName = "";
    next = nullptr;
    connections = -1;
}


void User::print(){
    cout << userName << endl;
    cout << "\t Full Name:" << fullName << endl;
    cout << "\t ID: " << ID << endl;
    cout << "\t Connections: " << connections << endl;
}