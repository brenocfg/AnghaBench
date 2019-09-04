#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  status ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ connection ;

/* Variables and functions */
#define  EAGAIN 128 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OK ; 
 int /*<<< orphan*/  RETRY ; 
 int errno ; 
 int write (int /*<<< orphan*/ ,char*,size_t) ; 

status sock_write(connection *c, char *buf, size_t len, size_t *n) {
    ssize_t r;
    if ((r = write(c->fd, buf, len)) == -1) {
        switch (errno) {
            case EAGAIN: return RETRY;
            default:     return ERROR;
        }
    }
    *n = (size_t) r;
    return OK;
}