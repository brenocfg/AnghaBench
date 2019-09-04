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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  CompressPath (char* const,char const* const,size_t const) ; 
 int /*<<< orphan*/  Strnpcat (char*,char*,int) ; 
 char* Strnpcpy (char*,char*,int) ; 

void
PathCat(char *const dst, const size_t dsize, const char *const cwd, const char *const src)
{
	char *cp;
	char tmp[512];

	if (src[0] == '/') {
		CompressPath(dst, src, dsize);
		return;
	}
	cp = Strnpcpy(tmp, (char *) cwd, sizeof(tmp) - 1);
	*cp++ = '/';
	*cp = '\0';
	(void) Strnpcat(cp, (char *) src, sizeof(tmp) - (cp - tmp));
	CompressPath(dst, tmp, dsize);
}