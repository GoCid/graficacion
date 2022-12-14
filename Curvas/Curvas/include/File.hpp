//
//  File.hpp
//  Curvas
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#ifndef File_hpp
#define File_hpp
#include <iostream>
#include "Object.hpp"
#include <fstream>
#include <string>
#include <sstream>

class File
{
    public:
        File();
        virtual ~File();
        void fileName(string n);
        bool open(void);
        bool saveInformation(Object *figure);
        void showInfo(Object figure);
        //Getters
        string getName(void);

    protected:

    private:
        string name;
        ifstream arch; //The file variable to open the file
};
#endif /* File_hpp */
