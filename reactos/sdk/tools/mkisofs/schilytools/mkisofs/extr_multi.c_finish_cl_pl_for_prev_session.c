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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct directory_entry {int de_flags; int /*<<< orphan*/  total_rr_attr_size; int /*<<< orphan*/  rr_attributes; struct directory_entry* parent_rec; TYPE_2__* filedir; } ;
struct directory {int /*<<< orphan*/  extent; TYPE_1__* contents; struct directory* next; struct directory_entry* self; } ;
struct dir_extent_link {struct dir_extent_link* next; struct directory_entry* de; } ;
struct TYPE_6__ {struct directory* subdir; } ;
struct TYPE_5__ {int /*<<< orphan*/  extent; } ;
struct TYPE_4__ {struct directory_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_BAD ; 
 int INHIBIT_ISO9660_ENTRY ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct dir_extent_link* cl_dirs ; 
 int /*<<< orphan*/  comerrno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* find_rr_attribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct dir_extent_link*) ; 
 struct dir_extent_link* re_dirs ; 
 TYPE_3__* reloc_dir ; 
 int /*<<< orphan*/  set_733 (char*,int /*<<< orphan*/ ) ; 

void
finish_cl_pl_for_prev_session()
{
	struct dir_extent_link *re = re_dirs;

	/* for those that were relocated, but NOT to rr_moved */
	re = re_dirs;
	for (; re; re = re->next) {
		if (re->de != NULL) {
			/*
			 * here we have hypothetical case when previous session
			 * was not created by mkisofs and contains relocations
			 */
			struct directory_entry *s_entry = re->de;
			struct directory_entry *s_entry1;
			struct directory *d_entry = reloc_dir->subdir;

			/* do the same as finish_cl_pl_entries */
			if (s_entry->de_flags & INHIBIT_ISO9660_ENTRY) {
				continue;
			}
			while (d_entry) {
				if (d_entry->self == s_entry)
					break;
				d_entry = d_entry->next;
			}
			if (!d_entry) {
				comerrno(EX_BAD, _("Unable to locate directory parent\n"));
			}

			if (s_entry->filedir != NULL && s_entry->parent_rec != NULL) {
				char	*rr_attr;

				/*
				 * First fix the PL pointer in the directory in the
				 * rr_reloc dir
				 */
				s_entry1 = d_entry->contents->next;
				rr_attr = find_rr_attribute(s_entry1->rr_attributes,
					s_entry1->total_rr_attr_size, "PL");
				if (rr_attr != NULL)
					set_733(rr_attr + 4, s_entry->filedir->extent);

				/* Now fix the CL pointer */
				s_entry1 = s_entry->parent_rec;

				rr_attr = find_rr_attribute(s_entry1->rr_attributes,
					s_entry1->total_rr_attr_size, "CL");
				if (rr_attr != NULL)
					set_733(rr_attr + 4, d_entry->extent);
			}
		}
	}
	/* free memory */
	re = re_dirs;
	while (re) {
		struct dir_extent_link *next = re->next;

		free(re);
		re = next;
	}
	re = cl_dirs;
	while (re) {
		struct dir_extent_link *next = re->next;

		free(re);
		re = next;
	}
}