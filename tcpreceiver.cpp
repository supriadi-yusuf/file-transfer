#include <iostream> 
#include <arpa/inet.h> 
#include <netdb.h> // header file for : gethostbyname
#include <unistd.h>
#include <cstring>

#include "tcpreceiver.h"
#include "ifilewriter.h"

using namespace std;

    TcpReceiver::TcpReceiver(const char* const my_ip, const int my_port){
      ip = my_ip;
      port = my_port;
    }

    void TcpReceiver::add(IFileWriter* const mywriter){
      writer = mywriter;
    }

    void TcpReceiver::remove(IFileWriter* const mywriter){

    }

    void TcpReceiver::notify(){
      writer->update();
    }

    const char * const TcpReceiver::getFileName(){
      return fileName;
    }
 
    const int TcpReceiver::getFileSize(){
      return fileSize;
    }

    const char * const TcpReceiver::getFileData(){
      return fileBuffer;
    }
    
    void TcpReceiver::run(){
      int sock_fd, n;
      struct sockaddr_in serv_addr;
      struct hostent* server;
      char* pData;

      sock_fd = socket( AF_INET, SOCK_STREAM, 0);
      if( sock_fd < 0){
        cout << "Error on creating socket" << endl;
        throw 1;
      }

      server = gethostbyname(ip); 
      if( server == NULL){
        cout << "Error no such host" << endl;
        throw 1;
      }

      bzero((char*)&serv_addr, sizeof(serv_addr));
      serv_addr.sin_family = AF_INET;
      bcopy((char*)server->h_addr, 
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length);
      
      serv_addr.sin_port = htons(port);

      if( connect( sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
         cout << "Error on connecting" << endl;
         throw 1;
      }   

      // get file name
      n = read( sock_fd, (char*)fileName, sizeof(fileName));
      if( n < 0 ){
         cout << "Error on reading from socket" << endl;
         throw 1;
      }

      cout << "receiving file : \"" << fileName << "\" ..." << endl;

      //debug
      //cout << "test debug : \"" << fileName << "\"" << endl;
       
      // get file size
      unsigned char a_filesize[4] = {0,0,0,0};

      n = read( sock_fd, (char*)a_filesize, sizeof(a_filesize));
      if( n < 0 ){
         cout << "Error on reading from socket" << endl;
         throw 1;
      }

      fileSize = a_filesize[0];
      fileSize += a_filesize[1] << 8;
      fileSize += a_filesize[2] << 16;
      fileSize += a_filesize[3] << 24;

      //debug
      //cout << "test debug : " << fileSize << endl;
 
      cout << "file size : " << fileSize << endl;

      // allocate memory
      fileBuffer = new char[fileSize];
      pData = fileBuffer;

      // get data
      for( int n_received=0; n_received < fileSize; n_received += n){
          n = read( sock_fd, (char*)pData, fileSize - n_received);
          if( n < 0 ){
             cout << "Error on reading from socket" << endl;
             throw 1;
          }   

          pData += n;       

      }

      close(sock_fd);

      cout << "receiving complete." << endl;

      notify();
   
      delete [] fileBuffer; 
    }
