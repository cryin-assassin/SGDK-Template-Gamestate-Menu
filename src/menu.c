#include <menu.h>
#include <gamestate.h>
#include <genesis.h>
#include <resources.h>


u8 currentIndex = 0;
Sprite *cursor;


typedef struct
{
    u16 x;
    u16 y;
    char label[10];
} Option;

#define NUM_OPTIONS 3
Option options[NUM_OPTIONS] = {
    {8, 8, "START"},
    {8, 9, "OPTIONS"},
    {8, 10, "EXIT"},
};

void updateCursorPosition(){
    SPR_setPosition(cursor, options[currentIndex].x*8-12, options[currentIndex].y*8);
}

void moveUp(){
    if(currentIndex > 0){
        currentIndex--;
        updateCursorPosition();
    }
}

void moveDown(){
    if(currentIndex < NUM_OPTIONS-1){
        currentIndex++;
        updateCursorPosition();
    }
}

void pickStart(){
    VDP_clearText(8, 12, 20);
    VDP_drawText("Picked Start", 8, 12);
}

void pickOptions(){
    VDP_clearText(8, 12, 20);
    VDP_drawText("Picked Options", 8, 12);
}

void pickExit(){
    VDP_clearText(8, 12, 20);
    VDP_drawText("Picked Exit", 8, 12);
}

void select(u16 Option){
    switch (Option)
    {
    case 0:{
        pickStart();
        break;
    }
    case 1:{
        pickOptions();
        break;
    }
    case 2:{
        pickExit();
        break;
    }
    
    default:
        break;
    }
}

void joyEventHandler(u16 joy, u16 changed, u16 state){
    if (changed & state & BUTTON_UP)
    {
        moveUp();
    }
    else if(changed & state & BUTTON_DOWN){
        moveDown();
    }
    if(changed & state & BUTTON_START){
    select(currentIndex);
}
}

void drawMenuScreen(){
    //Draw options
    u16 i = 0;
    for(i; i < NUM_OPTIONS; i++){
        Option o = options[i];
        VDP_drawText(o.label,o.x,o.y);
    }
    
    SPR_init();
    cursor = SPR_addSprite(&gfx_cursor, 0, 0, 0);
    updateCursorPosition();
    JOY_init();
    JOY_setEventHandler(&joyEventHandler);
}

// void destroyScreen(){

// }

void processStateMenu(){    
    //Init
    drawMenuScreen();

    //Update
    while(currentState == STATE_MENU){
        SPR_update();
        SYS_doVBlankProcess();      
    }

    // destroyScreen();

}


