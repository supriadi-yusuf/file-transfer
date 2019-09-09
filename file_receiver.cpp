#include <iostream>
#include <sstream>

#include "filewriter.h"
#include "tcpreceiver.h"

using namespace std;

void receive_file(int argc, char* argv[]){
  if( argc != 3){
     cout << "Should be " << argv[0] << " <ip_address> <port>" << endl;
     throw 1;
  }

  stringstream ss;
  int port;

  ss << argv[2];
  ss >> port;

  TcpReceiver receiver( argv[1], port);
  FileWriter writer(&receiver);

  receiver.add( &writer);
  receiver.run();

  cout << "Done" << endl;
}

int main(int argc, char* argv[]){
  try{
    receive_file( argc, argv);
  }catch(...){
    cout << "Error happened" << endl;
  }

  return 1;
}
