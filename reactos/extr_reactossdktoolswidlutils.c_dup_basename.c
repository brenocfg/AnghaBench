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
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 char* xmalloc (int) ; 

char *dup_basename(const char *name, const char *ext)
{
	int namelen;
	int extlen = strlen(ext);
	char *base;
	char *slash;

	if(!name)
		name = "widl.tab";

	slash = strrchr(name, '/');
	if (!slash)
		slash = strrchr(name, '\\');

	if (slash)
		name = slash + 1;

	namelen = strlen(name);

	/* +6 for later extension (strlen("_r.rgs")) and +1 for '\0' */
	base = xmalloc(namelen +6 +1);
	strcpy(base, name);
	if(!strcasecmp(name + namelen-extlen, ext))
	{
		base[namelen - extlen] = '\0';
	}
	return base;
}