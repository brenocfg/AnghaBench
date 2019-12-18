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
struct hostent {char** h_aliases; scalar_t__ h_name; } ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_2__ {char* defdname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* DOMAINNAME ; 
 char* HOSTNAME ; 
 int /*<<< orphan*/  STRNCPY (char*,char*) ; 
 int /*<<< orphan*/  Strncat (char*,char*,size_t) ; 
 int /*<<< orphan*/  Strncpy (char*,char*,size_t) ; 
 TYPE_1__ _res ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 struct hostent* gethostbyname (char*) ; 
 int gethostname (char*,int) ; 
 int /*<<< orphan*/  isalpha (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_init () ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 

int
GetOurHostName(char *host, size_t siz)
{
#ifdef HOSTNAME
	/* You can hardcode in the name if this routine doesn't work
	 * the way you want it to.
	 */
	Strncpy(host, HOSTNAME, siz);
	return (1);		/* Success */
#else
	struct hostent *hp;
	int result;
	char **curAlias;
	char domain[64];
	char *cp;
	int rc;

	host[0] = '\0';
	result = gethostname(host, (int) siz);
	if ((result < 0) || (host[0] == '\0')) {
		return (-1);
	}

	if (strchr(host, '.') != NULL) {
		/* gethostname returned full name (like "cse.unl.edu"), instead
		 * of just the node name (like "cse").
		 */
		return (2);		/* Success */
	}

	hp = gethostbyname(host);
	if (hp != NULL) {
		/* Maybe the host entry has the full name. */
		cp = strchr((char *) hp->h_name, '.');
		if ((cp != NULL) && (cp[1] != '\0')) {
			/* The 'name' field for the host entry had full name. */
			(void) Strncpy(host, (char *) hp->h_name, siz);
			return (3);		/* Success */
		}

		/* Now try the list of aliases, to see if any of those look real. */
		for (curAlias = hp->h_aliases; *curAlias != NULL; curAlias++) {
			cp = strchr(*curAlias, '.');
			if ((cp != NULL) && (cp[1] != '\0')) {
				(void) Strncpy(host, *curAlias, siz);
				return (4);		/* Success */
			}
		}
	}

	/* Otherwise, we just have the node name.  See if we can get the
	 * domain name ourselves.
	 */
#ifdef DOMAINNAME
	(void) STRNCPY(domain, DOMAINNAME);
	rc = 5;
#else
	rc = -1;
	domain[0] = '\0';
#	if defined(HAVE_RES_INIT) && defined(HAVE__RES_DEFDNAME)
	if (domain[0] == '\0') {
		(void) res_init();
		if ((_res.defdname != NULL) && (_res.defdname[0] != '\0')) {
			(void) STRNCPY(domain, _res.defdname);
			rc = 6;
		}
	}
#	endif	/* HAVE_RES_INIT && HAVE__RES_DEFDNAME */

	if (domain[0] == '\0') {
		FILE *fp;
		char line[256];
		char *tok;

		fp = fopen("/etc/resolv.conf", "r");
		if (fp != NULL) {
			(void) memset(line, 0, sizeof(line));
			while (fgets(line, sizeof(line) - 1, fp) != NULL) {
				if (!isalpha((int) line[0]))
					continue;	/* Skip comment lines. */
				tok = strtok(line, " \t\n\r");
				if (tok == NULL)
					continue;	/* Impossible */
				if (strcmp(tok, "domain") == 0) {
					tok = strtok(NULL, " \t\n\r");
					if (tok == NULL)
						continue;	/* syntax error */
					(void) STRNCPY(domain, tok);
					rc = 7;
					break;	/* Done. */
				}
			}
			(void) fclose(fp);
		}
	}
#endif	/* DOMAINNAME */

	if (domain[0] != '\0') {
		/* Supposedly, it's legal for a domain name with
		 * a period at the end.
		 */
		cp = domain + strlen(domain) - 1;
		if (*cp == '.')
			*cp = '\0';
		if (domain[0] != '.')
			(void) Strncat(host, ".", siz);
		(void) Strncat(host, domain, siz);
	}
	if (rc < 0)
		host[0] = '\0';
	return(rc);	/* Success */
#endif	/* !HOSTNAME */
}