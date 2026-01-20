#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "Application.h"

int main(int argc, char* argv[])
{
    Application app;

    app.Run();

    app.Cleanup();

    return 0;
}