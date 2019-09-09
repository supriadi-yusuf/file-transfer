#ifndef __tcpsender_h__
#define __tcpsender_h__

//#include "ifilereader.h"
#include "itcpsender.h"
#include "filereader.h"

class TcpSender : public ITcpSender{ 
  private:
    FileReader* reader;
    int client_socket ;
    void sendFileName();
    void sendFileSize();
    void sendFileData();
    void closeTcpSocket();

  public:     
    void update();
    TcpSender(FileReader* myreader); 
    void setSocket(int tcp_socket);

};

#endif
