#ifndef _ENEMIES_H
#define _ENEMIES_H

#include<_common.h>
#include<_timer.h>
#include<GL/gl.h>


class _enemies
{
    public:
        _enemies();
        virtual ~_enemies();

        void drawEnms();        //render
        void placeEnms(vec3);   //placements
        void actionsEnms();     //movements

        vec3 posE;              //position of enemies
        vec2 sizeE;             //size of enemies
        vec3 rotateE;           //rotate the enemies

        int numberOfFrames;
        int actions;            //action trigger
        float speed;

        _timer *eT = new _timer();  //keep animations in one speed

        GLuint tex;
        bool isAlive = true;


    protected:

    private:
        float xMax,yMax,xMin,yMin;
};

#endif // _ENEMIES_H
