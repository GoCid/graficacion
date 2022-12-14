//
//  File.cpp
//  Curvas
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#include "File.hpp"
#include <fstream>
#include "Object.hpp"
File::File()
{
    //ctor
}

File::~File()
{
    //dtor
}

//ask for the name of the file, and add the extension .obj
void File::fileName(string n)
{
    //cout<<"Write the name og the file (without .obj) :";
    //getline(cin,name);//get the name of the file
    name = n;
}

//return if can open the file
bool File::open(void)
{
    bool resp = true;
    arch.open(name,ios::in);//Open the file
    if(arch.fail()) //Check if can open the file
        resp = false;
    return resp;
}

//Function to separe the string in substrings
//The resultant strings save in a vector of strings
vector<string> split(string str, char delimiter){
    vector<string> strings;
    stringstream ss(str); //transform the string ss in stream
    string token;
    while(getline(ss, token, delimiter))
        strings.push_back(token);
    return strings;
}

//Function to save the information of the obj file in the vector of Objects
bool File::saveInformation(Object *figure)
{
    vector<string> val;
    string text;//String to copy all the text
    bool resp = true;//answer if the program can save all the information
    while(!arch.eof() && resp)
    {
        getline(arch,text); //Save one line of the text
        val = split(text,' ');
        if(val.size())
        {
            if(val[0]=="f")
            {
                Face f;
                for(int i = 1; i < val.size(); i++)
                    f.addVertex(std::stoi(val[i])-1);
                figure->addFace(f);
            }
            else
                if(val[0] == "v")
                    figure->addVertex(Vertex(std::stod(val[1]),std::stod(val[2]),std::stod(val[3])));
        }
    }
    arch.close();//Close the archive
    return resp;
}

void File::showInfo(Object figure)
{
    figure.showAll();
}
string File::getName(void)
{
    return name;
}
