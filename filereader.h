#ifndef __filereader_h__
#define __filereader_h__

#include "ifilereader.h"
#include "itcpsender.h"

class FileReader : public IFileReader{
  private:
    char fileBuffer[1000];
    const char * fileName;
    int fileSize;
    int updateStatus;

  public:    
    void add(ITcpSender* mysender);
    void remove(ITcpSender* mysender);
    void notify();
    FileReader(const char* const myfilename);
    const int getUpdateStatus();
    const char * const getFileName();
    const int getFileSize();
    const char * const getFileBuffer();
    int getBufferLength();
    void read();

    #define STATUS_READY 0
    #define STATUS_GET_FILE_NAME 1
    #define STATUS_GET_FILE_SIZE 2
    #define STATUS_READ_FILE 3
    #define STATUS_FINISH 4
};

#endif
