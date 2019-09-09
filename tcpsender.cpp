#include <iostream>
#include <cstring>
#include <unistd.h>
#include "tcpsender.h"

using namespace std;

    void TcpSender::sendFileName(){
      int n;
      const char* const file_name = reader->getFileName();

      // debug
      //cout << "test debug : " << file_name << endl;
      //cout << "test debug : " << strlen(file_name) << endl; 

      n = write( client_socket, file_name, strlen(file_name) + 1);
      if( n < 0){
         cout << "Error sending data" << endl;
         throw 1;
      }
    }

    void TcpSender::sendFileSize(){
      int n; 
      const int file_size = reader->getFileSize();

      // debug
      //cout << "#debug. size : " << file_size << endl;

      cout << "file size : " << file_size << endl;

      // avoid endian problem
      unsigned char a_filesize[4]; 
      
      a_filesize[0] = file_size & 0x000000ff;
      a_filesize[1] = (file_size & 0x0000ff00) >> 8;
      a_filesize[2] = (file_size & 0x00ff0000) >> 16;
      a_filesize[3] = file_size >> 24;

      // debug
      //int ai = a_filesize[0]; cout << "#debug. a0 : " << ai << endl;
      //ai = a_filesize[1]; cout << "#debug. a1 : " << ai << endl;
      //ai = a_filesize[2]; cout << "#debug. a2 : " << ai << endl;
      //ai = a_filesize[3]; cout << "#debug. a3 : " << ai << endl;     

      n = write( client_socket, (char*)a_filesize, sizeof(a_filesize));

      if( n < 0){
         cout << "Error sending data" << endl;
         throw 1;
      }
    }

    void TcpSender::sendFileData(){
      int n;
      const char* const file_data = reader->getFileBuffer();

      n = write( client_socket, file_data, reader->getBufferLength());
      if( n < 0){
         cout << "Error sending data" << endl;
         throw 1;
      }
    }

    void TcpSender::closeTcpSocket(){
      close( client_socket);
    }

    void TcpSender::update(){
      // n = read( client_socket, buffer, 255);
      // n = write( client_socket, "I got your message", 18);
      switch(reader->getUpdateStatus()){
        case STATUS_GET_FILE_NAME :
          sendFileName();
          break;

        case STATUS_GET_FILE_SIZE :
          sendFileSize();
          break;

        case STATUS_READ_FILE :
          sendFileData();
          break;

        case STATUS_FINISH :
          closeTcpSocket();
      }
    }
    
    TcpSender::TcpSender(FileReader* myreader){
      reader = myreader;
    }

    void TcpSender::setSocket(int tcp_socket){
      client_socket = tcp_socket;
    }




