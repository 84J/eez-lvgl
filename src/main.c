/*******************************************************************
 *
 * main.c - LVGL simulator for GNU/Linux
 *
 * Based on the original file from the repository
 *
 * @note eventually this file won't contain a main function and will
 * become a library supporting all major operating systems
 *
 * To see how each driver is initialized check the
 * 'src/lib/display_backends' directory
 *
 * - Clean up
 * - Support for multiple backends at once
 *   2025 EDGEMTech Ltd.
 *
 * Author: EDGEMTech Ltd, Erik Tagirov (erik.tagirov@edgemtech.ch)
 *
 ******************************************************************/
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"

#include "ui/screens.h"
#include "ui/ui.h"

#include "src/lib/driver_backends.h"
#include "src/lib/simulator_util.h"
#include "src/lib/simulator_settings.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#include "src/ui/state_machine.h"

/* Internal functions */
static void configure_simulator(int argc, char **argv);
static void print_lvgl_version(void);
static void print_usage(void);

/* contains the name of the selected backend if user
 * has specified one on the command line */
static char *selected_backend;

/* Global simulator settings, defined in lv_linux_backend.c */
extern simulator_settings_t settings;


/**
 * @brief Print LVGL version
 */
static void print_lvgl_version(void)
{
    fprintf(stdout, "%d.%d.%d-%s\n",
            LVGL_VERSION_MAJOR,
            LVGL_VERSION_MINOR,
            LVGL_VERSION_PATCH,
            LVGL_VERSION_INFO);
}

/**
 * @brief Print usage information
 */
static void print_usage(void)
{
    fprintf(stdout, "\nlvglsim [-V] [-B] [-b backend_name] [-W window_width] [-H window_height]\n\n");
    fprintf(stdout, "-V print LVGL version\n");
    fprintf(stdout, "-B list supported backends\n");
}

/**
 * @brief Configure simulator
 * @description process arguments recieved by the program to select
 * appropriate options
 * @param argc the count of arguments in argv
 * @param argv The arguments
 */
static void configure_simulator(int argc, char **argv)
{
    int opt = 0;

    selected_backend = NULL;
    driver_backends_register();

    const char *env_w = getenv("LV_SIM_WINDOW_WIDTH");
    const char *env_h = getenv("LV_SIM_WINDOW_HEIGHT");
    /* Default values */
    settings.window_width = atoi(env_w ? env_w : "640");
    settings.window_height = atoi(env_h ? env_h : "480");

    /* Parse the command-line options. */
    while ((opt = getopt (argc, argv, "b:fmW:H:BVh")) != -1) {
        switch (opt) {
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
            break;
        case 'V':
            print_lvgl_version();
            exit(EXIT_SUCCESS);
            break;
        case 'B':
            driver_backends_print_supported();
            exit(EXIT_SUCCESS);
            break;
        case 'b':
            if (driver_backends_is_supported(optarg) == 0) {
                die("error no such backend: %s\n", optarg);
            }
            selected_backend = strdup(optarg);
            break;
        case 'W':
            settings.window_width = atoi(optarg);
            break;
        case 'H':
            settings.window_height = atoi(optarg);
            break;
        case ':':
            print_usage();
            die("Option -%c requires an argument.\n", optopt);
            break;
        case '?':
            print_usage();
            die("Unknown option -%c.\n", optopt);
        }
    }
}

void* udp_listen(void* arg)
{
    (void) arg;
    const int port = 46666;

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) { perror("socket"); return NULL; }

    int one = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    struct timeval tv = { .tv_sec = 1, .tv_usec = 0 }; // 1s timeout
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    struct sockaddr_in addr; memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0
    addr.sin_port = htons(port);

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        close(s);
        return NULL;
    }

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    printf("[UDP] Receiver started\n");

    char buf[256];
    for (;;)
    {
        memset(buf, 0, sizeof(buf));

        struct sockaddr_in peer; socklen_t plen = sizeof(peer);
        ssize_t n = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&peer, &plen);
        if (n < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                pthread_testcancel();
                continue;
            }

            if (errno == EINTR) continue;
            perror("recvfrom");
            break;
        }

        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &peer.sin_addr, ip, sizeof(ip));

        char log[512];
        snprintf(log, sizeof(log), "[UDP] Received \"%s\" from %s:%d\n", buf, ip, port);

        if (strcmp(&buf[0], "POW") == 0) state == STATE_OFF ? state_set(STATE_SELECTION) : state_set(STATE_OFF);
        if (strcmp(&buf[0], "PR1") == 0)  program_set(PR_1);
        if (strcmp(&buf[0], "PR2") == 0)  program_set(PR_2);
        if (strcmp(&buf[0], "PR3") == 0)  program_set(PR_3);
        if (strcmp(&buf[0], "PR4") == 0)  program_set(PR_4);
        if (strcmp(&buf[0], "PR5") == 0)  program_set(PR_5);
        if (strcmp(&buf[0], "PR6") == 0)  program_set(PR_6);
        if (strcmp(&buf[0], "PR7") == 0)  program_set(PR_7);
        if (strcmp(&buf[0], "PR8") == 0)  program_set(PR_8);
        if (strcmp(&buf[0], "PR9") == 0)  program_set(PR_9);
        if (strcmp(&buf[0], "PR10") == 0) program_set(PR_10);
        if (strcmp(&buf[0], "PR11") == 0) program_set(PR_11);
        if (strcmp(&buf[0], "PR12") == 0) program_set(PR_12);

        if (strcmp(&buf[0], "OPT") == 0) screen_set(SCREEN_MOD);
        if (strcmp(&buf[0], "CF1") == 0) screen_set(SCREEN_MOD_SUMMARY);
        if (strcmp(&buf[0], "CF2") == 0) screen_set(SCREEN_MOD_2);
        if (strcmp(&buf[0], "CF3") == 0) screen_set(SCREEN_MOD_3);

        if (strcmp(&buf[0], "SET") == 0) screen_set(SCREEN_SET);
        if (strcmp(&buf[0], "PLAY") == 0) state != STATE_RUNNING ? state_set(STATE_RUNNING) : state_set(STATE_PAUSE);
        if (strcmp(&buf[0], "BACK") == 0) screen_set_previous();

        printf("%s", log);

        usleep(100000);
    }

    close(s);
    return NULL;
}

/**
 * @brief entry point
 * @description start a demo
 * @param argc the count of arguments in argv
 * @param argv The arguments
 */
int main(int argc, char **argv)
{

    configure_simulator(argc, argv);

    /* Initialize LVGL. */
    lv_init();

    /* Initialize the configured backend */
    if (driver_backends_init_backend(selected_backend) == -1) {
        die("Failed to initialize display backend");
    }

    /* Enable for EVDEV support */
#if LV_USE_EVDEV
    if (driver_backends_init_backend("EVDEV") == -1) {
        die("Failed to initialize evdev");
    }
#endif

    ui_init();

    // Run UDP receiver
    pthread_t th;
    pthread_create(&th, NULL, udp_listen, NULL);

    /* Enter the run loop of the selected backend */
    driver_backends_run_loop();

    // Stop UDP receiver
    pthread_cancel(th);
    pthread_join(th, NULL);

    return 0;
}
