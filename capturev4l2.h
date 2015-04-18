#ifndef __CAPTURE_H_
#define __CAPTURE_H_

#include "utils.h"
#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>


int open_device(const char* dev_name);
int print_caps(int fd);
int capture_image(IRISCONFIG* cfg);
int init_mmap(int fd);
int close_device(int fd);
#endif // __CAPTURE_H_
