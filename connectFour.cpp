//Matt Peebles
//October 21, 2017
//Connect Four

#include <Arduboy.h>
Arduboy arduboy;

const unsigned char board[] PROGMEM = {
0x00, 0x00, 0xfc, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xfc, 0x00, 0x00,
0x00, 0x00, 0x3f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3f, 0x00, 0x00,
};

const unsigned char transpiece[] PROGMEM = {
	0x00, 0x00, 0xfc, 0x04, 0xc4, 0x24, 0x14, 0x14, 0x14, 0x14, 0x24, 0xc4, 0x04, 0xfc, 0x00, 0x00,
	0x00, 0x00, 0x3f, 0x20, 0x23, 0x24, 0x28, 0x28, 0x28, 0x28, 0x24, 0x23, 0x20, 0x3f, 0x00, 0x00,

};

const unsigned char solidpiece[] PROGMEM = {
	0x00, 0x00, 0xfc, 0x04, 0xc4, 0xe4, 0xf4, 0xf4, 0xf4, 0xf4, 0xe4, 0xc4, 0x04, 0xfc, 0x00, 0x00,
	0x00, 0x00, 0x3f, 0x20, 0x23, 0x27, 0x2f, 0x2f, 0x2f, 0x2f, 0x27, 0x23, 0x20, 0x3f, 0x00, 0x00,
}

void drawBoard(){
  for(int backgroundx = 0, num = 0; backgroundx<128, num < 7; backgroundx = backgroundx + 12, ++num){
      for( int backgroundy = 0, num=0; backgroundy < 64, num < 5; backgroundy = backgroundy + 12, ++num) {
        arduboy.drawBitmap(backgroundx,backgroundy,board,16,16, WHITE);
    }
  }
}

int piecex = 0;
int piecey = 0;
int lateralbuffer = 0; 
int player = 2;
int token = transpiece;

void drawPiece(){
	
	if(player == 1){
		token = transpiece;
	}else{
		token = solidpiece;
	}

	if(arduboy.pressed(LEFT_BUTTON)  && lateralbuffer == 0) {
	    piecex = piecex - 12;

	    if(piecex < 0){
	    	piecex = 0;
	    }

	    lateralbuffer = 1;
	}
	if(arduboy.pressed(RIGHT_BUTTON) && lateralbuffer == 0) {
	    piecex = piecex + 12;

	    if(piecex > 72){
	    	piecex = 72;
	    }

	    lateralbuffer = 1;
	}

	if(!arduboy.pressed(RIGHT_BUTTON) && !arduboy.pressed(LEFT_BUTTON)){
		lateralbuffer = 0;
	}

 	arduboy.drawBitmap(piecex,piecey, token,16,16, WHITE);
}

void setup(){
  arduboy.begin();
  arduboy.clear();
}



void loop(){
  arduboy.clear();
  drawBoard();
  drawPiece();
  arduboy.display();
}