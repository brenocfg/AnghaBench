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

/* Variables and functions */
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ *,char const* const) ; 
 int /*<<< orphan*/ * buf ; 
 int kFirewallNotInUse ; 
 int /*<<< orphan*/ * parse ; 
 int /*<<< orphan*/ * strchr (char const* const,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * strtok (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * tok ; 

int
MayUseFirewall(const char *const hn, int firewallType, const char *const firewallExceptionList)
{
#ifdef HAVE_STRSTR
	char buf[256];
	char *tok;
	char *parse;
#endif /* HAVE_STRSTR */

	if (firewallType == kFirewallNotInUse)
		return (0);

	if (firewallExceptionList[0] == '\0') {
		if (strchr(hn, '.') == NULL) {
			/* Unqualified host name,
			 * assume it is in local domain.
			 */
			return (0);
		} else {
			return (1);
		}
	}

	if (strchr(hn, '.') == NULL) {
		/* Unqualified host name,
		 * assume it is in local domain.
		 *
		 * If "localdomain" is in the exception list,
		 * do not use the firewall for this host.
		 */
		(void) STRNCPY(buf, firewallExceptionList);
		for (parse = buf; (tok = strtok(parse, ", \n\t\r")) != NULL; parse = NULL) {
			if (strcmp(tok, "localdomain") == 0)
				return (0);
		}
		/* fall through */
	}

#ifdef HAVE_STRSTR
	(void) STRNCPY(buf, firewallExceptionList);
	for (parse = buf; (tok = strtok(parse, ", \n\t\r")) != NULL; parse = NULL) {
		/* See if host or domain was from exclusion list
		 * matches the host to open.
		 */
		if (strstr(hn, tok) != NULL)
			return (0);
	}
#endif /* HAVE_STRSTR */
	return (1);
}