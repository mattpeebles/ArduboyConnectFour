//Matt Peebles
//October 21, 2017
//Connect Four

#include <Arduboy.h>
Arduboy arduboy;

const unsigned char boardpiece[] PROGMEM = {
0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 
};

const unsigned char transpiece[] PROGMEM = {
0xff, 0x99, 0xa5, 0xc3, 0xc3, 0xa5, 0x99, 0xff,
};

const unsigned char solidpiece[] PROGMEM = {
0xff, 0x99, 0xbd, 0xff, 0xff, 0xbd, 0x99, 0xff, 
};

int piecex = 0;
int piecey = 10;
int lateralbuffer = 0;
int abuffer = 0;
int player = 2;
int token = transpiece;
int currentcol = 0;
bool winstate = false;
int currentplayer = 1;
char board[7][6] = {
  {'_', '_', '_', '_', '_', '_'},
  {'_', '_', '_', '_', '_', '_'},
  {'_', '_', '_', '_', '_', '_'},
  {'_', '_', '_', '_', '_', '_'},
  {'_', '_', '_', '_', '_', '_'},
  {'_', '_', '_', '_', '_', '_'},
  {'_', '_', '_', '_', '_', '_'}
};

void drawBoard(){
  for(int backgroundx = 0, col=0; backgroundx<128, col < 7; backgroundx = backgroundx + 8, ++col){
      for( int backgroundy = 10, row=0; backgroundy < 74, row < 6; backgroundy = backgroundy + 8, ++row) {
        if(board[col][row] == 'O'){
          arduboy.drawBitmap(backgroundx,backgroundy, transpiece, 8, 8, WHITE);
        }
      else if(board[col][row] == 'X'){
          arduboy.drawBitmap(backgroundx,backgroundy, solidpiece, 8, 8, WHITE);
        }

        else {
          arduboy.drawBitmap(backgroundx,backgroundy, boardpiece, 8, 8, WHITE);
        }
    }
  }
}

void drawInfo(){
  arduboy.setCursor(25, 0);
  arduboy.print("Connect Four");
  arduboy.setCursor(72, 10);
  arduboy.print("Player ");
  arduboy.print(currentplayer);
}

void drawPiece(){
  
  if(currentplayer == 1){
    token = transpiece;
  }else{
    token = solidpiece;
  }

  if(arduboy.pressed(LEFT_BUTTON)  && lateralbuffer == 0 && currentcol > 0) {
      piecex = piecex - 8;
      --currentcol;
      lateralbuffer = 1;
  }
  if(arduboy.pressed(RIGHT_BUTTON) && lateralbuffer == 0 && currentcol < 6) {
      piecex = piecex + 8;
      ++currentcol;
      lateralbuffer = 1;
  }

  if(!arduboy.pressed(RIGHT_BUTTON) && !arduboy.pressed(LEFT_BUTTON)){
    lateralbuffer = 0;
  }

  arduboy.drawBitmap(piecex,piecey, token,8,8, WHITE);
}

void placePiece(){
  for( int i = 5; i >= 0; i--){
    if(board[currentcol][i] == '_' && currentplayer == 1){
      board[currentcol][i] = 'O';
      return;
    }
    else if(board[currentcol][i] == '_' && currentplayer == 2){
      board[currentcol][i] = 'X';
      return;
    }
  }
}

void play(){
  if(arduboy.pressed(A_BUTTON) && abuffer == 0){
    placePiece();
    drawBoard();
    abuffer = 1;

    if(currentplayer == 1){
      currentplayer = 2;
    } else{
      currentplayer = 1;
    }
  }
  if(!arduboy.pressed(A_BUTTON)){
    abuffer = 0;
  }
}

void setup(){
  arduboy.begin();
  arduboy.clear();
}



void loop(){
  arduboy.clear();
  drawBoard();
  drawPiece();
  drawInfo();
  play();
  arduboy.display();
}