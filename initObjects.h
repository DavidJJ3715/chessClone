#ifndef _initObjects_
#define _initObjects_
#include "definitions.h"

using namespace std;

bool initPiecesMap(SDL_Renderer* renderer, vector<string> PNGHolder, map<int, shared_ptr<piece>> &board)
{
    for(int i = 0, x = 0; i < 8; i++)
    {
        pawn *temp = new pawn(PNGHolder.at(2), 'w', x, 615);
        if(!(temp->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        x += 100;
        board.insert(make_pair(getTile(temp->getxCoord(), temp->getyCoord()), temp));
    }
    for(int i = 0, x = 0; i < 8; i++)
    {
        pawn *temp = new pawn(PNGHolder.at(8), 'b', x, 115);
        if(!(temp->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        x += 100;
        board.insert(make_pair(getTile(temp->getxCoord(), temp->getyCoord()), temp));
    }
    if(true)
    {
        king *temp = new king(PNGHolder.at(4), 'w', 400, 700);
        if(!(temp->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp->getxCoord(), temp->getyCoord()), temp));
        queen *temp2 = new queen(PNGHolder.at(1), 'w', 300, 705);
        if(!(temp2->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp2->getxCoord(), temp2->getyCoord()), temp2));
    }
    if(true)
    {
        king *temp = new king(PNGHolder.at(10), 'b', 400, 0);
        if(!(temp->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp->getxCoord(), temp->getyCoord()), temp));
        queen *temp2 = new queen(PNGHolder.at(7), 'b', 300, 5);
        if(!(temp2->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp2->getxCoord(), temp2->getyCoord()), temp2));     
    }
    for(int i = 0, x = 100, x2 = 200, x3 = 0; i < 2; i++)
    {
        knight *temp = new knight(PNGHolder.at(3), 'w', x, 700);
        if(!(temp->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp->getxCoord(), temp->getyCoord()), temp));
        knight *temp2 = new knight(PNGHolder.at(9), 'b', x, 0);
        if(!(temp2->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp2->getxCoord(), temp2->getyCoord()), temp2));

        bishop *temp3 = new bishop(PNGHolder.at(5), 'w', x2, 715);
        if(!(temp3->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp3->getxCoord(), temp3->getyCoord()), temp3));
        bishop *temp4 = new bishop(PNGHolder.at(11), 'b', x2, 15);
        if(!(temp4->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp4->getxCoord(), temp4->getyCoord()), temp4));

        rook *temp5 = new rook(PNGHolder.at(0), 'w', x3, 700);
        if(!(temp5->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp5->getxCoord(), temp5->getyCoord()), temp5));
        rook *temp6 = new rook(PNGHolder.at(6), 'b', x3, 0);
        if(!(temp6->Draw(renderer)))
            {cout << "\n\nError Drawing Pieces\n\n\n"; return false;}
        board.insert(make_pair(getTile(temp6->getxCoord(), temp6->getyCoord()), temp6));
        
        x += 500;
        x2 += 300;
        x3 += 700;
    }

    return true;
}

#endif