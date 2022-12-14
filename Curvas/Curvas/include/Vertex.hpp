//
//  Vertex.hpp
//  Curvas
//
//  Created by Leonardo Alejandro González López on 01/11/21.
//  Copyright © 2021 UASLP. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

//Class for one vertex in a 3d plane
class Vertex
{
    public:
        //Constructors
        Vertex();
        Vertex(double x,double y,double z);
        Vertex(const Vertex &v);
        //Getters
        double getX(void);
        double getY(void);
        double getZ(void);
        //Show information of the vertex
        void showVertex(void);
        virtual ~Vertex();
        void plusX(double n);
        void plusY(double n);
        void plusZ(double n);
        void setX(double n);
        void setY(double n);
        void setZ(double n);
        private:
        double posX;
        double posY;
        double posZ;
      
};
#endif /* Vertex_hpp */
