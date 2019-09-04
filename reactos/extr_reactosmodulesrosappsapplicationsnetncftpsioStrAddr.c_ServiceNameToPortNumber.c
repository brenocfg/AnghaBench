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
struct servent {scalar_t__ s_port; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  ISALNUM (char) ; 
 unsigned int atoi (char*) ; 
 struct servent* getservbyname (char*,char*) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ ntohs (unsigned short) ; 
 int /*<<< orphan*/  strncpy (char*,char const* const,int) ; 

__attribute__((used)) static unsigned int
ServiceNameToPortNumber(const char *const s)
{
	char str[64];
	char *cp;
	struct servent *sp;

	strncpy(str, s, sizeof(str) - 1);
	str[sizeof(str) - 1] = '\0';
	cp = str;
	if (isdigit(*cp)) {
		while (isdigit(*cp))
			cp++;
		*cp = '\0';
		return (atoi(str));
	}
	for (;; cp++) {
		if ((*cp == '\0')
			|| ((!ISALNUM(*cp)) && (*cp != '-') && (*cp != '_')))
				break;
	}
	*cp = '\0';

	sp = getservbyname(str, "tcp");
	if (sp != NULL) {
		/* endservent(); */
		return ((unsigned int) ntohs((unsigned short) sp->s_port));
	}
	sp = getservbyname(str, "udp");
	if (sp != NULL) {
		/* endservent(); */
		return ((unsigned int) ntohs((unsigned short) sp->s_port));
	}
	return (0);	/* error */
}