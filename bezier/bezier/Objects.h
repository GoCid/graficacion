//
//  Objects.h
//  bezier
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#ifndef Objects_h
#define Objects_h

#include <list>
#include <iterator>
#include <iostream>
#include <math.h>
using namespace std;

class Vertex
{//This class saves everything related to the vertex of the objects
    private:
        int id;//A variable to identify each vertex in the file
        double x;
        double y;
        double z;
    public:
        Vertex(){}
        Vertex(int id, double x, double y, double z){
            this->id = id;
            this->x = x;
            this->y = y;
            this->z = z;
        }
        int getId(){
            return this->id;
        }
        double getX(){
            return this->x;
        }
        double getY(){
            return this->y;
        }
        double getZ(){
            return this->z;
        }

        void changePosition(double x, double y, double z){
            this->x += x;
            this->y += y;
            this->z += z;
        }

        void changePositionWithCopy(double x, double y, double z, Vertex C){
            this->x = x + C.getX();
            this->y = y + C.getY();
            this->z = z + C.getZ();
        }

        void changePositionRound2D(double x, double y){
            double rx = this->x,ry = this->y;
            rx += x;
            ry += y;
            this->x = round(rx);
            this->y = round(ry);
        }

        void showVertex(){
            cout << "V " << this->x << " " << this->y <<  " " << this->z << endl;
        }
};

class Faces{
    private:
        int id;

    public:
        list<Vertex> vertices;
        Faces(){}
        Faces(int id){
            this->id = id;
        }

        Faces(int id, list<Vertex> vertices){
            this->id = id;
            this->vertices = vertices;
        }

        int getId(){
            return this->id;
        }

        void addVertex(Vertex v){
            vertices.push_back(v);
        }

        Vertex getVertexID(int id_Vertex){
            Vertex ret;
            list <Vertex> :: iterator it;
            for(it = this->vertices.begin(); it != this->vertices.end(); ++it){
                if(it->getId() == id_Vertex){
                    ret = *it;
                }
            }
            return ret;
        }

        void translate(double x, double y, double z){
            list <Vertex> :: iterator it;
            for(it = this->vertices.begin(); it != this->vertices.end(); ++it){
                it->changePosition(x,y,z);
            }
        }

        void translateWithCopy(double x, double y, double z, Faces C){
            list <Vertex> :: iterator it;
            for(it = this->vertices.begin(); it != this->vertices.end(); ++it){
                it->changePositionWithCopy(x,y,z,C.getVertexID(it->getId()));
            }
        }

        void showVertices(){//Shows the info about each vertex in the face
            list <Vertex> :: iterator it;
            for(it = this->vertices.begin(); it != this->vertices.end(); ++it){
                it->showVertex();
            }
        }

        void showFace(){//Shows the vertices of each face but only the ID
            list <Vertex> :: iterator it;
            cout << "F ";
            for(it = this->vertices.begin(); it != this->vertices.end(); ++it){
                cout << it->getId() << " ";
            }
            cout << endl;
        }
};

class Objects{
    private:
        string name;

    public:
        list<Faces> faces;
        Objects(){
        }

        Objects(string name, list<Faces> faces){
            this->name = name;
            this->faces = faces;
        }

        void addFace(Faces f){
            this->faces.push_back(f);
        }

        Faces getFace(int id_Face){
            Faces ret;
            list <Faces> :: iterator it;
            for(it = this->faces.begin(); it != this->faces.end(); ++it){
                if(it->getId() == id_Face){
                    ret = *it;
                }
            }
            return ret;
        }
        
        void setName(string name){
            this->name = name;
        }

        string getName(){
            return this->name;
        }
        
        Faces getFaceId(int id){
            list <Faces> :: iterator it;
            Faces found;
            for(it = this->faces.begin(); it != this->faces.end(); ++it){
                if(it->getId() == id){
                    found = *it;
                    break;
                }
            }
            return found;
        }

        void translateWithCopy(double x, double y, double z, Objects C){
            list <Faces> :: iterator it;
            for(it = this->faces.begin(); it != this->faces.end(); ++it){
                it->translateWithCopy(x,y,z,C.getFaceId(it->getId()));
            }
        }

        void translate(double x, double y, double z){
            list <Faces> :: iterator it;
            for(it = this->faces.begin(); it != this->faces.end(); ++it){
                it->translate(x,y,z);
            }
            //showAll();
        }

        void moveObjectRound2D(double x, double y){
            list <Faces> :: iterator it;
            list <Vertex> :: iterator it2;
            for(it = this->faces.begin(); it != this->faces.end(); ++it){
                for(it2 = it->vertices.begin() ; it2 != it->vertices.end() ; it2++){
                    it2->changePositionRound2D(x,y);
                }
            }
        }

        void showAll(list<Vertex> v){//This method shows the info just like it's saved in the obj file
            list <Faces> :: iterator it;
            list <Vertex> :: iterator it2;
            cout << this->name << " \n";
            for(it2 = v.begin(); it2 != v.end(); ++it2){
                it2->showVertex();
            }
            for(it = this->faces.begin(); it != this->faces.end(); ++it){
                it->showFace();
            }
            cout << endl;
        }

        void showAll(){//Shows the info saved in each object
            list <Faces> :: iterator it;
            cout << this->name << " \n";
            for(it = this->faces.begin(); it != this->faces.end(); ++it){
                it->showVertices();
                it->showFace();
                cout << endl;
            }
        }
};

#endif /* Objects_h */
