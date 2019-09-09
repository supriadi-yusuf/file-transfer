#ifndef __filewriter_h__
#define __filewriter_h__

#include "ifilewriter.h"
#include "tcpreceiver.h"

class FileWriter : public IFileWriter{
  private:
    TcpReceiver* receiver;

  public: 
    FileWriter(TcpReceiver* myreceiver);
    void update();

};

#endif
