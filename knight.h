#ifndef _knight_
#define _knight_
#include "piece.h"

using namespace std;

class knight : public piece
{
    public:
		knight(string, char, int, int);

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
		void update(piece&, int);
		bool canAttackTile(int, int, map<int, shared_ptr<piece>>) override;

    private:
    	int xCoord;
		int yCoord;
		char color;
		string png;
		string identity;
		map<int, pair<int,int>> validBox;
};

knight::knight(string pngInput, char inputColor, int x, int y)
{
    png = pngInput;
	color = inputColor;
	xCoord = x;
	yCoord = y;
	identity = "knight";
}

int knight::getxCoord()
	{return xCoord;}
int knight::getyCoord()
	{return yCoord;}
char knight::getColor()
	{return color;}
string knight::getPNG()
	{return png;}
string knight::getIdentity()
	{return identity;}
		
void knight::setxCoord(int x)
	{xCoord = x;}
void knight::setyCoord(int y)
	{yCoord = y;}

bool knight::Draw(SDL_Renderer* renderer)
{
	SDL_Texture* currentImage = IMG_LoadTexture(renderer, png.data());
    if(!currentImage) 
		{cout << "NO SPRITE" << endl; return false;}
	SDL_Rect dstrect = {xCoord, yCoord, 100, 100}; //sprite location and size				
	SDL_RenderCopy(renderer, currentImage, NULL, &dstrect);
	SDL_DestroyTexture(currentImage);
	return true;
}

bool knight::drawRedBoxes(SDL_Renderer* renderer, string Box, int tileClicked, map<int, shared_ptr<piece>> board)
{
	SDL_Texture* currentImage;
	SDL_Rect redBox;
	currentImage = IMG_LoadTexture(renderer, Box.data());
		if(!currentImage) {cout << "NO SPRITE" << endl; return false;}

	if(board.find(tileClicked-10) == board.end())
	{
		redBox = {xCoord-200, yCoord-100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked-10, (make_pair(xCoord-200, yCoord-100))));
	}
	else
	{
		if(board.at(tileClicked-10).get()->getColor() != color)
		{
			redBox = {xCoord-200, yCoord-100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-10, (make_pair(xCoord-200, yCoord-100))));
		}
	}
	if(board.find(tileClicked+10) == board.end())
	{
		redBox = {xCoord+200, yCoord+100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked+10, (make_pair(xCoord+200, yCoord+100))));
	}
	else
	{
		if(board.at(tileClicked+10).get()->getColor() != color)
		{
			redBox = {xCoord+200, yCoord+100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+10, (make_pair(xCoord+200, yCoord+100))));
		}
	}
	if(board.find(tileClicked-6) == board.end())
	{
		redBox = {xCoord+200, yCoord-100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked-6, (make_pair(xCoord+200, yCoord-100))));
	}
	else
	{
		if(board.at(tileClicked-6).get()->getColor() != color)
		{
			redBox = {xCoord+200, yCoord-100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-6, (make_pair(xCoord+200, yCoord-100))));
		}
	}
	if(board.find(tileClicked+6) == board.end())
	{
		redBox = {xCoord-200, yCoord+100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked+6, (make_pair(xCoord-200, yCoord+100))));
	}
	else
	{
		if(board.at(tileClicked+6).get()->getColor() != color)
		{
			redBox = {xCoord-200, yCoord+100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+6, (make_pair(xCoord-200, yCoord+100))));	
		}
	}
	if(board.find(tileClicked-17) == board.end())
	{
		redBox = {xCoord-100, yCoord-200, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked-17, (make_pair(xCoord-100, yCoord-200))));
	}
	else
	{
		if(board.at(tileClicked-17).get()->getColor() != color)
		{
			redBox = {xCoord-100, yCoord-200, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-17, (make_pair(xCoord-100, yCoord-200))));
		}
	}
	if(board.find(tileClicked+17) == board.end())
	{
		redBox = {xCoord+100, yCoord+200, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked+17, (make_pair(xCoord+100, yCoord+200))));
	}
	else
	{
		if(board.at(tileClicked+17).get()->getColor() != color)
		{
			redBox = {xCoord+100, yCoord+200, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+17, (make_pair(xCoord+100, yCoord+200))));
		}
	}
	if(board.find(tileClicked-15) == board.end())
	{
		redBox = {xCoord+100, yCoord-200, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked-15, (make_pair(xCoord+100, yCoord-200))));
	}
	else
	{
		if(board.at(tileClicked-15).get()->getColor() != color)
		{
			redBox = {xCoord+100, yCoord-200, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-15, (make_pair(xCoord+100, yCoord-200))));	
		}
	}
	if(board.find(tileClicked+15) == board.end())
	{
		redBox = {xCoord-100, yCoord+200, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked+15, (make_pair(xCoord-100, yCoord+200))));
	}
	else
	{
		if(board.at(tileClicked+15).get()->getColor() != color)
		{
			redBox = {xCoord-100, yCoord+200, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+15, (make_pair(xCoord-100, yCoord+200))));
		}
	}
	
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(currentImage);
    return true;
}

bool knight::validMove(int newTileClicked)
{
	if(validBox.find(newTileClicked) == validBox.end())
		{return false;}
    return true;
}

void knight::update(piece &p, int newTileClicked)
{
	p.setxCoord(validBox.at(newTileClicked).first);
	p.setyCoord(validBox.at(newTileClicked).second);
	validBox.clear();
}

int knight::check(int tile, map<int, shared_ptr<piece>> board)
{
	int moves[8] = {tile-6, tile+6, tile-10, tile+10, tile-15, tile+15, tile-17, tile+17};
	for(int i = 0; i < 8; i++)
	{
		if(board.find(moves[i]) != board.end())
		{
			if(board.at(moves[i])->getIdentity() == "king" && board.at(moves[i])->getColor() != color)
				{return moves[i];}
		}
	}
	return 0;
}

bool knight::canAttackTile(int location, int attackerTile, map<int, shared_ptr<piece>> board)
{
	int moves[8] = {location-6, location+6, location-10, location+10, location-15, location+15, location-17, location+17};

	map<int, shared_ptr<piece>>::iterator it = board.find(attackerTile);
	for(int i = 0; i < 8; i++)
	{
		if(board.find(moves[i]) == it)
			{return true;}
	}
	return false;
}

#endif