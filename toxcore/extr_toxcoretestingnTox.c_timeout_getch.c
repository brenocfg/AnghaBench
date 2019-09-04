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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 char ERR ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 char getch () ; 
 int /*<<< orphan*/  new_lines (char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int tox_iteration_interval (int /*<<< orphan*/ *) ; 

char timeout_getch(Tox *m)
{
    char c;
    int slpval = tox_iteration_interval(m);

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = slpval * 1000;

    c = ERR;
    int n = select(1, &fds, NULL, NULL, &tv);

    if (n < 0) {
        new_lines("select error: maybe interupted");
    } else if (n == 0) {
    } else {
        c = getch();
    }

    return c;
}