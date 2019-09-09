#include <iostream>
#include <fstream>
#include <string>

#include <sys/stat.h>

#include "filereader.h"

using namespace std;

    void FileReader::add(ITcpSender* mysender){
      sender = mysender;
    }

    void FileReader::remove(ITcpSender* mysender){
    }

    void FileReader::notify(){
      sender->update();
    }

    FileReader::FileReader(const char* const myfilename){
      fileName = myfilename;
    }

    const int FileReader::getUpdateStatus(){
      return updateStatus;
    }

    const char * const FileReader::getFileName(){
      return fileName;
    }

    const int FileReader::getFileSize(){
      return fileSize;
    }

    const char * const FileReader::getFileBuffer(){
      return fileBuffer;
    }

    int FileReader::getBufferLength(){
      return sizeof(fileBuffer);
    }

    void FileReader::read(){
      string myFileName = fileName;

      //updateStatus = STATUS_GET_FILE_NAME;
      //notify();
    
      myFileName = "source/" + myFileName;

      struct stat fileInfo;

      if(stat( myFileName.c_str(), &fileInfo) ) { 
         //error
         cout << "File : " << fileName << " tidak ditemukan." << endl;
         throw 0;
      }

      updateStatus = STATUS_GET_FILE_NAME;
      notify();
      
      fileSize = fileInfo.st_size;

      // debug
      //cout << "#debug. size : " << fileSize << endl;     

      updateStatus = STATUS_GET_FILE_SIZE;
      notify();

      updateStatus = STATUS_READ_FILE;

      ifstream ifile;

      ifile.open( myFileName.c_str(), ios::in | ios::binary);
      if( !ifile){
         cout << "file tidak dapat dibuka" << endl;
         throw 0;
      }

      for( int i=0; i < fileSize; i += sizeof(fileBuffer)){
        ifile.read( fileBuffer, sizeof(fileBuffer));
        notify();
      }        

      ifile.close(); 

      updateStatus = STATUS_FINISH;
      notify();   
    }

