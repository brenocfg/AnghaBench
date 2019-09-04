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
struct sockinfo {int /*<<< orphan*/  addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  si ;

/* Variables and functions */
 int getpeername (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  memset (struct sockinfo*,int /*<<< orphan*/ ,int) ; 
 char* nc_unresolve_addr (struct sockaddr*,int) ; 

char *
nc_unresolve_peer_desc(int sd)
{
    static struct sockinfo si;
    struct sockaddr *addr;
    socklen_t addrlen;
    int status;

    memset(&si, 0, sizeof(si));
    addr = (struct sockaddr *)&si.addr;
    addrlen = sizeof(si.addr);

    status = getpeername(sd, addr, &addrlen);
    if (status < 0) {
        return "unknown";
    }

    return nc_unresolve_addr(addr, addrlen);
}