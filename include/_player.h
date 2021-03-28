#ifndef _PLAYER_H
#define _PLAYER_H

#include<_common.h>
#include<_texture.h>

#include<iostream>
#include<GL/gl.h>

using namespace std;

class _player
{
    public:
        _player();
        virtual ~_player();

        enum {STAND, WALK, RUN, JUMP};
        int actionTrigger;


        vec3 playerPos;         //player position settings
        vec3 playerScale;       //player size
        vec3 vert[4];           //rectangle around player

        void playerInit(float, float);      //initialize player - passing horizontal and vertical frames from sprite sheet
        void drawPlayer();      //rendering the player
        void actions();         //player actions

        float xMin,xMax,yMin,yMax;
        float framesX, framesY;

        _texture *plyImage = new _texture();

    protected:

    private:
};

#endif // _PLAYER_H
