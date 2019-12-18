#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 scalar_t__ close (int) ; 
 int copy_fd (int,int) ; 
 scalar_t__ errno ; 
 int g_open (char const*,int,int) ; 

int copy_file (const char *dst, const char *src, int mode)
{
    int fdi, fdo, status;

    if ((fdi = g_open (src, O_RDONLY | O_BINARY, 0)) < 0)
        return fdi;

    fdo = g_open (dst, O_WRONLY | O_CREAT | O_EXCL | O_BINARY, mode);
    if (fdo < 0 && errno == EEXIST) {
        close (fdi);
        return 0;
    } else if (fdo < 0){
        close (fdi);
        return -1;
    }

    status = copy_fd (fdi, fdo);
    if (close (fdo) != 0)
        return -1;

    return status;
}