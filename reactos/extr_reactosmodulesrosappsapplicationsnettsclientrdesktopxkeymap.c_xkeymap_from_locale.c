#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  keymapname; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* strrchr (char*,char) ; 
 char tolower (int) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 int /*<<< orphan*/ * xkeymap_open (char*) ; 
 char* xstrdup (char const*) ; 

BOOL
xkeymap_from_locale(RDPCLIENT * This, const char *locale)
{
	char *str, *ptr;
	FILE *fp;

	/* Create a working copy */
	str = xstrdup(locale);

	/* Truncate at dot and at */
	ptr = strrchr(str, '.');
	if (ptr)
		*ptr = '\0';
	ptr = strrchr(str, '@');
	if (ptr)
		*ptr = '\0';

	/* Replace _ with - */
	ptr = strrchr(str, '_');
	if (ptr)
		*ptr = '-';

	/* Convert to lowercase */
	ptr = str;
	while (*ptr)
	{
		*ptr = tolower((int) *ptr);
		ptr++;
	}

	/* Try to open this keymap (da-dk) */
	fp = xkeymap_open(str);
	if (fp == NULL)
	{
		/* Truncate at dash */
		ptr = strrchr(str, '-');
		if (ptr)
			*ptr = '\0';

		/* Try the short name (da) */
		fp = xkeymap_open(str);
	}

	if (fp)
	{
		fclose(fp);
		STRNCPY(This->keymapname, str, sizeof(This->keymapname));
		xfree(str);
		return True;
	}

	xfree(str);
	return False;
}