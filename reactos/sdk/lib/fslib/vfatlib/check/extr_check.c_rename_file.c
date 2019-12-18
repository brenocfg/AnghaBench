#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int lcase; int attr; struct TYPE_6__* name; } ;
struct TYPE_5__ {TYPE_3__ dir_ent; int /*<<< orphan*/  offset; int /*<<< orphan*/  lfn_offset; scalar_t__ lfn; } ;
typedef  TYPE_1__ DOS_FILE ;

/* Variables and functions */
 int ATTR_DIR ; 
 int ATTR_VOLUME ; 
 int FAT_NO_83NAME ; 
 scalar_t__ MSDOS_NAME ; 
 int /*<<< orphan*/  VfatPrint (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ file_cvt (unsigned char*,TYPE_3__*) ; 
 int /*<<< orphan*/  fs_write (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  lfn_fix_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strrchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rename_file(DOS_FILE * file)
{
#ifndef __REACTOS__
    unsigned char name[46];
    unsigned char *walk, *here;
#endif

    if (!file->offset) {
#ifndef __REACTOS__
	printf("Cannot rename FAT32 root dir\n");
#else
	VfatPrint( "Cannot rename FAT32 root dir\n" );
#endif
	return;			/* cannot rename FAT32 root dir */
    }
    while (1) {
#ifndef __REACTOS__
	printf("New name: ");
	fflush(stdout);
	if (fgets((char *)name, 45, stdin)) {
	    if ((here = (unsigned char *)strchr((const char *)name, '\n')))
		*here = 0;
	    for (walk = (unsigned char *)strrchr((const char *)name, 0);
		 walk >= name && (*walk == ' ' || *walk == '\t'); walk--) ;
	    walk[1] = 0;
	    for (walk = name; *walk == ' ' || *walk == '\t'; walk++) ;
	    if (file_cvt(walk, file->dir_ent.name)) {
		if (file->dir_ent.lcase & FAT_NO_83NAME) {
		    /* as we only assign a new 8.3 filename, reset flag that 8.3 name is not
		       present */
		    file->dir_ent.lcase &= ~FAT_NO_83NAME;
		    /* reset the attributes, only keep DIR and VOLUME */
		    file->dir_ent.attr &= ~(ATTR_DIR | ATTR_VOLUME);
		    fs_write(file->offset, MSDOS_NAME + 2, &file->dir_ent);
		} else {
		    fs_write(file->offset, MSDOS_NAME, file->dir_ent.name);
		}
		if (file->lfn)
		    lfn_fix_checksum(file->lfn_offset, file->offset,
				     (const char *)file->dir_ent.name);
		return;
	    }
	}
#else
    return;
#endif
    }
}