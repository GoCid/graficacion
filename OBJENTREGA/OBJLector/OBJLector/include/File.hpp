//
//  File.hpp
//  OBJLector
//
//  Created by Leonardo Alejandro González López on 18/09/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <iostream>
#include "File.hpp"
#include <fstream>
#include "Object.hpp"
#include <string>
#include <sstream>

class File
{
public:
    File();
    virtual ~File();
    void fileName(void);
    bool open(void);
    bool saveInformation(Object *figure);
    void showInfo(Object figure);
        //Getters
    string getName(void);

private:
    string name;
    ifstream arch; //The file variable to open the file
};

#endif /* File_hpp */
