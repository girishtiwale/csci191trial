#include "_glScene.h"
#include "_glLight.h"
#include <SOIL.h>


_glScene::_glScene()
{
    //ctor
}

_glScene::~_glScene()
{
    //dtor
}
GLint _glScene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL);

    _glLight myLight(GL_LIGHT0);
    modelTex->loadTexture("images/unnamed.jpg");
    background->parallaxInit("images/3_16.png");
    background1->parallaxInit("images/parallax8.png");

    timer->startTimer();
    myPly->playerInit(8,1);
    myPly->plyImage->loadTexture("images/playerAnimated2.png");

    texEnms->loadTexture("images/playerAnimated.png");
    for(int i=0;i<20;i++)
    {
        enms[i].tex=texEnms->tex;
        enms[i].posE.x = (float)rand()/float(RAND_MAX)*5-2.5;
        enms[i].posE.y = 0.0;

        enms[i].placeEnms(enms[i].posE);
        enms[i].sizeE.y = enms[i].sizeE.x = (float)(rand()%12)/30.0;
        enms[i].sizeE.x = (float)(rand()%12)/30.0;

    }

    return true;
}

GLint _glScene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,0.2f,0.2f,0.3f);
    glLoadIdentity();


    glPushMatrix();
    glScalef(3.33,3.33,1.0);
    glBindTexture(GL_TEXTURE_2D,background->plxTexture->tex);
    //background->renderBack(screenWidth,screenHeight);
    glPopMatrix();

    glPushMatrix();
    glScalef(3.33,1.33,1.0);
    glBindTexture(GL_TEXTURE_2D,background1->plxTexture->tex);
    //background1->renderBack(screenWidth,screenHeight);
    glPopMatrix();

    //background->scroll(false,"left",0.003);

    glTranslated(0,0,-8.0);     //Place in the screen
    glColor3f(1.0,0.3,0.2);     //set a color to the object
    glBindTexture(GL_TEXTURE_2D,modelTex->tex);
    modelTeapot->drawModel();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,myPly->plyImage->tex);
    myPly->drawPlayer();
    if(timer->getTicks() > 150)
    {
        myPly->actions();

        timer->resetTime();
    }
    /*
    myPly->actions();
    if(timer->getTicks() > 150)
    {
        timer->resetTime();
    }
    */

    glPopMatrix();

    for(int i=0;i<20;i++)
    {
        if(enms[i].posE.x < -2.0)
        {
            enms[i].actions = 0;
            enms[i].speed = 0.001;
        }
        else if(enms[i].posE.x > 2.0)
        {
            enms[i].actions = 1;
            enms[i].speed = -0.001;
        }

        enms[i].posE.x += enms[i].speed;
        enms[i].actionsEnms();
        enms[i].drawEnms();
    }
}

void _glScene::resizeGLScene(int width, int height)
{
    screenWidth = width, screenHeight = height;
    float aspectRatio = (float)width/(float)height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100);
    //glOrtho((-1.0/2),(1.0/2),(-1.0/2),(1.0/2),0.1,1000);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
int _glScene::winMsg(HWND	hWnd,			        // Handle For This Window
                     UINT	uMsg,			// Message For This Window
					 WPARAM	wParam,			// Additional Message Information
					 LPARAM	lParam)
{
    kbMs->wParam = wParam;
    switch (uMsg)									// Check For Windows Messages
	{
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
		    kbMs->keyPressed(modelTeapot);
		    // to move background
		    kbMs->moveEnv(background,0.005);
		    kbMs->keyPressed(myPly);
			break;								// Jump Back
		}
		case WM_KEYUP:								// Has A Key Been Released?
		{
		    kbMs->wParam = wParam;
		    kbMs->keyUp();
            kbMs->keyUp(myPly);
			break;								// Jump Back
		}
		case WM_LBUTTONDOWN:
        {
            kbMs->mouseDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
            break;
        }
        case WM_RBUTTONDOWN:
        {
            kbMs->mouseDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
            break;
        }
        case WM_MBUTTONDOWN:
        {
            break;
        }
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
            kbMs->mouseUp();
            break;
        }
        case WM_MOUSEMOVE:
        {
            kbMs->mouseMove(modelTeapot,LOWORD(lParam),HIWORD(lParam));
            break;
        }
        case WM_MOUSEWHEEL:
        {
            kbMs->mouseWheel(modelTeapot, (float)GET_WHEEL_DELTA_WPARAM(wParam));
            break;
        }
	}
}
