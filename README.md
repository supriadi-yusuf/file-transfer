This repository contains source in c++ to build simple application.
This application is simply to transfer file between two pc in a network.
on the server side file that we want to transfer must be put in source folder.
client side must have folder destination to store received file.

Compiling source code :
1. for server side application
   g++ file_sender.cpp tcpfileserver.cpp tcpsender.cpp filereader.cpp -o send_file
 
2. for client side application
   g++ file_receiver.cpp tcpreceiver.cpp filewriter.cpp -o receive_file
   
   
Command for transfering file :

  ./send_file <port> <file_name>
   
  example : ./send_file 20001 "Iterator Pattern – Design Patterns (ep 16).mp4"
  
  
Command for receiving file :

  ./receive_file <ip_address> <port>
   
  example : ./receive_file 127.0.0.1 20001
