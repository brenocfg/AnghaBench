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
struct entry {char* name; scalar_t__ is_dir; } ;

/* Variables and functions */
 int strcmp (char*,char*) ; 

__attribute__((used)) static int cmp_entry(const void *av, const void *bv)
{
	const struct entry *a = av;
	const struct entry *b = bv;
	/* "." first */
	if (a->name[0] == '.' && a->name[1] == 0) return -1;
	if (b->name[0] == '.' && b->name[1] == 0) return 1;
	/* ".." second */
	if (a->name[0] == '.' && a->name[1] == '.' && a->name[2] == 0) return -1;
	if (b->name[0] == '.' && b->name[1] == '.' && b->name[2] == 0) return 1;
	/* directories before files */
	if (a->is_dir && !b->is_dir) return -1;
	if (b->is_dir && !a->is_dir) return 1;
	/* then alphabetically */
	return strcmp(a->name, b->name);
}