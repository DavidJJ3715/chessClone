#ifndef _bishop_
#define _bishop_
#include "piece.h"

using namespace std;

class bishop : public piece
{
    public:
		bishop(string, char, int, int);

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

		void checkDiagOne(SDL_Renderer*, SDL_Texture*, int, map<int, shared_ptr<piece>>, int, int);
		void checkDiagTwo(SDL_Renderer*, SDL_Texture*, int, map<int, shared_ptr<piece>>, int, int);
		void checkDiagThree(SDL_Renderer*, SDL_Texture*, int, map<int, shared_ptr<piece>>, int, int);
		void checkDiagFour(SDL_Renderer*, SDL_Texture*, int, map<int, shared_ptr<piece>>, int, int);

    private:
    	int xCoord;
		int yCoord;
		char color;
		string png;
		string identity;
		map<int, pair<int,int>> validBox;
};

bishop::bishop(string pngInput, char inputColor, int x, int y)
{
    png = pngInput;
	color = inputColor;
	xCoord = x;
	yCoord = y;
	identity = "bishop";
}

int bishop::getxCoord()
	{return xCoord;}
int bishop::getyCoord()
	{return yCoord;}
char bishop::getColor()
	{return color;}
string bishop::getPNG()
	{return png;}
string bishop::getIdentity()
	{return identity;}
		
void bishop::setxCoord(int x)
	{xCoord = x;}
void bishop::setyCoord(int y)
	{yCoord = y;}

bool bishop::Draw(SDL_Renderer* renderer)
{
	SDL_Texture* currentImage = IMG_LoadTexture(renderer, png.data());
    if(!currentImage) 
		{cout << "NO SPRITE" << endl; return false;}
	SDL_Rect dstrect = {xCoord, yCoord, 100, 100}; //sprite location and size				
	SDL_RenderCopy(renderer, currentImage, NULL, &dstrect);
	SDL_DestroyTexture(currentImage);
	return true;
}

void bishop::checkDiagOne(SDL_Renderer* renderer, SDL_Texture* redBox, int tile, map<int, shared_ptr<piece>> board, int x, int y)
{
	SDL_Rect box;
	if(tile < 1 || tile > 64) {}
	else if(tile % 8 == 0) //Right edge of the board, cannot keep going
	{
		if(board.find(tile) == board.end()) //Hit the edge of board, but landed on an empty space so mark it
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Make sure we are not marking a piece of the same color
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	else
	{
		if(board.find(tile) == board.end()) //Tile is empty, keep going
		{
			checkDiagOne(renderer, redBox, tile-7, board, x+100, y-100);
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Hit piece of opposing color. Can not go past
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	SDL_RenderPresent(renderer);
}

void bishop::checkDiagTwo(SDL_Renderer* renderer, SDL_Texture* redBox, int tile, map<int, shared_ptr<piece>> board, int x, int y)
{
	SDL_Rect box;
	if(tile < 1 || tile > 64) {}
	else if((tile+7) % 8 == 0) //Left edge of the board, cannot keep going
	{
		if(board.find(tile) == board.end()) //Hit the edge of board, but landed on an empty space so mark it
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Make sure we are not marking a piece of the same color
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	else
	{
		if(board.find(tile) == board.end()) //Tile is empty, keep going
		{
			checkDiagTwo(renderer, redBox, tile-9, board, x-100, y-100);
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Hit piece of opposing color. Can not go past
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	SDL_RenderPresent(renderer);
}

void bishop::checkDiagThree(SDL_Renderer* renderer, SDL_Texture* redBox, int tile, map<int, shared_ptr<piece>> board, int x, int y)
{
	SDL_Rect box;
	if(tile < 1 || tile > 64) {} //Out of bounds
	else if((tile+7) % 8 == 0) //Left edge of the board, cannot keep going
	{
		if(board.find(tile) == board.end()) //Hit the edge of board, but landed on an empty space so mark it
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Make sure we are not marking a piece of the same color
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	else
	{
		if(board.find(tile) == board.end()) //Tile is empty, keep going
		{
			checkDiagThree(renderer, redBox, tile+7, board, x-100, y+100);
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Hit piece of opposing color. Can not go past
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	SDL_RenderPresent(renderer);
}

void bishop::checkDiagFour(SDL_Renderer* renderer, SDL_Texture* redBox, int tile, map<int, shared_ptr<piece>> board, int x, int y)
{
	SDL_Rect box;
	if(tile < 1 || tile > 64) {}
	else if(tile % 8 == 0) //Right edge of the board, cannot keep going
	{
		if(board.find(tile) == board.end()) //Hit the edge of board, but landed on an empty space so mark it
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Make sure we are not marking a piece of the same color
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	else
	{
		if(board.find(tile) == board.end()) //Tile is empty, keep going
		{
			checkDiagFour(renderer, redBox, tile+9, board, x+100, y+100);
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
		else if(board.at(tile).get()->getColor() != color) //Hit piece of opposing color. Can not go past
		{
			box = {x, y-15, 100, 100};
			SDL_RenderCopy(renderer, redBox, NULL, &box);
			validBox.insert(make_pair(tile, (make_pair(x, y))));
		}
	}
	SDL_RenderPresent(renderer);
}

bool bishop::drawRedBoxes(SDL_Renderer* renderer, string Box, int tileClicked, map<int, shared_ptr<piece>> board)
{
	SDL_Texture* currentImage;
	currentImage = IMG_LoadTexture(renderer, Box.data());
		if(!currentImage) {cout << "NO SPRITE" << endl; return false;}

	checkDiagOne(renderer, currentImage, tileClicked-7, board, board.at(tileClicked).get()->getxCoord()+100, board.at(tileClicked).get()->getyCoord()-100);
	checkDiagTwo(renderer, currentImage, tileClicked-9, board, board.at(tileClicked).get()->getxCoord()-100, board.at(tileClicked).get()->getyCoord()-100);
	checkDiagThree(renderer, currentImage, tileClicked+7, board, board.at(tileClicked).get()->getxCoord()-100, board.at(tileClicked).get()->getyCoord()+100);
	checkDiagFour(renderer, currentImage, tileClicked+9, board, board.at(tileClicked).get()->getxCoord()+100, board.at(tileClicked).get()->getyCoord()+100);

	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(currentImage);
    return true;
}

bool bishop::validMove(int newTileClicked)
{
	if(validBox.find(newTileClicked) == validBox.end())
		{return false;}
    return true;
}

void bishop::update(piece &p, int newTileClicked)
{
    p.setxCoord(validBox.at(newTileClicked).first);
	p.setyCoord(validBox.at(newTileClicked).second);
	validBox.clear();
}

int bishop::checkHelper(int tile, int change, map<int, shared_ptr<piece>> board, int &res)
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

int bishop::check(int tile, map<int, shared_ptr<piece>> board)
{
	int change[4] = {-7, 7, -9, 9}, res = 0;

	for(int i = 0; i < 4; i++)
	{
		if(checkHelper(tile - change[i], change[i], board, res) > 0)
			{return res;}
	}

	return 0;
}

int bishop::attackHelper(int location, int change, map<int, shared_ptr<piece>> board)
{
	if(location < 1 || location > 64 || location%8 == 0 || (location+7)%8 == 0)
		{return 0;}
	else if(board.find(location) != board.end())
		{return location;}
	return attackHelper(location-change, change, board);
}

bool bishop::canAttackTile(int location, int attackerTile, map<int, shared_ptr<piece>> board)
{
	int change[4] = {-7, 7, -9, 9};

	for(int i = 0; i < 4; i++)
	{
		if(attackHelper(location - change[i], change[i], board) == attackerTile)
			{return true;}
	}
	return false;
}

#endif