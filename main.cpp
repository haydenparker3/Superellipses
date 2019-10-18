#include "common.h"
#include "cmath"

bool Init();
void CleanUp();
void Run();
void SuperEllipse();
double SuperShape(double ang);
double sgn(double a);

SDL_Window *window;
SDL_GLContext glContext;
SDL_Surface *gScreenSurface = nullptr;
SDL_Renderer *renderer = nullptr;

int screenWidth = 500;
int screenHeight = 500;
double n1 = 1;
double n2 = 1;
double n3 = 1;
double m = 5;
double a = 1;
double b = 1;
const double PI = 3.1415926;

bool Init()
{
    if (SDL_Init(SDL_INIT_NOPARACHUTE & SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        //Specify OpenGL Version (4.2)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_Log("SDL Initialised");
    }

    //Create Window Instance
    window = SDL_CreateWindow(
        "Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenWidth,
        screenHeight,   
        SDL_WINDOW_OPENGL);

    //Check that the window was succesfully created
    if (window == NULL)
    {
        //Print error, if null
        printf("Could not create window: %s\n", SDL_GetError());
        return false;
    }
    else{
        gScreenSurface = SDL_GetWindowSurface(window);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_Log("Window Successful Generated");
    }
    //Map OpenGL Context to Window
    glContext = SDL_GL_CreateContext(window);

    return true;
}

int main()
{
    //Error Checking/Initialisation
    if (!Init())
    {
        printf("Failed to Initialize");
        return -1;
    }

    // Clear buffer with black background
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //Swap Render Buffers
    SDL_GL_SwapWindow(window);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Run();

    CleanUp();
    return 0;
}

void CleanUp()
{
    //Free up resources
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Run()
{
    bool gameLoop = true;
    srand(time(NULL));

    while (gameLoop)
    {   
        SuperEllipse();
        SDL_RenderPresent(renderer);
        SDL_Event event;
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameLoop = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        gameLoop = false;
                        break;
                    // case SDLK_w:
                    //     n+=.1;
                    //     break;
                    // case SDLK_s:
                    //     n-=.1;
                    //     break;
                    // case SDLK_a:
                    //     a--;
                    //     break;
                    // case SDLK_d:
                    //     b--;
                    //     break;
                    // case SDLK_e:
                    //     b++;
                    //     break;
                    // case SDLK_q:
                    //     a++;
                    //     break;
                    // case SDLK_r:
                    //     break;
                    // case SDLK_f:
                    //     break;
                    default:
                        break;
                }
            }

            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym){
                    default:
                        break;
                }
            }
        }
    }
}

double SuperShape(double ang){
    double in = pow(abs((1/a) * cos((m * ang)/4)), n2) + pow(abs((1/b) * sin((m * ang)/4)), n3);
    double r = 1 / pow(in, 1/n1);
    return r;
}

void SuperEllipse(){
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    pos.w = screenWidth;
    pos.h = screenHeight;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &pos);

    int points = 500;
    double inc = (2 * PI) / points;
    for(double ang = 0; ang < 2 * PI; ang+=inc){
        double radius = 100;
        double r = SuperShape(ang);
        double x = radius * r * cos(ang) + screenWidth/2;
        double y = radius * r * sin(ang) + screenHeight/2;

        pos.x = x;
        pos.y = y; 
        pos.w = 1;
        pos.h = 1;
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderFillRect(renderer, &pos);
    }  
    
}

double sgn(double a){
    if(a < 0)
        return -1;
    else if(a > 0)
        return 1;
    else
        return 0;
}