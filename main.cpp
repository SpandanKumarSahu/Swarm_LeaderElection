#include<iostream>
#include<queue>
#include<thread>
#include<mutex>
#include<type_traits>
#include"ZigBee.h"
#include"BotFramework.h"

std::mutex mtx;

//Create a stack of messages that are received.
std::queue<Message>tasks;

  //Create a message for shouting its own ID to others.
Message create_LeaderElectionMessage(int leader_id){
  Message election;
  election.senderID=i_dec;
  election.type=Message::LeaderElection;
  Message_LeaderElection lm;
  lm.leader=i_dec;
  election.data=lm;
  return election;
}

// Wish to discuss the option of calling another program to handle different inputs differntly or just do it in here.
   
void do_the_task(){
  mtx.lock();
  if(tasks.front().type==Message::LeaderElection){
    fstream fs;
    fs.open("BotDescription.dat",ios::in);
    fs.seekg(0,ios::beg);
    Bot mBot;
    fs.read((char*)&mBot,sizeof(Bot));
    if(mBot.getLeader()>tasks.front().data.leader){
      mBot.setLeader(tasks.front().data.leader);
      fs.close();
      fs.open("BotDescription.dat",ios::out|ios::trunc);
      fs.seekp(0,ios::beg);
      fs.write((char*)&mBot,sizeof(Bot));
    }
    fs.close();
    fstream networks=getNetworks(mBot.getID());
    
    //Broadcast to all networks and if needed, may have to stop listening for sometime.
    ZigBeeHandler handler=new ZigBeeHandler();
    handler.broadcast(networks,create_LeaderElectionMessage(mBot.getLeader()));
    if(networks.is_open())
      networks.close();
  }
  mtx.unlock();
}

int main(int argc,char *argv[]){
  //Get BotID as input and a create a file of it.
  std::string::size_type sz;   // alias of size_t
  int i_dec = std::stoi (argv[1],&sz);
  createBotFile(i_dec);

  //Get all networks available.
  fstream networks=getNetworks(i_dec);
  
  //Broadcast to all networks.
  ZigBeeHandler handler=new ZigBeeHandler();
  handler.broadcast(networks,create_LeaderElectionMessage(i_dec));
  if(networks.is_open())
    networks.close();

  //Create socket and keep listening to messages and push them in the stack.
  /*
    while(1){
      create_socket();    // Follow previously written TCP/IP code.
      listen();
      Message m;
      if(m=accept_message()){
	tasks.push(m);
	std::thread t(do_the_task);
	t.join();
      }   
    }
  */
  return 0;
}
  
		    
