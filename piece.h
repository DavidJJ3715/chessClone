#ifndef _piece_
#define _piece_
#include "definitions.h" //Included for the sole purpose of using SDL_Renderer, map, and shared_ptr in the class files

using namespace std;

class piece
{
    public:
        virtual bool Draw(SDL_Renderer*) {return false;}
        virtual bool drawRedBoxes(SDL_Renderer*, string, int, map<int, shared_ptr<piece>>) {return false;}
        virtual bool validMove(int) {return false;}
        virtual int check(int, map<int, shared_ptr<piece>>) {return 0;}
        virtual void update(piece&, int) {}
        virtual bool canAttackTile(int, int, map<int, shared_ptr<piece>>) {return false;}

        virtual char getColor() {return 'w';}
        virtual int getxCoord() {return 0;}
        virtual int getyCoord() {return 0;}
        virtual string getIdentity() {return "piece";}

        virtual void setxCoord(int) {}
        virtual void setyCoord(int) {}
        virtual void setfirstMove() {}
};

#endif