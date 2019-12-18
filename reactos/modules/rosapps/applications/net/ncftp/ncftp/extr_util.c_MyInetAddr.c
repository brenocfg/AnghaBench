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
struct in_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  Strncpy (char*,char*,size_t) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,struct in_addr*,char*,size_t) ; 

void
MyInetAddr(char *dst, size_t siz, char **src, int i)
{
	struct in_addr *ia;
#ifndef HAVE_INET_NTOP
	char *cp;
#endif

	(void) Strncpy(dst, "???", siz);
	if (src != (char **) 0) {
		ia = (struct in_addr *) src[i];
#ifdef HAVE_INET_NTOP	/* Mostly to workaround bug in IRIX 6.5's inet_ntoa */
		(void) inet_ntop(AF_INET, ia, dst, siz - 1);
#else
		cp = inet_ntoa(*ia);
		if ((cp != (char *) 0) && (cp != (char *) -1) && (cp[0] != '\0'))
			(void) Strncpy(dst, cp, siz);
#endif
	}
}