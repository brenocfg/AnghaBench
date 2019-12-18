#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; } ;
struct hostent {scalar_t__ h_length; int /*<<< orphan*/ * h_addr_list; int /*<<< orphan*/  h_addrtype; } ;
typedef  int /*<<< orphan*/  portstr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EADDRNOTAVAIL ; 
 scalar_t__ ENOENT ; 
 unsigned long INADDR_NONE ; 
 int /*<<< orphan*/  ISALNUM (char) ; 
 unsigned int ServiceNameToPortNumber (char*) ; 
 unsigned int atoi (char*) ; 
 scalar_t__ errno ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  htons (short) ; 
 unsigned long inet_addr (char*) ; 
 scalar_t__ isdigit (char) ; 
 int kAddrStrToAddrBadHost ; 
 int kAddrStrToAddrMiscErr ; 
 int /*<<< orphan*/  memcpy (unsigned long*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in* const,int /*<<< orphan*/ ,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char const* const,int) ; 

int
AddrStrToAddr(const char * const s, struct sockaddr_in * const sa, const int defaultport)
{
	char portstr[128];
	unsigned long ipnum;
	unsigned int port;
	struct hostent *hp;
	char *hostcp, *atsign, *colon, *cp, *p2;

	memset(sa, 0, sizeof(struct sockaddr_in));
	strncpy(portstr, s, sizeof(portstr));
	portstr[sizeof(portstr) - 1] = '\0';

	if ((colon = strchr(portstr, ':')) != NULL) {
		/* Does it look like a URL?  http://host ? */
		if ((colon[1] == '/') && (colon[2] == '/')) {
			*colon = '\0';
			port = 0;
			hostcp = colon + 3;
			for (cp = hostcp; *cp != '\0'; cp++) {
				if ((!ISALNUM(*cp)) && (*cp != '.')) {
					/* http://host:port */
					if ((*cp == ':') && (isdigit(cp[1]))) {
						*cp++ = '\0';
						p2 = cp;
						while (isdigit(*cp))
							cp++;
						*cp = '\0';
						port = atoi(p2);
					}
					*cp = '\0';
					break;
				}
			}
			if (port == 0)
				port = ServiceNameToPortNumber(portstr);
		} else {
			/* Look for host.name.domain:port */
			*colon = '\0';
			hostcp = portstr;
			port = (unsigned int) atoi(colon + 1);
		}
	} else if ((atsign = strchr(portstr, '@')) != NULL) {
		/* Look for port@host.name.domain */
		*atsign = '\0';
		hostcp = atsign + 1;
		port = (unsigned int) atoi(portstr);
	} else if (defaultport > 0) {
		/* Have just host.name.domain, use that w/ default port. */
		port = (unsigned int) defaultport;
		hostcp = portstr;
	} else {
		/* If defaultport <= 0, they must supply a port number
		 * in the host/port string.
		 */
		errno = EADDRNOTAVAIL;
		return (kAddrStrToAddrMiscErr);
	}

	sa->sin_port = htons((short) port);

	ipnum = inet_addr(hostcp);
	if (ipnum != INADDR_NONE) {
		sa->sin_family = AF_INET;
		sa->sin_addr.s_addr = ipnum;
	} else {
		errno = 0;
		hp = gethostbyname(hostcp);
		if (hp == NULL) {
			if (errno == 0)
				errno = ENOENT;
			return (kAddrStrToAddrBadHost);
		}
		sa->sin_family = hp->h_addrtype;
		memcpy(&sa->sin_addr.s_addr, hp->h_addr_list[0],
			(size_t) hp->h_length);
	}
	return (0);
}