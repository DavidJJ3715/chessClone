#ifndef _definitions_
#define _definitions_
#define SDL_MAIN_HANDLED
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "server.h"

using namespace std;

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;
const int SPRITE_HEIGHT = 100;
const int SPRITE_WIDTH = 100;

int titleScreen(SDL_Renderer* renderer, TTF_Font* scoreFont)
{
    SDL_Surface *surface{};
    SDL_Texture *msg{}, *startGame{}, *quitGame{}, *multiP{};
    SDL_Rect begin = {250, 300, 300, 100}, multi = {250, 425, 300, 100}, end = {275, 550, 250, 100}, message = {150, 50, 500, 150};

    if(!(surface = TTF_RenderText_Solid(scoreFont, "CHESS", {0xFF, 0xFF, 0xFF, 0xFF})))
        {cout << "Surface Error\n"; return -1;}
    if(!(msg = SDL_CreateTextureFromSurface(renderer, surface)))
        {cout << "msg Error\n"; return -1;}
    if(!(surface = TTF_RenderText_Solid(scoreFont, "SINGLE PLAYER", {0xFF, 0xFF, 0xFF, 0xFF})))
        {cout << "Surface Error\n"; return -1;}
    if(!(startGame = SDL_CreateTextureFromSurface(renderer, surface)))
        {cout << "startGame Error\n"; return -1;}
    if(!(surface = TTF_RenderText_Solid(scoreFont, "MULTIPLAYER", {0xFF, 0xFF, 0xFF, 0xFF})))
        {cout << "Surface Error\n"; return -1;}
    if(!(multiP = SDL_CreateTextureFromSurface(renderer, surface)))
        {cout << "startGame Error\n"; return -1;}
    if(!(surface = TTF_RenderText_Solid(scoreFont, "QUIT", {0xFF, 0xFF, 0xFF, 0xFF})))
        {cout << "Surface Error\n"; return -1;}
    if(!(quitGame = SDL_CreateTextureFromSurface(renderer, surface)))
        {cout << "quitGame Error\n"; return -1;}

    if(SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0x80, 0x00) < 0)
        {cout << "SetRenderDrawColor Error\n"; return -1;}
    if(SDL_RenderFillRect(renderer, NULL) < 0)
        {cout << "RenderFillRect Error\n"; return -1;}

    if(SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00) < 0)
        {cout << "SetRenderDrawColor Error\n"; return -1;}
    if(SDL_RenderCopy(renderer, startGame, nullptr, &begin) < 0)
        {cout << "RenderCopy Error\n"; return -1;}
    if(SDL_RenderCopy(renderer, multiP, nullptr, &multi) < 0)
        {cout << "RenderCopy Error\n"; return -1;}
    if(SDL_RenderCopy(renderer, quitGame, nullptr, &end) < 0)
        {cout << "RenderCopy Error\n"; return -1;}

    if(SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF) < 0)
        {cout << "SetRenderDrawColor Error\n"; return -1;}
    if(SDL_RenderCopy(renderer, msg, nullptr, &message) < 0)
        {cout << "RenderCopy Error\n"; return -1;}
    SDL_RenderPresent(renderer);
    
    int ret = 0;
    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                {
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                        {
                            int initX = event.motion.x;
                            int initY = event.motion.y;
                            if((initX >= 250 && initX <= 550) && (initY >=300 && initY <= 400))
                                {ret = 1; running = false;}
                            else if((initX >= 250 && initX <= 550) && (initY >=425 && initY <= 525))
                                {ret = 2; running = false;}
                            else if((initX >= 275 && initX <= 550) && (initY >=550 && initY <= 650))
                                {ret = -1; running = false;}
                        }
                    }
                }
            }
        }   
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(msg);
    SDL_DestroyTexture(startGame);
    SDL_DestroyTexture(quitGame);
    return ret;
}

bool Create_Board(SDL_Renderer* renderer) 
{
    SDL_Rect Box = {0,0,100,100};
    bool toggle_color = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(toggle_color)
            {
                if(SDL_SetRenderDrawColor(renderer, 0x3D, 0x2B, 0x1F, 0xFF) < 0) //darker brown squares
                    {cout << "SetRenderDrawColor Error\n"; return false;}
            }
            else
            {
                if(SDL_SetRenderDrawColor(renderer, 0xBD, 0x8F, 0x60, 255) < 0) //lighter brown squares
                    {cout << "SetRenderDrawColor Error\n"; return false;}  
            }
            if(SDL_RenderFillRect(renderer, &Box) < 0)
                {cout << "SetRenderFillRect Error\n"; return false;}
            Box.x += 100;
            if(j != 7) //needed for chess color pattern
            toggle_color = !toggle_color;
        }
        Box.x = 0;
        Box.y += 100;
    }
    return true;
}

void redrawBoard(SDL_Renderer* renderer, map<int, shared_ptr<piece>> board)
{
    Create_Board(renderer);
    for(int i = 1; i < 65; i++)
    {
        if(board.find(i) == board.end()) 
            {continue;}
        else 
            {board.at(i).get()->Draw(renderer);}
    }
}

void loadPNGs(vector<string> &PNGHolder, string path)
{
    PNGHolder.push_back(path + "spritePNGs/whiteRook.png");     //0
    PNGHolder.push_back(path + "spritePNGs/whiteQueen.png");    //1
    PNGHolder.push_back(path + "spritePNGs/whitePawn.png");     //2
    PNGHolder.push_back(path + "spritePNGs/whiteKnight.png");   //3
    PNGHolder.push_back(path + "spritePNGs/whiteKing.png");     //4
    PNGHolder.push_back(path + "spritePNGs/whiteBishop.png");   //5
    PNGHolder.push_back(path + "spritePNGs/blackRook.png");     //6
    PNGHolder.push_back(path + "spritePNGs/blackQueen.png");    //7
    PNGHolder.push_back(path + "spritePNGs/blackPawn.png");     //8
    PNGHolder.push_back(path + "spritePNGs/blackKnight.png");   //9
    PNGHolder.push_back(path + "spritePNGs/blackKing.png");     //10
    PNGHolder.push_back(path + "spritePNGs/blackBishop.png");   //11
    PNGHolder.push_back(path + "spritePNGs/redBox.png");        //12
}

int getRow(int y)
{
    int row = 0;
    if(y < 100) {row += 1;}
    else if(y < 200) {row = 2;}
    else if(y < 300) {row = 3;}
    else if(y < 400) {row = 4;}
    else if(y < 500) {row = 5;}
    else if(y < 600) {row = 6;}
    else if(y < 700) {row = 7;}
    else if(y < 800) {row = 8;}
    return row;
}

int getColumn(int x)
{
    int column = 0;
    if(x < 100) {column += 1;}
    else if(x < 200) {column = 2;}
    else if(x < 300) {column = 3;}
    else if(x < 400) {column = 4;}
    else if(x < 500) {column = 5;}
    else if(x < 600) {column = 6;}
    else if(x < 700) {column = 7;}
    else if(x < 800) {column = 8;}
    return column;
}

int getTile(int x, int y)
{
    int column = getColumn(x);
    int row = getRow(y);
    int tile = ((row-=1)*8) + column;
    return tile;
}

int select(SDL_Renderer* renderer, piece &given, int tileClicked, string Box, map<int, shared_ptr<piece>> board)
{
    bool loop = true;
	SDL_Event event;
    if(!given.drawRedBoxes(renderer, Box, tileClicked, board))
        {cout << "RedBox Error\n";}

	while(loop)
	{
		SDL_PollEvent(&event);
		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
			{
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
                        int clickX = event.motion.x;
                        int clickY = event.motion.y;
                        int newTileClicked = getTile(clickX, clickY);
                        if(newTileClicked == tileClicked)
                            {loop = false; break;}
                        
                        if(!given.validMove(newTileClicked))
                            {break;}
                        else
                            {return newTileClicked;}
					}
                    case SDL_BUTTON_RIGHT:
                        {cout << "\n\nWhy tf you right clickin? -__-\n\n\n"; break;}
				}
				break;
			}
		}
	}
    return -1;
}

bool playAgain(SDL_Renderer* renderer, char winChar, TTF_Font* scoreFont, map<int, shared_ptr<piece>> board)
{
    endScreen:
        bool ret = true, running = true;
        const char* winString;
        SDL_Surface* surface{};
        SDL_Texture* gameOverMsg{}, *winnerMsg{}, *retryButton{}, *quitButton{}, *seeBoardButton{};
        SDL_Rect gameOver = {150, 50, 500, 150}, winner = {200, 150, 400, 150};
        SDL_Rect playAgain = {250, 300, 300, 100}, titleScreen = {250, 425, 300, 100}, seeBoardAgain = {275, 550, 250, 100};

        if(winChar == 'w')
            {winString = "WHITE WINS";}
        else
            {winString = "BLACK WINS";}

        if(!(surface = TTF_RenderText_Solid(scoreFont, "GAME OVER", {0xFF, 0xFF, 0xFF, 0xFF})))
            {cout << "Surface Error\n"; return false;}
        if(!(gameOverMsg = SDL_CreateTextureFromSurface(renderer, surface)))
            {cout << "gameOverMsg Error\n"; return false;}
        if(!(surface = TTF_RenderText_Solid(scoreFont, winString, {0xFF, 0xFF, 0xFF, 0xFF})))
            {cout << "Surface Error\n"; return false;}
        if(!(winnerMsg = SDL_CreateTextureFromSurface(renderer, surface)))
            {cout << "winnerMsg Error\n"; return false;}
        if(!(surface = TTF_RenderText_Solid(scoreFont, "PLAY AGAIN", {0xFF, 0xFF, 0xFF, 0xFF})))
            {cout << "Surface Error\n"; return false;}
        if(!(retryButton = SDL_CreateTextureFromSurface(renderer, surface)))
            {cout << "gameOverMsg Error\n"; return false;}
        if(!(surface = TTF_RenderText_Solid(scoreFont, "TITLE SCREEN", {0xFF, 0xFF, 0xFF, 0xFF})))
            {cout << "Surface Error\n"; return false;}
        if(!(quitButton = SDL_CreateTextureFromSurface(renderer, surface)))
            {cout << "gameOverMsg Error\n"; return false;}
        if(!(surface = TTF_RenderText_Solid(scoreFont, "See Board Again", {0xFF, 0xFF, 0xFF, 0xFF})))
            {cout << "Surface Error\n"; return false;}
        if(!(seeBoardButton = SDL_CreateTextureFromSurface(renderer, surface)))
            {cout << "gameOverMsg Error\n"; return false;}

        if(SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0x80, 0x00) < 0)
            {cout << "SetRenderDrawColor Error\n"; return false;}
        if(SDL_RenderFillRect(renderer, NULL) < 0)
            {cout << "RenderFillRect Error\n"; return false;}

        if(SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00) < 0)
            {cout << "SetRenderDrawColor Error\n"; return false;}
        if(SDL_RenderCopy(renderer, retryButton, nullptr, &playAgain) < 0)
            {cout << "RenderCopy Error\n"; return false;}
        if(SDL_RenderCopy(renderer, quitButton, nullptr, &titleScreen) < 0)
            {cout << "RenderCopy Error\n"; return false;}
        if(SDL_RenderCopy(renderer, seeBoardButton, nullptr, &seeBoardAgain) < 0)
            {cout << "RenderCopy Error\n"; return false;}

        if(SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF) < 0)
            {cout << "SetRenderDrawColor Error\n"; return false;}
        if(SDL_RenderCopy(renderer, gameOverMsg, nullptr, &gameOver) < 0)
            {cout << "RenderCopy Error\n"; return false;}
        if(SDL_RenderCopy(renderer, winnerMsg, nullptr, &winner) < 0)
            {cout << "RenderCopy Error\n"; return false;}
        SDL_RenderPresent(renderer);

        while(running)
        {
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        switch(event.button.button)
                        {
                            case SDL_BUTTON_LEFT:
                            {
                                int initX = event.motion.x;
                                int initY = event.motion.y;

                                if((initX >= 250 && initX <= 550) && (initY >=300 && initY <= 400))
                                    {ret = true; running = false;}
                                else if((initX >= 250 && initX <= 550) && (initY >=425 && initY <= 525))
                                    {ret = false; running = false;}
                                else if((initX >= 275 && initX <= 550) && (initY >=550 && initY <= 650))
                                {
                                    redrawBoard(renderer, board);
                                    SDL_RenderPresent(renderer);
                                    cout << "Press Any Button To Go Back To End Screen\n";
                                    while(true)
                                    {
                                        SDL_Event event2;
                                        while(SDL_PollEvent(&event2))
                                        {
                                            switch(event2.type)
                                            {
                                                case SDL_MOUSEBUTTONDOWN:
                                                case SDL_KEYDOWN:
                                                    goto endScreen;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }   
        }
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(gameOverMsg);
        SDL_DestroyTexture(winnerMsg);
        SDL_DestroyTexture(quitButton);
        SDL_DestroyTexture(retryButton);
        return ret;
}

bool isCheckMate(int tile, map<int, shared_ptr<piece>> board)
{
    vector<int> moves, safe, protect;
    int valid = 0, direction[8] = {-9, -8, -7, -1, 1, 7, 8, 9};
    shared_ptr<piece> deadKing = board.at(tile);

    for(int i = 0; i < 8; i++)
    {
        valid = deadKing.get()->check(tile-direction[i], board);
        if(valid > 0)
            {moves.push_back(valid);}
    }
    safe = moves;
    for(vector<int>::size_type i = 0; i < moves.size(); i++)
    {
        map<int, shared_ptr<piece>> temp = board;
        temp.insert(make_pair(moves.at(i), deadKing));
        temp.erase(tile);
        for(auto const& [tempTile, cPiece] : temp)
        {
            if(cPiece->getIdentity() == "king")
                {continue;}
            else if(cPiece.get()->getColor() == deadKing.get()->getColor())
                {continue;}
            int val = cPiece.get()->check(tempTile, temp);
            if(val > 0)
            {
                vector<int>::iterator it = find(safe.begin(), safe.end(), val);
                if(it != safe.end())
                    {safe.erase(it);}
            }
        }
    }

    if(safe.size() == 0)
    {
        moves.clear();
        safe.clear();   
        protect.clear();     
        return true;
    }
    moves.clear();
    safe.clear();
    return false;
}

bool protect(int attackerTile, map<int ,shared_ptr<piece>> board, int kingTile)
{
    for(auto const& [location, cPiece] : board)
    {
        if(location == attackerTile || location == kingTile)
            {continue;}
        if(cPiece.get()->getColor() != board.at(attackerTile).get()->getColor())
        {
            if(cPiece.get()->canAttackTile(location, attackerTile, board))
                {return true;}
        }
    }
    return false;
}

#endif