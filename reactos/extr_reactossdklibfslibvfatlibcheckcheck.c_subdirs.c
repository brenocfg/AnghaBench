#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int attr; scalar_t__ name; } ;
struct TYPE_7__ {TYPE_1__ dir_ent; struct TYPE_7__* next; struct TYPE_7__* first; } ;
typedef  int /*<<< orphan*/  FDSC ;
typedef  int /*<<< orphan*/  DOS_FS ;
typedef  TYPE_2__ DOS_FILE ;

/* Variables and functions */
 int ATTR_DIR ; 
 int /*<<< orphan*/  MSDOS_DOT ; 
 int /*<<< orphan*/  MSDOS_DOTDOT ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 int /*<<< orphan*/  file_cd (int /*<<< orphan*/ **,char*) ; 
 TYPE_2__* root ; 
 scalar_t__ scan_dir (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subdirs(DOS_FS * fs, DOS_FILE * parent, FDSC ** cp)
{
    DOS_FILE *walk;

    for (walk = parent ? parent->first : root; walk; walk = walk->next)
	if (walk->dir_ent.attr & ATTR_DIR)
	    if (strncmp((const char *)walk->dir_ent.name, MSDOS_DOT, MSDOS_NAME)
		&& strncmp((const char *)walk->dir_ent.name, MSDOS_DOTDOT,
			   MSDOS_NAME))
		if (scan_dir(fs, walk, file_cd(cp, (char *)walk->dir_ent.name)))
		    return 1;
    return 0;
}