#include "Game.hpp"

Game::Game(Player* p1, Player* p2){
    players.first=p1;
    players.second=p2;
    p1->isWhite=true;
    p2->isWhite=false;
    currPlayer=p1;

    board= new Board();
    p1->setCurrGame(this);
    p2->setCurrGame(this);
    board->displayBoard();

    status=GAME_STATUS::ACTIVE;
    
    initialise();
}

void Game::initialise(){  
    while(status==GAME_STATUS::ACTIVE){
        string strPos,endPos;
        cout<<"Enter Start Position: ";
        cin>>strPos;
        cout<<endl;
        cout<<"Enter End Position: ";
        cin>>endPos;
        cout<<endl;
        processMove(strPos,endPos);
    }
}

Board *Game::getBoard(){ return board;}

void Game::switchTurn(){
    if(currPlayer==players.first) currPlayer=players.second;
    else currPlayer=players.second;
}

void Game::unDo(){
    if (movesPlayed.empty()) {
        cout << "No moves to undo!" << endl;
        return;
    }

    Move* lastMove = movesPlayed.back();
    movesPlayed.pop_back();

    Spot* startSpot = lastMove->strPos;
    Spot* endSpot = lastMove->endPos;
    Piece* movedPiece = endSpot->getPiece();

    // Undo the move
    startSpot->setPiece(movedPiece);
    endSpot->setPiece(nullptr);

    // Handle castling undo
    if (movedPiece->getSymbol() == "King" && abs(startSpot->getX() - endSpot->getX()) == 2) {
        // Castling detected
        int rookStartX = (endSpot->getX() > startSpot->getX()) ? 7 : 0; // Determine rook's original position
        int rookEndX = (endSpot->getX() > startSpot->getX()) ? 5 : 3; // Determine rook's new position
        Spot* rookStartSpot = board->getSpot(startSpot->getY(), rookStartX);
        Spot* rookEndSpot = board->getSpot(startSpot->getY(), rookEndX);

        // Move the rook back to its original position
        rookStartSpot->setPiece(rookEndSpot->getPiece());
        rookEndSpot->setPiece(nullptr);
    }

    // Restore the captured piece if any
    if (lastMove->endPiece != nullptr) {
        endSpot->setPiece(lastMove->endPiece);
    }

    // Switch turn back
    switchTurn();

    delete lastMove;
    board->displayBoard();
}

void Game::processMove(string strPos, string endPos) {
    Spot* strSpot = board->getSpot(strPos);
    Spot* endSpot = board->getSpot(endPos);

    // Check if the start and end spots are valid
    if (!strSpot || !endSpot) {
        cout << "Invalid position entered. Please try again." << endl;
        return;
    }

    // Check if there is a piece on the start spot
    if (!strSpot->getPiece()) {
        cout << "No piece at the start position. Please try again." << endl;
        return;
    }

    // Check if the piece can move to the end spot
    if (strSpot->getPiece()->canMove(board, strSpot, endSpot)) {
        strSpot->getPiece()->move(board, strSpot, endSpot);
        Move* move = new Move(strSpot, endSpot, currPlayer);
        movesPlayed.emplace_back(move);
        board->displayBoard();
        switchTurn();
    } else {
        cout << "Invalid move. Please try again." << endl;
    }
}
