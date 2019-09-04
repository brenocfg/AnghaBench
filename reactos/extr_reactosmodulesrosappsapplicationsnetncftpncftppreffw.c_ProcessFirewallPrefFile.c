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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ISTREQ (char*,char*) ; 
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,char*) ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 void* gDataPortMode ; 
 int /*<<< orphan*/  gFirewallExceptionList ; 
 int /*<<< orphan*/  gFirewallHost ; 
 int /*<<< orphan*/  gFirewallPass ; 
 unsigned int gFirewallPort ; 
 int gFirewallType ; 
 int /*<<< orphan*/  gFirewallUser ; 
 void* gFwDataPortMode ; 
 scalar_t__ isdigit (char) ; 
 void* kFallBackToSendPortMode ; 
 int kFirewallLastType ; 
 void* kPassiveMode ; 
 void* kSendPortMode ; 
 char* strtok (char*,char*) ; 

void
ProcessFirewallPrefFile(FILE *fp)
{
	char line[256];
	char *tok1, *tok2;
	int n;

	/* Opened the firewall preferences file. */
	line[sizeof(line) - 1] = '\0';
	while (fgets(line, sizeof(line) - 1, fp) != NULL) {
		tok1 = strtok(line, " =\t\r\n");
		if ((tok1 == NULL) || (tok1[0] == '#'))
			continue;
		tok2 = strtok(NULL, "\r\n");
		if (tok2 == NULL)
			continue;
		if (ISTREQ(tok1, "firewall-type")) {
			n = atoi(tok2);
			if ((n > 0) && (n <= kFirewallLastType))
				gFirewallType = n;
		} else if (ISTREQ(tok1, "firewall-host")) {
			(void) STRNCPY(gFirewallHost, tok2);
		} else if (ISTREQ(tok1, "firewall-port")) {
			n = atoi(tok2);
			if (n > 0)
				gFirewallPort = (unsigned int) n;
		} else if (ISTREQ(tok1, "firewall-user")) {
			(void) STRNCPY(gFirewallUser, tok2);
		} else if (ISTREQ(tok1, "firewall-pass")) {
			(void) STRNCPY(gFirewallPass, tok2);
		} else if (ISTREQ(tok1, "firewall-password")) {
			(void) STRNCPY(gFirewallPass, tok2);
		} else if (ISTREQ(tok1, "firewall-exception-list")) {
			(void) STRNCPY(gFirewallExceptionList, tok2);
		} else if (ISTREQ(tok1, "passive")) {
			if (ISTREQ(tok2, "optional")) {
				gDataPortMode = gFwDataPortMode = kFallBackToSendPortMode;
			} else if (ISTREQ(tok2, "on")) {
				gDataPortMode = gFwDataPortMode = kPassiveMode;
			} else if (ISTREQ(tok2, "off")) {
				gDataPortMode = gFwDataPortMode = kSendPortMode;
			} else if ((int) isdigit(tok2[0])) {
				gDataPortMode = gFwDataPortMode = atoi(tok2);
			}
		}
	}
}