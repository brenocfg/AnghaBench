#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sockaddr ;
struct TYPE_4__ {int /*<<< orphan*/  sock; } ;
struct TYPE_5__ {TYPE_1__ tcp; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

wchar_t *
tcp_get_address(RDPCLIENT * This)
{
#if 0
	static char ipaddr[32];
	struct sockaddr_in sockaddr;
	socklen_t len = sizeof(sockaddr);
	if (getsockname(This->tcp.sock, (struct sockaddr *) &sockaddr, &len) == 0)
	{
		unsigned char *ip = (unsigned char *) &sockaddr.sin_addr;
		sprintf(ipaddr, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
	}
	else
		strcpy(ipaddr, "127.0.0.1");
	return ipaddr;
#endif
	return NULL; // TODO
}