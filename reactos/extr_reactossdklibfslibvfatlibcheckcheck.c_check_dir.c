#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int attr; scalar_t__ name; } ;
struct TYPE_14__ {struct TYPE_14__* next; TYPE_1__ dir_ent; struct TYPE_14__* parent; } ;
typedef  int /*<<< orphan*/  DOS_FS ;
typedef  TYPE_2__ DOS_FILE ;

/* Variables and functions */
 int ATTR_VOLUME ; 
 int /*<<< orphan*/  DELETED_FLAG ; 
 int /*<<< orphan*/  MODIFY (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSDOS_DOT ; 
 int /*<<< orphan*/  MSDOS_DOTDOT ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 int /*<<< orphan*/  auto_rename (TYPE_2__*) ; 
 scalar_t__ bad_name (TYPE_2__*) ; 
 int /*<<< orphan*/  drop_file (int /*<<< orphan*/ *,TYPE_2__*) ; 
 char* file_name (scalar_t__) ; 
 char* file_stat (TYPE_2__*) ; 
 int get_key (char*,char*) ; 
 scalar_t__ handle_dot (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ interactive ; 
 int /*<<< orphan*/  memcmp (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * name ; 
 char* path_name (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  rename_file (TYPE_2__*) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_file (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_dir(DOS_FS * fs, DOS_FILE ** root, int dots)
{
    DOS_FILE *parent, **walk, **scan;
    int dot, dotdot, skip, redo;
    int good, bad;

    if (!*root)
	return 0;
    parent = (*root)->parent;
    good = bad = 0;
    for (walk = root; *walk; walk = &(*walk)->next)
	if (bad_name(*walk))
	    bad++;
	else
	    good++;
    if (*root && parent && good + bad > 4 && bad > good / 2) {
	printf("%s\n  Has a large number of bad entries. (%d/%d)\n",
	       path_name(parent), bad, good + bad);
	if (!dots)
	    printf("  Not dropping root directory.\n");
#ifndef __REACTOS__
	else if (!interactive)
#else
	else if (!interactive || !rw)
#endif
	    printf("  Not dropping it in auto-mode.\n");
	else if (get_key("yn", "Drop directory ? (y/n)") == 'y') {
	    truncate_file(fs, parent, 0);
	    MODIFY(parent, name[0], DELETED_FLAG);
	    /* buglet: deleted directory stays in the list. */
	    return 1;
	}
    }
    dot = dotdot = redo = 0;
    walk = root;
    while (*walk) {
	if (!strncmp
	    ((const char *)((*walk)->dir_ent.name), MSDOS_DOT, MSDOS_NAME)
	    || !strncmp((const char *)((*walk)->dir_ent.name), MSDOS_DOTDOT,
			MSDOS_NAME)) {
	    if (handle_dot(fs, *walk, dots)) {
		*walk = (*walk)->next;
		continue;
	    }
	    if (!strncmp
		((const char *)((*walk)->dir_ent.name), MSDOS_DOT, MSDOS_NAME))
		dot++;
	    else
		dotdot++;
	}
	if (!((*walk)->dir_ent.attr & ATTR_VOLUME) && bad_name(*walk)) {
#ifndef __REACTOS__
	    puts(path_name(*walk));
	    printf("  Bad short file name (%s).\n",
		   file_name((*walk)->dir_ent.name));
#else
	    printf("%s\n  Bad short file name (%s).\n",
		   path_name(*walk), file_name((*walk)->dir_ent.name));
#endif
	    if (interactive)
		printf("1) Drop file\n2) Rename file\n3) Auto-rename\n"
		       "4) Keep it\n");
	    else
#ifdef __REACTOS__
	    if (rw)
#endif
		printf("  Auto-renaming it.\n");
#ifdef __REACTOS__
	    if (rw || interactive) {
#endif
	    switch (interactive ? get_key("1234", "?") : '3') {
	    case '1':
		drop_file(fs, *walk);
		walk = &(*walk)->next;
		continue;
	    case '2':
		rename_file(*walk);
		redo = 1;
		break;
	    case '3':
		auto_rename(*walk);
		printf("  Renamed to %s\n", file_name((*walk)->dir_ent.name));
		break;
	    case '4':
		break;
#ifdef __REACTOS__
		    }
#endif
	    }
	}
	/* don't check for duplicates of the volume label */
	if (!((*walk)->dir_ent.attr & ATTR_VOLUME)) {
	    scan = &(*walk)->next;
	    skip = 0;
	    while (*scan && !skip) {
		if (!((*scan)->dir_ent.attr & ATTR_VOLUME) &&
		    !memcmp((*walk)->dir_ent.name, (*scan)->dir_ent.name,
			    MSDOS_NAME)) {
		    printf("%s\n  Duplicate directory entry.\n  First  %s\n",
			   path_name(*walk), file_stat(*walk));
		    printf("  Second %s\n", file_stat(*scan));
		    if (interactive)
			printf
			    ("1) Drop first\n2) Drop second\n3) Rename first\n"
			     "4) Rename second\n5) Auto-rename first\n"
			     "6) Auto-rename second\n");
		    else
#ifdef __REACTOS__
		    if (rw)
#endif
			printf("  Auto-renaming second.\n");
#ifdef __REACTOS__
		    if (rw || interactive) {
#endif
		    switch (interactive ? get_key("123456", "?") : '6') {
		    case '1':
			drop_file(fs, *walk);
			*walk = (*walk)->next;
			skip = 1;
			break;
		    case '2':
			drop_file(fs, *scan);
			*scan = (*scan)->next;
			continue;
		    case '3':
			rename_file(*walk);
			printf("  Renamed to %s\n", path_name(*walk));
			redo = 1;
			break;
		    case '4':
			rename_file(*scan);
			printf("  Renamed to %s\n", path_name(*walk));
			redo = 1;
			break;
		    case '5':
			auto_rename(*walk);
			printf("  Renamed to %s\n",
			       file_name((*walk)->dir_ent.name));
			break;
		    case '6':
			auto_rename(*scan);
			printf("  Renamed to %s\n",
			       file_name((*scan)->dir_ent.name));
			break;
#ifdef __REACTOS__
			    }
#endif
		    }
		}
		scan = &(*scan)->next;
	    }
	    if (skip)
		continue;
	}
	if (!redo)
	    walk = &(*walk)->next;
	else {
	    walk = root;
	    dot = dotdot = redo = 0;
	}
    }
    if (dots && !dot)
	printf("%s\n  \".\" is missing. Can't fix this yet.\n",
	       path_name(parent));
    if (dots && !dotdot)
	printf("%s\n  \"..\" is missing. Can't fix this yet.\n",
	       path_name(parent));
    return 0;
}