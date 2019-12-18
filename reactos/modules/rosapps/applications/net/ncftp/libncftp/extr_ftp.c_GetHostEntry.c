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
struct in_addr {scalar_t__ s_addr; } ;
struct hostent {scalar_t__ h_length; int /*<<< orphan*/ * h_addr_list; } ;

/* Variables and functions */
 scalar_t__ INADDR_NONE ; 
 struct hostent* gethostbyname (char*) ; 
 scalar_t__ inet_addr (char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static struct hostent *
GetHostEntry(char *host, struct in_addr *ip_address)
{
	struct in_addr ip;
	struct hostent *hp;

	/* See if the host was given in the dotted IP format, like "36.44.0.2."
	 * If it was, inet_addr will convert that to a 32-bit binary value;
	 * it not, inet_addr will return (-1L).
	 */
	ip.s_addr = inet_addr(host);
	if (ip.s_addr != INADDR_NONE) {
		hp = NULL;
	} else {
		/* No IP address, so it must be a hostname, like ftp.wustl.edu. */
		hp = gethostbyname(host);
		if (hp != NULL)
			(void) memcpy(&ip.s_addr, hp->h_addr_list[0], (size_t) hp->h_length);
	}
	if (ip_address != NULL)
		*ip_address = ip;
	return (hp);
}