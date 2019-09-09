#include <iostream>
#include <fstream>
#include <string>

#include "filewriter.h"
#include "tcpreceiver.h"

using namespace std;

    FileWriter::FileWriter(TcpReceiver* myreceiver){
      receiver = myreceiver;
    }

    void FileWriter::update(){
      string fileName = receiver->getFileName();
      const int fileSize = receiver->getFileSize();
      const char* const fileBuffer = receiver->getFileData();

      cout << "Writing process ..." << endl;

      ofstream ofile;

      fileName = "destination/" + fileName;
      ofile.open( fileName.c_str() , ios::out | ios::trunc | ios::binary);
      
      ofile.write( fileBuffer, fileSize);

      ofile.close();

      cout << "Writing finish." << endl;
    }
