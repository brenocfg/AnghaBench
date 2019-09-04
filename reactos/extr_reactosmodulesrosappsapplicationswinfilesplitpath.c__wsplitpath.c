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
typedef  char WCHAR ;

/* Variables and functions */
 int lstrlenW (char const*) ; 

void _wsplitpath(const WCHAR* path, WCHAR* drv, WCHAR* dir, WCHAR* name, WCHAR* ext)
{
        const WCHAR* end; /* end of processed string */
	const WCHAR* p;	  /* search pointer */
	const WCHAR* s;	  /* copy pointer */

	/* extract drive name */
	if (path[0] && path[1]==':') {
		if (drv) {
			*drv++ = *path++;
			*drv++ = *path++;
			*drv = '\0';
		}
	} else if (drv)
		*drv = '\0';

    /* Don't parse colons as stream separators when splitting paths */
    end = path + lstrlenW(path);

	/* search for begin of file extension */
	for(p=end; p>path && *--p!='\\' && *p!='/'; )
		if (*p == '.') {
			end = p;
			break;
		}

	if (ext)
		for(s=end; (*ext=*s++); )
			ext++;

	/* search for end of directory name */
	for(p=end; p>path; )
		if (*--p=='\\' || *p=='/') {
			p++;
			break;
		}

	if (name) {
		for(s=p; s<end; )
			*name++ = *s++;

		*name = '\0';
	}

	if (dir) {
		for(s=path; s<p; )
			*dir++ = *s++;

		*dir = '\0';
	}
}