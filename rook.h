#ifndef _rook_
#define _rook_
#include "piece.h"

using namespace std;

class rook : public piece
{
    public:
		rook(string, char, int, int);

		int getxCoord() override; 
		int getyCoord() override;
		bool getfirstMove();
		char getColor() override;
		string getPNG();
		string getIdentity() override;

		void setxCoord(int) override;
		void setyCoord(int) override;

		bool Draw(SDL_Renderer*);
		bool validMove(int) override;
		bool drawRedBoxes(SDL_Renderer*, string, int, map<int, shared_ptr<piece>>);
		int check(int, map<int, shared_ptr<piece>>) override;
		int checkHelper(int, int, map<int, shared_ptr<piece>>, int&);
		void update(piece&, int);
		bool canAttackTile(int, int, map<int, shared_ptr<piece>>) override;
		int attackHelper(int, int, map<int, shared_ptr<piece>>);

		void checkPathOne(SDL_Renderer*, SDL_Texture*, int, map<int, shared_ptr<piece>>, int, int);
		void checkPathTwo(SDL_Renderer*, SDL_Texture*, int, map<int, shared_ptr<piece>>, int, int);
		void checkPathThree(SDL_Renderer*, SDL_Texture*, int, map<int, shared_ptr<piece>>, int, int);
		void checkPathFour(SDL_Renderer*, SDL_Texture*, int, map<int, shared_ptr<piece>>, int, int);

    private:
    	int xCoord;
		int yCoord;
		char color;
		string png;
		string identity;
		map<int, pair<int, int>> validBox;
};

rook::rook(string pngInput, char inputColor, int x, int y)
{
    png = pngInput;
	color = inputColor;
	xCoord = x;
	yCoord = y;
	identity = "rook";
}

int rook::getxCoord()
	{return xCoord;}
int rook::getyCoord()
	{return yCoord;}
char rook::getColor()
	{return color;}
string rook::getPNG()
	{return png;}
string rook::getIdentity()
	{return identity;}
		
void rook::setxCoord(int x)
	{xCoord = x;}
void rook::setyCoord(int y)
	{yCoord = y;}

bool rook::Draw(SDL_Renderer* renderer)
{
	SDL_Texture* currentImage = IMG_LoadTexture(renderer, png.data());
    if(!currentImage) 
		{cout << "NO SPRITE" << endl; return false;}
	SDL_Rect dstrect = {xCoord, yCoord, 100, 100}; //sprite location and size				
	SDL_RenderCopy(renderer, currentImage, NULL, &dstrect);
	SDL_DestroyTexture(currentImage);
	return true;
}

void rook::checkPathOne(SDL_Renderer* renderer, SDL_Texture* redBox, int tile, map<int, shared_ptr<piece>> board, int x, int y)
{
	SDL_Rect box;
	if(tile < 1 || tile > 64) {}
	else if(tile < 9)
	{
		if(board.find(tile) == board.end()) //Hit the edge of board, but landed on an empty space so mark it
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Make sure we are not marking a piece of the same color
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	else
	{
		if(board.find(tile) == board.end()) //Tile is empty, keep going
		{
			checkPathOne(renderer, redBox, tile-8, board, x, y-100);
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Hit piece of opposing color. Can not go past
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	SDL_RenderPresent(renderer);
}

void rook::checkPathTwo(SDL_Renderer* renderer, SDL_Texture* redBox, int tile, map<int, shared_ptr<piece>> board, int x, int y)
{
	SDL_Rect box;
	if(tile < 1 || tile > 64) {}
	else if((tile+7) % 8 == 0)
	{
		if(board.find(tile) == board.end()) //Hit the edge of board, but landed on an empty space so mark it
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Make sure we are not marking a piece of the same color
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	else
	{
		if(board.find(tile) == board.end()) //Tile is empty, keep going
		{
			checkPathTwo(renderer, redBox, tile-1, board, x-100, y);
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Hit piece of opposing color. Can not go past
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	SDL_RenderPresent(renderer);
}

void rook::checkPathThree(SDL_Renderer* renderer, SDL_Texture* redBox, int tile, map<int, shared_ptr<piece>> board, int x, int y)
{
	SDL_Rect box;
	if(tile < 1 || tile > 64) {}
	else if(tile > 56)
	{
		if(board.find(tile) == board.end()) //Hit the edge of board, but landed on an empty space so mark it
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Make sure we are not marking a piece of the same color
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	else
	{
		if(board.find(tile) == board.end()) //Tile is empty, keep going
		{
			checkPathThree(renderer, redBox, tile+8, board, x, y+100);
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Hit piece of opposing color. Can not go past
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	SDL_RenderPresent(renderer);
}

void rook::checkPathFour(SDL_Renderer* renderer, SDL_Texture* redBox, int tile, map<int, shared_ptr<piece>> board, int x, int y)
{
	SDL_Rect box;
	if(tile < 1 || tile > 64) {}
	else if(tile % 8 == 0)
	{
		if(board.find(tile) == board.end()) //Hit the edge of board, but landed on an empty space so mark it
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Make sure we are not marking a piece of the same color
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	else
	{
		if(board.find(tile) == board.end()) //Tile is empty, keep going
		{
			checkPathFour(renderer, redBox, tile+1, board, x+100, y);
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Hit piece of opposing color. Can not go past
		{
			box = {x, y, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	SDL_RenderPresent(renderer);
}

bool rook::drawRedBoxes(SDL_Renderer* renderer, string Box, int tileClicked, map<int, shared_ptr<piece>> board)
{
	SDL_Texture* currentImage;
	SDL_Rect redBox;
	currentImage = IMG_LoadTexture(renderer, Box.data());
		if(!currentImage) {cout << "NO SPRITE" << endl; return false;}

	checkPathOne(renderer, currentImage, tileClicked-8, board, board.at(tileClicked).get()->getxCoord(), board.at(tileClicked).get()->getyCoord()-100);
	checkPathTwo(renderer, currentImage, tileClicked-1, board, board.at(tileClicked).get()->getxCoord()-100, board.at(tileClicked).get()->getyCoord());
	checkPathThree(renderer, currentImage, tileClicked+8, board, board.at(tileClicked).get()->getxCoord(), board.at(tileClicked).get()->getyCoord()+100);
	checkPathFour(renderer, currentImage, tileClicked+1, board, board.at(tileClicked).get()->getxCoord()+100, board.at(tileClicked).get()->getyCoord());
	
	SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(currentImage);
    return true;
}

bool rook::validMove(int newTileClicked)
{
	if(validBox.find(newTileClicked) == validBox.end())
		{return false;}
    return true;
}

void rook::update(piece &p, int newTileClicked)
{
    p.setxCoord(validBox.at(newTileClicked).first);
	p.setyCoord(validBox.at(newTileClicked).second);
	validBox.clear();
}

int rook::checkHelper(int tile, int change, map<int, shared_ptr<piece>> board, int &res)
{
	if(tile < 1 || tile > 64 || tile%8 == 0 || (tile+7)%8 == 0)
		{return 0;}
	else if(board.find(tile) != board.end())
	{
		if(board.at(tile)->getIdentity() == "king" && board.at(tile)->getColor() != color)
			{return res = tile;}
		else 
			{return 0;}
	}
	return checkHelper(tile-change, change, board, res);
}

int rook::check(int tile, map<int, shared_ptr<piece>> board)
{
	int change[4] = {-8, 8, -1, 1}, res = 0;

	for(int i = 0; i < 4; i++)
	{
		if(checkHelper(tile - change[i], change[i], board, res) > 0)
			{return res;}
	}

	return 0;
}

int rook::attackHelper(int location, int change, map<int, shared_ptr<piece>> board)
{
	if(location < 1 || location > 64 || location%8 == 0 || (location+7)%8 == 0)
		{return 0;}
	else if(board.find(location) != board.end())
		{return location;}
	return attackHelper(location-change, change, board);
}

bool rook::canAttackTile(int location, int attackerTile, map<int, shared_ptr<piece>> board)
{
	int change[4] = {-8, 8, -1, 1};

	for(int i = 0; i < 4; i++)
	{
		if(attackHelper(location-change[i], change[i], board) == attackerTile)
			{return true;}
	}

	return false;
}

#endif