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
struct chmcSection {int /*<<< orphan*/  mark_count; int /*<<< orphan*/  mark_list; } ;
struct chmcResetTableMark {int /*<<< orphan*/  list; int /*<<< orphan*/  at; } ;
struct chmcFile {struct chmcSection** sections; } ;
typedef  int /*<<< orphan*/  UInt64 ;

/* Variables and functions */
 int CHMC_ENOMEM ; 
 int CHMC_NOERR ; 
 int /*<<< orphan*/  _CHMC_RSTTBL_MARK ; 
 int /*<<< orphan*/  assert (struct chmcFile*) ; 
 int /*<<< orphan*/  chmc_dump (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct chmcResetTableMark* malloc (int /*<<< orphan*/ ) ; 

int chmc_compressed_add_mark(struct chmcFile *chm, UInt64 at)
{
	struct chmcSection *section;
	struct chmcResetTableMark *mark;

	assert(chm);

	section = chm->sections[1];

	mark = malloc(_CHMC_RSTTBL_MARK);
	if (mark) {
		mark->at = at;
		chmc_dump("[%d] at: %jd\n", section->mark_count, at);
		list_add_tail(&mark->list, &section->mark_list);
		section->mark_count++;
		return CHMC_NOERR;
	}

	return CHMC_ENOMEM;
}