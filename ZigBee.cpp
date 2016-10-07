#include<bits/stdc++.h>
#include"BotFramework.h"
using namespace std;

void broadcast(fsteam networks,Message m){
  Bot mBot;
  while(!networks.eof()){
    networks.read((char*)mBot,sizeof(Bot));
    m.receiver=mBot.getID();
    sendTo(mBot,m);
  }
  networks.close();
}
