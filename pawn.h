#ifndef _Pawn_
#define _Pawn_
#include "piece.h"

using namespace std;

class pawn : public piece
{
    public:
		pawn(string, char, int, int);

		int getxCoord() override; 
		int getyCoord() override;
		bool getfirstMove();
		char getColor() override;
		string getPNG();
		string getIdentity() override;

		void setxCoord(int) override;
		void setyCoord(int) override;
		void setfirstMove() override;

		bool Draw(SDL_Renderer*);
		bool validMove(int) override;
		bool drawRedBoxes(SDL_Renderer*, string, int, map<int, shared_ptr<piece>>);
		int check(int, map<int, shared_ptr<piece>>) override;
		void update(piece&, int);
		bool canAttackTile(int, int, map<int, shared_ptr<piece>>) override;


	private: 
		bool firstMove = true;
		int xCoord;
		int yCoord;
		char color;
		string png;
		string identity;
		map<int, pair<int, int>> validBox;

};

pawn::pawn(string pngInput, char inputColor, int x, int y)
{
	png = pngInput;
	color = inputColor;
	xCoord = x;
	yCoord = y;
	identity = "pawn";
}

int pawn::getxCoord()
	{return xCoord;}
int pawn::getyCoord()
	{return yCoord;}
bool pawn::getfirstMove()
	{return firstMove;}
char pawn::getColor()
	{return color;}
string pawn::getPNG()
	{return png;}
string pawn::getIdentity()
	{return identity;}
		
void pawn::setxCoord(int x)
	{xCoord = x;}
void pawn::setyCoord(int y)
	{yCoord = y;}
void pawn::setfirstMove()
	{firstMove = false;}

bool pawn::Draw(SDL_Renderer* renderer)
{
	SDL_Texture* currentImage = IMG_LoadTexture(renderer, png.data());
    if(!currentImage) 
		{cout << "NO SPRITE" << endl; return false;}
	SDL_Rect dstrect = {xCoord, yCoord, 100, 100}; //sprite location and size				
	SDL_RenderCopy(renderer, currentImage, NULL, &dstrect);
	SDL_DestroyTexture(currentImage);
	return true;
}

bool pawn::drawRedBoxes(SDL_Renderer* renderer, string Box, int tileClicked, map<int, shared_ptr<piece>> board)
{
	SDL_Texture* currentImage;
	SDL_Rect redBox;
	currentImage = IMG_LoadTexture(renderer, Box.data());
        if(!currentImage) {cout << "NO SPRITE" << endl; return false;}

	if(color == 'w')
	{
		if(board.find(tileClicked-16) == board.end() && firstMove && board.find(tileClicked-8) == board.end())
		{
			redBox = {xCoord, yCoord-215, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-16, make_pair(xCoord, yCoord-200)));
		}
		if(board.find(tileClicked-8) == board.end())
		{
			redBox = {xCoord, yCoord-115, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-8, make_pair(xCoord, yCoord-100)));
		}
		if(board.find(tileClicked-7) != board.end())
		{
			if(board.at(tileClicked-7).get()->getColor() != color)
			{
				redBox = {xCoord+100, yCoord-115, 100, 100};
				SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
				validBox.insert(make_pair(tileClicked-7, make_pair(xCoord+100, yCoord-100)));				
			}
		}
		if(board.find(tileClicked-9) != board.end())
		{
			if(board.at(tileClicked-9).get()->getColor() != color)
			{
				redBox = {xCoord-100, yCoord-115, 100, 100};
				SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
				validBox.insert(make_pair(tileClicked-9, make_pair(xCoord-100, yCoord-100)));				
			}
		}
	}	
	else
	{
		if(board.find(tileClicked+16) == board.end() && firstMove && board.find(tileClicked+8) == board.end())
		{
			redBox = {xCoord, yCoord+185, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+16, make_pair(xCoord, yCoord+200)));
		}
		if(board.find(tileClicked+8) == board.end())
		{
			redBox = {xCoord, yCoord+85, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+8, make_pair(xCoord, yCoord+100)));
		}
		if(board.find(tileClicked+7) != board.end())
		{
			if(board.at(tileClicked+7).get()->getColor() != color)
			{
				redBox = {xCoord-100, yCoord+85, 100, 100};
				SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
				validBox.insert(make_pair(tileClicked+7, make_pair(xCoord-100, yCoord+100)));				
			}
		}
		if(board.find(tileClicked+9) != board.end())
		{
			if(board.at(tileClicked+9).get()->getColor() != color)
			{
				redBox = {xCoord+100, yCoord+85, 100, 100};
				SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
				validBox.insert(make_pair(tileClicked+9, make_pair(xCoord+100, yCoord+100)));				
			}
		}	
	}

	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(currentImage);
	return true;
}

bool pawn::validMove(int newTileClicked)
{
	if(validBox.find(newTileClicked) == validBox.end())
		{return false;}
    return true;
}

void pawn::update(piece &p, int newTileClicked)
{
	p.setxCoord(validBox.at(newTileClicked).first);
	p.setyCoord(validBox.at(newTileClicked).second);
	p.setfirstMove();
	validBox.clear();
}

int pawn::check(int tile, map<int, shared_ptr<piece>> board)
{
	int moves[2];
	if(color == 'w')
		{moves[0] = tile-7; moves[1] = tile-9;}
	else if(color == 'b')
		{moves[0] = tile+7; moves[1] = tile+9;}

	for(int i = 0; i < 2; i++)
	{
		if(board.find(moves[i]) != board.end())
		{
			if(board.at(moves[i])->getIdentity() == "king" && board.at(moves[i])->getColor() != color)
				{return moves[i];}
		}
	}
	return 0;
}

bool pawn::canAttackTile(int location, int attackerTile, map<int, shared_ptr<piece>> board)
{
	int moves[4];
	if(color == 'w')
		{moves[0] = location-7; moves[1] = location-9;}
	else if(color == 'b')
		{moves[0] = location+7; moves[1] = location+9;}

	map<int, shared_ptr<piece>>::iterator it = board.find(attackerTile);
	for(int i = 0; i < 2; i++)
	{
		if(board.find(moves[i]) == it)
			{return true;}
	}
	return false;
}

#endif
