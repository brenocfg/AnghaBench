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
 scalar_t__ ISTRNEQ (char const*,char*,int) ; 
 int /*<<< orphan*/  STRNCPY (char*,char*) ; 
 int /*<<< orphan*/  Strncpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  isdigit (int) ; 
 char* strtok (char*,char*) ; 

void
DefaultBookmarkName(char *dst, size_t siz, char *src)
{
	char str[128];
	const char *token;
	const char *cp;

	(void) STRNCPY(str, src);

	/* Pick the first "significant" part of the hostname.  Usually
	 * this is the first word in the name, but if it's something like
	 * ftp.unl.edu, we would want to choose "unl" and not "ftp."
	 */
	token = str;
	if ((token = strtok(str, ".")) == NULL)
		token = str;
	else if ((ISTRNEQ(token, "ftp", 3)) || (ISTRNEQ(token, "www", 3))) {
		if ((token = strtok(NULL, ".")) == NULL)
			token = "";
	}
	for (cp = token; ; cp++) {
		if (*cp == '\0') {
			/* Token was all digits, like an IP address perhaps. */
			token = "";
		}
		if (!isdigit((int) *cp))
			break;
	}
	(void) Strncpy(dst, token, siz);
}