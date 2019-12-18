#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int matpartcolno; int /*<<< orphan*/ * matpartcolname; int /*<<< orphan*/  mat_groupcolname_list; int /*<<< orphan*/ * partial_grouplist; int /*<<< orphan*/ * partial_seltlist; int /*<<< orphan*/ * matcollist; } ;
typedef  TYPE_1__ MatTableColumnInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 

__attribute__((used)) static void
mattablecolumninfo_init(MatTableColumnInfo *matcolinfo, List *collist, List *tlist, List *grouplist)
{
	matcolinfo->matcollist = collist;
	matcolinfo->partial_seltlist = tlist;
	matcolinfo->partial_grouplist = grouplist;
	matcolinfo->mat_groupcolname_list = NIL;
	matcolinfo->matpartcolno = -1;
	matcolinfo->matpartcolname = NULL;
}