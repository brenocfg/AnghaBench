#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct directory_entry {struct directory_entry* next; int /*<<< orphan*/  filedir; struct directory_entry* parent_rec; } ;
struct dir_extent_link {scalar_t__ extent; struct directory_entry* de; struct dir_extent_link* next; } ;
struct TYPE_2__ {struct directory_entry* contents; } ;

/* Variables and functions */
 struct dir_extent_link* cl_dirs ; 
 struct dir_extent_link* re_dirs ; 
 TYPE_1__* reloc_dir ; 

void
match_cl_re_entries()
{
	struct dir_extent_link *re = re_dirs;

	/* for each relocated directory */
	for (; re; re = re->next) {
		struct dir_extent_link *cl = cl_dirs;

		for (; cl; cl = cl->next) {
			/* find a place where it was relocated from */
			if (cl->extent == re->extent) {
				/* set link to that place */
				re->de->parent_rec = cl->de;
				re->de->filedir = cl->de->filedir;

				/*
				 * see if it is in rr_moved
				 */
				if (reloc_dir != NULL) {
					struct directory_entry *rr_moved_e = reloc_dir->contents;

					for (; rr_moved_e; rr_moved_e = rr_moved_e->next) {
						/* yes it is */
						if (re->de == rr_moved_e) {
							/* forget it */
							re->de = NULL;
						}
					}
				}
				break;
			}
		}
	}
}