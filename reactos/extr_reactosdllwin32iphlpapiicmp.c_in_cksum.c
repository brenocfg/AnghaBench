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
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */

__attribute__((used)) static int in_cksum(u_short *addr, int len)
{
    int nleft=len;
    u_short *w = addr;
    int sum = 0;
    u_short answer = 0;

    while (nleft > 1) {
        sum += *w++;
        nleft -= 2;
    }

    if (nleft == 1) {
        *(u_char *)(&answer) = *(u_char *)w;
        sum += answer;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum  += (sum >> 16);
    answer = ~sum;
    return(answer);
}