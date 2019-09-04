#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int attr; scalar_t__ name; } ;
struct TYPE_10__ {TYPE_1__ dir_ent; } ;
typedef  int /*<<< orphan*/  DOS_FS ;
typedef  TYPE_2__ DOS_FILE ;

/* Variables and functions */
 int ATTR_DIR ; 
 int /*<<< orphan*/  MODIFY (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSDOS_DOT ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 int /*<<< orphan*/  attr ; 
 int /*<<< orphan*/  auto_rename (TYPE_2__*) ; 
 int /*<<< orphan*/  drop_file (int /*<<< orphan*/ *,TYPE_2__*) ; 
 char* file_name (scalar_t__) ; 
 int get_key (char*,char*) ; 
 int htole32 (int /*<<< orphan*/ ) ; 
 scalar_t__ interactive ; 
 char* path_name (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rename_file (TYPE_2__*) ; 
 int /*<<< orphan*/  size ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_dot(DOS_FS * fs, DOS_FILE * file, int dots)
{
    const char *name;

    name =
	strncmp((const char *)file->dir_ent.name, MSDOS_DOT,
		MSDOS_NAME) ? ".." : ".";
    if (!(file->dir_ent.attr & ATTR_DIR)) {
	printf("%s\n  Is a non-directory.\n", path_name(file));
	if (interactive)
	    printf("1) Drop it\n2) Auto-rename\n3) Rename\n"
		   "4) Convert to directory\n");
#ifndef __REACTOS__
	else
#else
	else if (rw)
#endif
	    printf("  Auto-renaming it.\n");
#ifdef __REACTOS__
	if (rw || interactive) {
#endif
	switch (interactive ? get_key("1234", "?") : '2') {
	case '1':
	    drop_file(fs, file);
	    return 1;
	case '2':
	    auto_rename(file);
	    printf("  Renamed to %s\n", file_name(file->dir_ent.name));
	    return 0;
	case '3':
	    rename_file(file);
	    return 0;
	case '4':
	    MODIFY(file, size, htole32(0));
	    MODIFY(file, attr, file->dir_ent.attr | ATTR_DIR);
	    break;
#ifdef __REACTOS__
		}
#endif
	}
    }
    if (!dots) {
	printf("Root contains directory \"%s\". Dropping it.\n", name);
	drop_file(fs, file);
	return 1;
    }
    return 0;
}