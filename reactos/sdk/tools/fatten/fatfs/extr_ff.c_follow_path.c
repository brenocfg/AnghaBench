#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char UINT ;
struct TYPE_8__ {int /*<<< orphan*/  cdir; } ;
struct TYPE_7__ {int* dir; int* fn; TYPE_2__* fs; int /*<<< orphan*/  sclust; } ;
typedef  char TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 int AM_DIR ; 
 size_t DIR_Attr ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_NO_PATH ; 
 scalar_t__ FR_OK ; 
 size_t NSFLAG ; 
 int NS_DOT ; 
 int NS_LAST ; 
 scalar_t__ _FS_RPATH ; 
 scalar_t__ create_name (TYPE_1__*,char const**) ; 
 scalar_t__ dir_find (TYPE_1__*) ; 
 scalar_t__ dir_sdi (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ld_clust (TYPE_2__*,int*) ; 

__attribute__((used)) static
FRESULT follow_path (	/* FR_OK(0): successful, !=0: error code */
	DIR* dp,			/* Directory object to return last directory and found object */
	const TCHAR* path	/* Full-path string to find a file or directory */
)
{
	FRESULT res;
	BYTE *dir, ns;


#if _FS_RPATH
	if (*path == '/' || *path == '\\') {	/* There is a heading separator */
		path++;	dp->sclust = 0;				/* Strip it and start from the root directory */
	} else {								/* No heading separator */
		dp->sclust = dp->fs->cdir;			/* Start from the current directory */
	}
#else
	if (*path == '/' || *path == '\\')		/* Strip heading separator if exist */
		path++;
	dp->sclust = 0;							/* Always start from the root directory */
#endif

	if ((UINT)*path < ' ') {				/* Null path name is the origin directory itself */
		res = dir_sdi(dp, 0);
		dp->dir = 0;
	} else {								/* Follow path */
		for (;;) {
			res = create_name(dp, &path);	/* Get a segment name of the path */
			if (res != FR_OK) break;
			res = dir_find(dp);				/* Find an object with the sagment name */
			ns = dp->fn[NSFLAG];
			if (res != FR_OK) {				/* Failed to find the object */
				if (res == FR_NO_FILE) {	/* Object is not found */
					if (_FS_RPATH && (ns & NS_DOT)) {	/* If dot entry is not exist, */
						dp->sclust = 0; dp->dir = 0;	/* it is the root directory and stay there */
						if (!(ns & NS_LAST)) continue;	/* Continue to follow if not last segment */
						res = FR_OK;					/* Ended at the root directroy. Function completed. */
					} else {							/* Could not find the object */
						if (!(ns & NS_LAST)) res = FR_NO_PATH;	/* Adjust error code if not last segment */
					}
				}
				break;
			}
			if (ns & NS_LAST) break;			/* Last segment matched. Function completed. */
			dir = dp->dir;						/* Follow the sub-directory */
			if (!(dir[DIR_Attr] & AM_DIR)) {	/* It is not a sub-directory and cannot follow */
				res = FR_NO_PATH; break;
			}
			dp->sclust = ld_clust(dp->fs, dir);
		}
	}

	return res;
}