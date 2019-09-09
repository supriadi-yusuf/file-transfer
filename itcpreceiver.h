#ifndef __itcpreceiver_h__
#define __itcpreceiver_h__

#include "ifilewriter.h"

class ITcpReceiver{
  protected:
    IFileWriter* writer;

  public:
    virtual void add(IFileWriter* const mywriter) = 0;
    virtual void remove(IFileWriter* const mywriter) = 0;
    virtual void notify() = 0;
};
#endif
