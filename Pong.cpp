#include <SDL/SDL.h>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("Pong!", NULL);
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    bool running = true;

    const int FPS = 30;
    Uint32 start;

    Uint32 COLOR_WHITE = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
    Uint32 COLOR_BLACK = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
    Uint32 COLOR_YELLOW = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0x00);
    Uint32 CLEAR_COLOR = COLOR_BLACK;

    const int DIRECTION_UP = 0, DIRECTION_RIGHT = 1, DIRECTION_DOWN = 2, DIRECTION_LEFT = 3;

    bool dir[4] = {false, false, false, false};

    bool ballDir[4] = {true, false, false, true};
    int ballSpeed = 4;

    SDL_Rect screenTop;
    SDL_Rect screenBottom;
    SDL_Rect screenMiddle;

    SDL_Rect ball;

    SDL_Rect paddle1;
    SDL_Rect paddle2;

    screenTop.x = 0;
    screenTop.y = 0;
    screenTop.w = 800;
    screenTop.h = 20;

    screenMiddle.x = 397;
    screenMiddle.y = 0;
    screenMiddle.w = 6;
    screenMiddle.h = 600;

    screenBottom.x = 0;
    screenBottom.y = 580;
    screenBottom.w = 800;
    screenBottom.h = 20;

    ball.x = 392;
    ball.y = 292;
    ball.w = 16;
    ball.h = 16;

    paddle1.x = 20;
    paddle1.y = 270;
    paddle1.w = 10;
    paddle1.h = 60;

    paddle2.x = 780;
    paddle2.y = 270;
    paddle2.w = 10;
    paddle2.h = 60;

    while (running)
    {
        start = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_w:
                            dir[DIRECTION_UP] = true;
                            break;
                        case SDLK_s:
                            dir[DIRECTION_DOWN] = true;
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_w:
                            dir[DIRECTION_UP] = false;
                            break;
                        case SDLK_s:
                            dir[DIRECTION_DOWN] = false;
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }

        // Check if the player collided with the game bounds.
        if (dir[DIRECTION_UP])
        {
            if (paddle1.y >= 20)
            {
                paddle1.y -= 10;
            }
        }
        if (dir[DIRECTION_DOWN])
        {
            if ((paddle1.y + paddle1.h) < 580)
            {
                paddle1.y += 10;
            }
        }

        // Check if the ball collided with the game bounds.
        if (ball.y <= 20)
        {
            ballDir[DIRECTION_UP] = false;
            ballDir[DIRECTION_DOWN] = true;
        }
        if ((ball.y + ball.h) >= 580)
        {
            ballDir[DIRECTION_UP] = true;
            ballDir[DIRECTION_DOWN] = false;
        }

        // Check if the ball collided with the paddles
        if ((ball.x <= (paddle1.x + paddle1.w)) && (ball.y >= paddle1.y) && (ball.y <= (paddle1.y + paddle1.h)))
        {
            ballDir[DIRECTION_LEFT] = false;
            ballDir[DIRECTION_RIGHT] = true;
        }
        if (((ball.x + ball.w) >= paddle2.x) && (ball.y >= paddle2.y) && (ball.y <= (paddle2.y + paddle2.h)))
        {
            ballDir[DIRECTION_LEFT] = true;
            ballDir[DIRECTION_RIGHT] = false;
        }

        // Check if the balls has fallen 'out of bounds' and reposition it if it has.
        if ((ball.x < 1) || (ball.x > 799) || (ball.y < 1) || (ball.y > 599))
        {
            ball.x = 392;
            ball.y = 292;
            ball.w = 16;
            ball.h = 16;
        }

        // Move the computer-controlled paddle.
        if (paddle2.y > ball.y)
        {
            if (paddle2.y >= 20)
            {
                paddle2.y -= 10;
            }

        }
        if ((paddle2.y + paddle2.h) < ball.y)
        {
            if ((paddle2.y + paddle2.h) < 580)
            {
                paddle2.y += 10;
            }
        }

        // Move the ball
        if (ballDir[DIRECTION_UP])
        {
            ball.y -= ballSpeed;
        }
        if (ballDir[DIRECTION_RIGHT])
        {
            ball.x += ballSpeed;
        }
        if (ballDir[DIRECTION_LEFT])
        {
            ball.x -= ballSpeed;
        }
        if (ballDir[DIRECTION_DOWN])
        {
            ball.y += ballSpeed;
        }

        SDL_FillRect(screen, &screen->clip_rect, CLEAR_COLOR);

        SDL_FillRect(screen, &screenTop, COLOR_WHITE);
        SDL_FillRect(screen, &screenMiddle, COLOR_WHITE);
        SDL_FillRect(screen, &screenBottom, COLOR_WHITE);

        SDL_FillRect(screen, &ball, COLOR_YELLOW);

        SDL_FillRect(screen, &paddle1, COLOR_WHITE);
        SDL_FillRect(screen, &paddle2, COLOR_WHITE);

        SDL_Flip(screen);

        if (1000 / FPS > SDL_GetTicks() - start)
        {
            SDL_Delay(1000/FPS-(SDL_GetTicks() - start));
        }
    }

    SDL_Quit();
    exit(0);
}
