#ifndef _king_
#define _king_
#include "piece.h"

using namespace std;

class king : public piece
{
    public:
		king(string, char, int, int);

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

	private: 
		int xCoord;
		int yCoord;
		char color;
		string png;
		string identity;
		map<int, pair<int, int>> validBox;
};

king::king(string pngInput, char inputColor, int x, int y)
{
    png = pngInput;
	color = inputColor;
	xCoord = x;
	yCoord = y;
	identity = "king";
}

int king::getxCoord()
	{return xCoord;}
int king::getyCoord()
	{return yCoord;}
char king::getColor()
	{return color;}
string king::getPNG()
	{return png;}
string king::getIdentity()
	{return identity;}
		
void king::setxCoord(int x)
	{xCoord = x;}
void king::setyCoord(int y)
	{yCoord = y;}

bool king::Draw(SDL_Renderer* renderer)
{
	SDL_Texture* currentImage = IMG_LoadTexture(renderer, png.data());
    if(!currentImage) 
		{cout << "NO SPRITE" << endl; return false;}
	SDL_Rect dstrect = {xCoord, yCoord, 100, 100}; //sprite location and size				
	SDL_RenderCopy(renderer, currentImage, NULL, &dstrect);
	SDL_DestroyTexture(currentImage);
	return true;
}

bool king::drawRedBoxes(SDL_Renderer* renderer, string Box, int tileClicked, map<int, shared_ptr<piece>> board)
{
	SDL_Texture* currentImage;
	SDL_Rect redBox;
	currentImage = IMG_LoadTexture(renderer, Box.data());
		if(!currentImage) {cout << "NO SPRITE" << endl; return false;}
	
//Check Front and Back
	if(board.find(tileClicked-8) == board.end())
	{
		redBox = {xCoord, yCoord-100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked-8, (make_pair(xCoord, yCoord-100))));
	}
	else
	{
		if(board.at(tileClicked-8).get()->getColor() != color)
		{
			redBox = {xCoord, yCoord-100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-8, (make_pair(xCoord, yCoord-100))));
		}
	}
	if(board.find(tileClicked+8) == board.end())
	{
		redBox = {xCoord, yCoord+100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked+8, (make_pair(xCoord, yCoord+100))));
	}
	else
	{
		if(board.at(tileClicked+8).get()->getColor() != color)
		{
			redBox = {xCoord, yCoord+100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+8, (make_pair(xCoord, yCoord+100))));
		}
	}

//Check Both Sides
	if(board.find(tileClicked-1) == board.end())
	{
		redBox = {xCoord-100, yCoord, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked-1, (make_pair(xCoord-100, yCoord))));
	}
	else
	{
		if(board.at(tileClicked-1).get()->getColor() != color)
		{
			redBox = {xCoord-100, yCoord, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-1, (make_pair(xCoord-100, yCoord))));
		}
	}
	if(board.find(tileClicked+1) == board.end())
	{
		redBox = {xCoord+100, yCoord, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked+1, (make_pair(xCoord+100, yCoord))));
	}
	else
	{
		if(board.at(tileClicked+1).get()->getColor() != color)
		{
			redBox = {xCoord+100, yCoord, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+1, (make_pair(xCoord+100, yCoord))));
		}
	}

//Check All 4 Diagonals
	if(board.find(tileClicked-7) == board.end())
	{
		redBox = {xCoord+100, yCoord-100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked-7, (make_pair(xCoord+100, yCoord-100))));
	}
	else
	{
		if(board.at(tileClicked-7).get()->getColor() != color)
		{
			redBox = {xCoord+100, yCoord-100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-7, (make_pair(xCoord+100, yCoord-100))));
		}
	}
	if(board.find(tileClicked-9) == board.end())
	{
		redBox = {xCoord-100, yCoord-100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked-9, (make_pair(xCoord-100, yCoord-100))));
	}
	else
	{
		if(board.at(tileClicked-9).get()->getColor() != color)
		{
			redBox = {xCoord-100, yCoord-100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked-9, (make_pair(xCoord-100, yCoord-100))));
		}
	}
	if(board.find(tileClicked+7) == board.end())
	{
		redBox = {xCoord-100, yCoord+100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked+7, (make_pair(xCoord-100, yCoord+100))));
	}
	else
	{
		if(board.at(tileClicked+7).get()->getColor() != color)
		{
			redBox = {xCoord-100, yCoord+100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+7, (make_pair(xCoord-100, yCoord+100))));
		}
	}
	if(board.find(tileClicked+9) == board.end())
	{
		redBox = {xCoord+100, yCoord+100, 100, 100};
		SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
		validBox.insert(make_pair(tileClicked+9, (make_pair(xCoord+100, yCoord+100))));
	}
	else
	{
		if(board.at(tileClicked+9).get()->getColor() != color)
		{
			redBox = {xCoord+100, yCoord+100, 100, 100};
			SDL_RenderCopy(renderer, currentImage, NULL, &redBox);
			validBox.insert(make_pair(tileClicked+9, (make_pair(xCoord+100, yCoord+100))));
		}
	}

	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(currentImage);
    return true;
}

bool king::validMove(int newTileClicked)
{
	if(validBox.find(newTileClicked) == validBox.end())
		{return false;}
    return true;
}

void king::update(piece &p, int newTileClicked)
{
	p.setxCoord(validBox.at(newTileClicked).first);
	p.setyCoord(validBox.at(newTileClicked).second);
	validBox.clear();
}

int king::check(int tile, map<int, shared_ptr<piece>> board)
{
	if(tile < 1 || tile > 64)
		{return 0;}
	else if(board.find(tile) == board.end())
		{return tile;}
	else if(board.find(tile) != board.end())
	{
		if(board.at(tile).get()->getColor() != color)
			{return tile;}
	}

	return 0;
}

#endif