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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int COLOUR_FLAG_256 ; 
 int colour_join_rgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isxdigit (int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 int strtonum (char const*,int /*<<< orphan*/ ,int,char const**) ; 

int
colour_fromstring(const char *s)
{
	const char	*errstr;
	const char	*cp;
	int		 n;
	u_char		 r, g, b;

	if (*s == '#' && strlen(s) == 7) {
		for (cp = s + 1; isxdigit((u_char) *cp); cp++)
			;
		if (*cp != '\0')
			return (-1);
		n = sscanf(s + 1, "%2hhx%2hhx%2hhx", &r, &g, &b);
		if (n != 3)
			return (-1);
		return (colour_join_rgb(r, g, b));
	}

	if (strncasecmp(s, "colour", (sizeof "colour") - 1) == 0) {
		n = strtonum(s + (sizeof "colour") - 1, 0, 255, &errstr);
		if (errstr != NULL)
			return (-1);
		return (n | COLOUR_FLAG_256);
	}

	if (strcasecmp(s, "default") == 0)
		return (8);
	if (strcasecmp(s, "terminal") == 0)
		return (9);

	if (strcasecmp(s, "black") == 0 || strcmp(s, "0") == 0)
		return (0);
	if (strcasecmp(s, "red") == 0 || strcmp(s, "1") == 0)
		return (1);
	if (strcasecmp(s, "green") == 0 || strcmp(s, "2") == 0)
		return (2);
	if (strcasecmp(s, "yellow") == 0 || strcmp(s, "3") == 0)
		return (3);
	if (strcasecmp(s, "blue") == 0 || strcmp(s, "4") == 0)
		return (4);
	if (strcasecmp(s, "magenta") == 0 || strcmp(s, "5") == 0)
		return (5);
	if (strcasecmp(s, "cyan") == 0 || strcmp(s, "6") == 0)
		return (6);
	if (strcasecmp(s, "white") == 0 || strcmp(s, "7") == 0)
		return (7);
	if (strcasecmp(s, "brightblack") == 0 || strcmp(s, "90") == 0)
		return (90);
	if (strcasecmp(s, "brightred") == 0 || strcmp(s, "91") == 0)
		return (91);
	if (strcasecmp(s, "brightgreen") == 0 || strcmp(s, "92") == 0)
		return (92);
	if (strcasecmp(s, "brightyellow") == 0 || strcmp(s, "93") == 0)
		return (93);
	if (strcasecmp(s, "brightblue") == 0 || strcmp(s, "94") == 0)
		return (94);
	if (strcasecmp(s, "brightmagenta") == 0 || strcmp(s, "95") == 0)
		return (95);
	if (strcasecmp(s, "brightcyan") == 0 || strcmp(s, "96") == 0)
		return (96);
	if (strcasecmp(s, "brightwhite") == 0 || strcmp(s, "97") == 0)
		return (97);
	return (-1);
}