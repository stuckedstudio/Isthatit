//This document contains comments, because I'm making this game as a learning process, and therefor needs to remember a few things XD

#pragma once
#include "ECS.h"

class PositionComponent : public Component
{
    private:
        int xpos,ypos;

    public:
        int x() {return xpos;}
        int y() {return ypos;}

        //Using override to override the virtual functions in ECS.h
        void init() override
        {
            xpos = 0;
            ypos = 0;
        }
        void update() override
        {

        }
        void draw() override
        {
            
        }
        void setPos(int newX, int newY)
        {
            xpos = newX;
            ypos = newY;
        }

};