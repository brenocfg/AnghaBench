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
struct linger {int l_onoff; int l_linger; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  linger ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct linger*,int) ; 

int
nc_set_linger(int sd, int timeout)
{
    struct linger linger;
    socklen_t len;

    linger.l_onoff = 1;
    linger.l_linger = timeout;

    len = sizeof(linger);

    return setsockopt(sd, SOL_SOCKET, SO_LINGER, &linger, len);
}