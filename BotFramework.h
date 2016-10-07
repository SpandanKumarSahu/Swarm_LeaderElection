#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <fstream>
#include <thread>
#include <mutex>
using namespace std;

/*
  For the time being there is only BotID and LeaderID in framwework.
*/

class Bot{
 private:
  int BotID;
  int LeaderID;
 public:
  //Create a bot with a proper ID.
  //Initially he is the leader of himself.
  Bot(int id){
    this.BotID=id;
    this.LeaderID=id;
  }
  //Primarily for creating temporary Bot structures.
  Bot(){
    this->BotID=7777;
    this->LeaderID=7777;
  }
  //Getters and setters for LeaderID
  int getLeader(){
    return this->LeaderID;
  }
  void setLeader(int id){
    this->LeaderID=id;
  }
  int getID(){
    return this->BotID;
  }
};

// Creates a bot description file.
void createBotFile(int id){
  fstream fs;
  fs.open("BotDescription.dat",ios::out|ios::trunc);
  Bot mBot(id);
  fs.seekp(0,ios::beg);
  fs.write((char*)&mBot,sizeof(Bot));
  fs.close();
}


//Sometimes, you need to update the bot file.
void updateBotFile(Bot mBot){
  fstream fs;
  fs.open("BotDescription.dat",ios::out|ios::trunc);
  fs.seekp(0,ios::beg);
  fs.write((char*)&mBot,sizeof(Bot));
  fs.close();
}



/*
  Framework for all kinds of Messages.
  Temporarily it's just LeaderElection and Motion
*/

class Message_LeaderElection{
 public:
  int leader;
};

class Message_Motion{
 public:
  float x,y,x,theta,vel_x,vel_y,vel_z;
};

class Message{
 public:
  int senderID;
  int receiverID;
  enum Type{
    LeaderElection,
    Motion
  } type;
  union Data{
    Message_LeaderElection leader;
    Message_Motion motion;
  } data;  
};
