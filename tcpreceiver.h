#ifndef __tcpreceiver_h__
#define __tcpreceiver_h__

#include "itcpreceiver.h"

class TcpReceiver : public ITcpReceiver{
  private:
    const char* ip;
    int port;    

    char* fileBuffer;
    char fileName[150];
    int fileSize;

  public:
    TcpReceiver(const char* const my_ip, const int my_port);
    void add(IFileWriter* const mywriter);
    void remove(IFileWriter* const mywriter);
    void notify(); 

    const char * const getFileName();
    const int getFileSize();
    const char * const getFileData();
    void run();

};

#endif
