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
typedef  char UINT ;
typedef  char TCHAR ;

/* Variables and functions */
 scalar_t__ _USE_LFN ; 
 char _VOLUMES ; 

__attribute__((used)) static
int get_ldnumber (		/* Returns logical drive number (-1:invalid drive) */
	const TCHAR** path	/* Pointer to pointer to the path name */
)
{
	const TCHAR *tp, *tt;
	UINT i;
	int vol = -1;
#if _STR_VOLUME_ID		/* Find string drive id */
	static const char* const str[] = {_VOLUME_STRS};
	const char *sp;
	char c;
	TCHAR tc;
#endif


	if (*path) {	/* If the pointer is not a null */
		for (tt = *path; (UINT)*tt >= (_USE_LFN ? ' ' : '!') && *tt != ':'; tt++) ;	/* Find ':' in the path */
		if (*tt == ':') {	/* If a ':' is exist in the path name */
			tp = *path;
			i = *tp++ - '0'; 
			if (i < 10 && tp == tt) {	/* Is there a numeric drive id? */
				if (i < _VOLUMES) {	/* If a drive id is found, get the value and strip it */
					vol = (int)i;
					*path = ++tt;
				}
			}
#if _STR_VOLUME_ID
			 else {	/* No numeric drive number, find string drive id */
				i = 0; tt++;
				do {
					sp = str[i]; tp = *path;
					do {	/* Compare a string drive id with path name */
						c = *sp++; tc = *tp++;
						if (IsLower(tc)) tc -= 0x20;
					} while (c && (TCHAR)c == tc);
				} while ((c || tp != tt) && ++i < _VOLUMES);	/* Repeat for each id until pattern match */
				if (i < _VOLUMES) {	/* If a drive id is found, get the value and strip it */
					vol = (int)i;
					*path = tt;
				}
			}
#endif
			return vol;
		}
#if _FS_RPATH && _VOLUMES >= 2
		vol = CurrVol;	/* Current drive */
#else
		vol = 0;		/* Drive 0 */
#endif
	}
	return vol;
}