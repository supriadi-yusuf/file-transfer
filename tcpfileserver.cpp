#include <iostream>
#include <cstring>

#include <unistd.h> // header file for close()
#include <arpa/inet.h> // header file for : struct sockaddr_in, socklen_t, etc
#include <sys/stat.h>

#include "tcpfileserver.h"
#include "tcpsender.h"
#include "filereader.h"

using namespace std;

    void TcpFileServer::sendFile(int client_socket){
      FileReader file_reader(fileName);
      TcpSender tcp_sender(&file_reader);

      tcp_sender. setSocket(client_socket); 
      file_reader.add(&tcp_sender);

      cout << "transferring file : \"" << fileName << "\"" << endl; 

      file_reader.read();      

      cout << "Done" << endl;
    }

    TcpFileServer::TcpFileServer(const int tcp_port, const char* const strfileName){
      // check if file exist
      struct stat fileInfo;
      string myfilename = strfileName;

      myfilename = "source/" + myfilename;

      if(stat( myfilename.c_str(), &fileInfo) ) { 
         //error
         cout << "File : " << strfileName << " tidak ditemukan." << endl;
         throw 0;
      }

      portno = tcp_port;
      fileName = strfileName;
    }

    void TcpFileServer::run(){
      struct sockaddr_in serv_addr, cli_addr;
      socklen_t cli_len;
      int sock_fd, newsock_fd, pid=0;

      sock_fd = socket( AF_INET, SOCK_STREAM, 0);
      if( sock_fd < 0){
        cout << "Error in creating socket" << endl;
        throw 1; // raise exception
      }

      bzero((char*)&serv_addr, sizeof(serv_addr));

      serv_addr.sin_family = AF_INET;
      serv_addr.sin_addr.s_addr = INADDR_ANY;
      serv_addr.sin_port = htons(portno);  

      if( bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0 ){
         cout << "Error on binding" << endl;
         throw 1; // raise exception
      }

      if( listen( sock_fd, 5) < 0){
         cout << "Error on listening" << endl;
         throw 1; // raise exception
      }

      while(1){
         newsock_fd = accept( sock_fd, (struct sockaddr*)&cli_addr, &cli_len);
         if( newsock_fd < 0){
            cout << "Error on accept" << endl;
            throw 1;
         }

         pid = fork();
         if( pid ==  0){
            sendFile(newsock_fd);            
         }else{
            close(newsock_fd);
            
            if( pid < 0){
               cout << "Error on fork" << endl;
               throw 1;
            }
         }

      }

      close(sock_fd);
    }

