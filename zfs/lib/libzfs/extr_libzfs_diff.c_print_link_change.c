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
struct TYPE_6__ {int /*<<< orphan*/  zs_mode; scalar_t__* zs_ctime; } ;
typedef  TYPE_1__ zfs_stat_t ;
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_7__ {scalar_t__ classify; scalar_t__ timestamped; } ;
typedef  TYPE_2__ differ_info_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ZDIFF_MODIFIED ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_cmn (int /*<<< orphan*/ *,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  print_what (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_link_change(FILE *fp, differ_info_t *di, int delta, const char *file,
    zfs_stat_t *isb)
{
	if (di->timestamped)
		(void) fprintf(fp, "%10lld.%09lld\t",
		    (longlong_t)isb->zs_ctime[0],
		    (longlong_t)isb->zs_ctime[1]);
	(void) fprintf(fp, "%c\t", ZDIFF_MODIFIED);
	if (di->classify) {
		print_what(fp, isb->zs_mode);
		(void) fprintf(fp, "\t");
	}
	print_cmn(fp, di, file);
	(void) fprintf(fp, "\t(%+d)", delta);
	(void) fprintf(fp, "\n");
}