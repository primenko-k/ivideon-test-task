#include "camera.h"
#include "server.h"
#include <csignal>

static Camera cam;
static Server server(&cam);

void handle_signal(int signum)
{
    switch (signum)
    {
    case SIGINT:
    case SIGTERM:
    case SIGHUP:
        server.stop();
        break;
    }
}

void set_signal_handler()
{
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    // ignore signals to prevent program termination
    action.sa_handler = SIG_IGN;
    sigaction (SIGPIPE, &action, NULL);
    sigaction (SIGALRM, &action, NULL);
    sigaction (SIGUSR1, &action, NULL);
    sigaction (SIGUSR2, &action, NULL);
    // handle signals to perform garbage collection
    action.sa_handler = handle_signal;
    sigaction (SIGINT, &action, NULL);
    sigaction (SIGTERM, &action, NULL);
    sigaction (SIGHUP, &action, NULL);
}

int main()
{
    set_signal_handler();

    server.run();

    return 0;
}
