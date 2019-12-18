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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ readn (int,char*,int) ; 
 scalar_t__ writen (int,char*,scalar_t__) ; 

int copy_fd (int ifd, int ofd)
{
    while (1) {
        char buffer[8192];
        ssize_t len = readn (ifd, buffer, sizeof(buffer));
        if (!len)
            break;
        if (len < 0) {
            close (ifd);
            return -1;
        }
        if (writen (ofd, buffer, len) < 0) {
            close (ofd);
            return -1;
        }
    }
    close(ifd);
    return 0;
}