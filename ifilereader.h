#ifndef __ifilereader_h__
#define __ifilereader_h__

#include "itcpsender.h"

class IFileReader{
  protected:
    ITcpSender* sender;

  public:
    virtual void add(ITcpSender* mysender) = 0;
    virtual void remove(ITcpSender* mysender) = 0;
    virtual void notify() = 0;
};

#endif
