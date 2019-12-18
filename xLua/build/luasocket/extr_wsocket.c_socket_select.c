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
typedef  scalar_t__ t_socket ;
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  p_timeout ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (int /*<<< orphan*/ ) ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 double timeout_get (int /*<<< orphan*/ ) ; 

int socket_select(t_socket n, fd_set *rfds, fd_set *wfds, fd_set *efds, 
        p_timeout tm) {
    struct timeval tv; 
    double t = timeout_get(tm);
    tv.tv_sec = (int) t;
    tv.tv_usec = (int) ((t - tv.tv_sec) * 1.0e6);
    if (n <= 0) {
        Sleep((DWORD) (1000*t));
        return 0;
    } else return select(0, rfds, wfds, efds, t >= 0.0? &tv: NULL);
}