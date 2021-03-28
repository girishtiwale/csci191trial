#ifndef _INPUT_H
#define _INPUT_H

#include<windows.h>
#include<_model.h>
#include<_parallax.h>
#include<_player.h>

class _input
{
    public:
        _input();
        virtual ~_input();

        void keyPressed(_model*);       //kick off when the key is pressed
        void keyPressed(_player*);

        void moveEnv(_parallax *,float);
        void keyUp(_player*);
        void keyUp();


        void mouseDown(_model*,float,float);
        void mouseUp();
        void mouseWheel(_model*,float);
        void mouseMove(_model*,float,float);

        float prevMouseX;
        float prevMouseY;
        bool mouseTranslation;
        bool mouseRotate;

        WPARAM wParam;

    protected:

    private:
};

#endif // _INPUT_H
