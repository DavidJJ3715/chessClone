#include <thread>
#include <chrono>
#include "definitions.h"
#include "initObjects.h"

using namespace std;

int main()
{
    bool running2 = true;
    while(running2)
    {
        vector<string> PNGHolder;
        vector<shared_ptr<piece>> whiteGraveYard;
        vector<shared_ptr<piece>> blackGraveYard;
        map<int, shared_ptr<piece>> board;
        bool running = true, whiteTurn = true, blackTurn = false, multiplayer = false;

        string path = SDL_GetBasePath();

        loadPNGs(PNGHolder, path);

        if(SDL_Init(SDL_INIT_EVERYTHING) != 0) 
            {cout << "\n\nSDL_Init Failure\n\n\n";}
        if(TTF_Init() != 0) 
            {cout << "\n\nTTF_Init Failure\n\n\n"; return -1;}
        if(!IMG_Init(IMG_INIT_PNG)) 
            {cout << "\n\nIMG_Init Failure\n\n\n"; return -1;}

        SDL_Window* window = SDL_CreateWindow("Chess", 650, 75, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
            if(!window) {cout << "NO WINDOW\n"; return -1;}
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(!renderer) {cout << "NO RENDERER\n"; return -1;}
        TTF_Font* scoreFont = TTF_OpenFont("DejaVuSans.ttf", 40);
            if(!scoreFont) {cout << "NO FONT\n"; return -1;}

        int titleCheck = titleScreen(renderer, scoreFont);
        if(titleCheck < 0) 
            {running2 = false; running = false; goto cleanup;}
        else if(titleCheck == 2)
        {
            multiplayer = true;
        }
    again:
        if(SDL_RenderClear(renderer) < 0)
            {cout << "RenderClear Error\n"; goto cleanup;}
        if(!Create_Board(renderer))
            {cout << "Create_Board Error\n"; goto cleanup;}

        if(!(initPiecesMap(renderer, PNGHolder, board)))
            {cout << "initPieces Failure Map\n"; return -1;}

        while(running)
        {
            if(multiplayer && blackTurn)
            {
            /*
                Read from socket
                tileClicked = input[0]; newTileClicked = input [1];
                shared_ptr<piece> p = board.at(tileClicked);
                goto update;
            */
            }
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                    {
                        running = false;
                        running2 = false;
                        goto cleanup;
                    }
                    case SDL_KEYDOWN:
                    {
                        if(event.key.keysym.sym == SDLK_ESCAPE)
                            {running = false; running2 = false;}
                        goto cleanup;
                    }
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        switch(event.button.button)
                        {
                            case SDL_BUTTON_LEFT:
                            {
                                int initX = event.motion.x;
                                int initY = event.motion.y;
                                int tileClicked = getTile(initX, initY);
                                if(board.find(tileClicked) == board.end())
                                    {break;}
                                else
                                {
                                    shared_ptr<piece> p = board.at(tileClicked);

                                    if(whiteTurn && p.get()->getColor() == 'w') {whiteTurn = false; blackTurn = true;} 
                                    else if(blackTurn && p.get()->getColor() == 'b') {blackTurn = false; whiteTurn = true;}
                                    else {break;}

                                    int newTileClicked = select(renderer, *p.get(), tileClicked, PNGHolder.at(12), board);
                                    redrawBoard(renderer, board);
                                    if(newTileClicked == -1) 
                                    {
                                        if(p.get()->getColor() == 'w') {whiteTurn = true; blackTurn = false;}
                                        else {blackTurn = true; whiteTurn = false;}
                                        break;
                                    }

                                //update:
                                    if(board.find(newTileClicked) != board.end())
                                    {
                                        if(board.at(newTileClicked).get()->getColor() == 'b')
                                            {blackGraveYard.emplace_back(board.at(newTileClicked));}
                                        else 
                                            {whiteGraveYard.emplace_back(board.at(newTileClicked));}
                                        board.erase(newTileClicked);
                                    }
                                    p.get()->update(*p.get(), newTileClicked);
                                    board.erase(tileClicked);
                                    board.insert(make_pair(newTileClicked, p));
                                    redrawBoard(renderer, board);
                                    SDL_RenderPresent(renderer);

                                    for(auto const& [tile, cPiece] : board)
                                    {
                                        if(cPiece->getIdentity() == "king")
                                            {continue;}
                                        int val = cPiece.get()->check(tile, board);
                                        if(val > 0)
                                        {
                                            if(!isCheckMate(val, board))
                                                {cout << "\nCheck\n\n"; break;}
                                            else
                                            {
                                                if(!protect(tile, board, val))
                                                {
                                                    if(!playAgain(renderer, cPiece.get()->getColor(), scoreFont, board))
                                                        {running = false; goto cleanup;} 
                                                    else
                                                    {
                                                        board.clear();
                                                        whiteGraveYard.clear();
                                                        blackGraveYard.clear();
                                                        whiteTurn = true; blackTurn = false;
                                                        goto again;
                                                    }                                                    
                                                }
                                                cout << "\nCheck\n\n";
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            SDL_RenderPresent(renderer);
        }
        cleanup: 
            board.clear();
            PNGHolder.clear();
            whiteGraveYard.clear();
            blackGraveYard.clear();
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_CloseFont(scoreFont);
            TTF_Quit();
            SDL_Quit();
    }
    return 0;
}

/**
*   TODO: Update graveyard system
*   TODO: Label the axes
*   TODO: Settings menu
*   TODO: Play Clock
*   TODO: Pawn promotions
*   TODO: Add a second window for the graveyard
*   ?: Tile Class?
*   ?: Special piece specific rules... En passant, Castling, etc.
*   ?: Server access?
*   !: Code is cluttered and should be cleaned up
*/