#include <iostream>
#include <fstream>
#include "functions.h"

using namespace std;

unsigned char* initialize() {
    FILE *myFile = fopen("test.txt", "rb");
    if(!myFile) {
        cout << "Source File not found!";
        return 0;
    }
    else {
        cout << "Opened Source file";
        fseek(myFile, 0, SEEK_END);
        int sz = ftell(myFile);
        //cout << "\n" << "sz: " << sz;
        fseek(myFile, 0, SEEK_SET);
        unsigned char *buffer = new unsigned char[sz+1];
        fread(buffer, 1, sz, myFile);
        fclose(myFile);
        buffer[sz] = 0;
        
        int lineNum = 0;
        cout << "\n" << "line " << lineNum << ": ";
        for(int i = 0; i < sz; i++) {
            if(buffer[i] == '\n') {
                cout << buffer[i];
                lineNum++;
                cout << "line " << lineNum << ": ";
                continue;
            }
            cout << buffer[i];
        }
        cout << "\n";
        return buffer;
    }
}