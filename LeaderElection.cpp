#include<iostream>
#include<thread>
#include<mutex>
#include"ZigBee.h"
#include"BotFramework.h"

std::mutex mtx; 

int main(){
  //Get Bot description file.
  fstream BotFile=getBotFile();

  
  
