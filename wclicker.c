#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/uinput.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <getopt.h>

static int fd = -1, run = 1;

void emit(int t, int c, int v) {
    struct input_event e = { .type = t, .code = c, .value = v };
    gettimeofday(&e.time, 0);
    if (write(fd, &e, sizeof(e)) < 0) exit(1);
}

void click() {
    emit(EV_KEY, BTN_LEFT, 1); emit(EV_SYN, SYN_REPORT, 0);
    usleep(8000);
    emit(EV_KEY, BTN_LEFT, 0); emit(EV_SYN, SYN_REPORT, 0);
}

void sigint(int _) { (void)_; run = 0; }

void die(const char *msg) {
    dprintf(2, "wclicker: %s\n", msg);
    if (fd >= 0) { ioctl(fd, UI_DEV_DESTROY); close(fd); }
    exit(1);
}

int setup() {
    if ((fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK)) < 0) return -1;
    if (ioctl(fd, UI_SET_EVBIT, EV_KEY) || ioctl(fd, UI_SET_KEYBIT, BTN_LEFT) || ioctl(fd, UI_SET_EVBIT, EV_SYN)) return -1;
    struct uinput_setup us = { .id = { BUS_USB, 0x1, 0x1, 1 } };
    strncpy(us.name, "wclicker", sizeof(us.name) - 1);
    return ioctl(fd, UI_DEV_SETUP, &us) || ioctl(fd, UI_DEV_CREATE);
}

int main(int ac, char **av) {
    unsigned n = 0, d = 100, i = 0; int opt, anyopt = 0;

    while ((opt = getopt(ac, av, "n:d:h")) != -1) {
        if (opt == 'n') { n = strtoul(optarg, 0, 10); anyopt = 1; }
        else if (opt == 'd') { d = strtoul(optarg, 0, 10); anyopt = 1; }
        else {
            printf("Usage: %s [-n count] [-d delay_ms]\n", *av);
            return 0;
        }
    }

    if (!anyopt) {
        printf("Usage: wclicker [-n count] [-d delay_ms]\n");
        return 0;
    }

    if (d == 0 || setup()) die("failed to init uinput (need root?)");

    signal(SIGINT, sigint);
    for (; run && (!n || i++ < n); usleep(d * 1000)) click();

    ioctl(fd, UI_DEV_DESTROY); close(fd);
    return 0;
}

