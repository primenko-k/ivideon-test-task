#include "camera.h"
#include "server.h"

int main()
{
    Camera cam;
    Server server(&cam);

    server.run();

    return 0;
}
