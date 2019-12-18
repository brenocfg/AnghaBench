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
struct seq_file {int dummy; } ;
struct TYPE_6__ {char* c; int /*<<< orphan*/  ul; int /*<<< orphan*/  l; scalar_t__ ui64; scalar_t__ i64; int /*<<< orphan*/  ui32; int /*<<< orphan*/  i32; } ;
struct TYPE_7__ {int data_type; TYPE_1__ value; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ kstat_named_t ;

/* Variables and functions */
#define  KSTAT_DATA_CHAR 135 
#define  KSTAT_DATA_INT32 134 
#define  KSTAT_DATA_INT64 133 
#define  KSTAT_DATA_LONG 132 
#define  KSTAT_DATA_STRING 131 
#define  KSTAT_DATA_UINT32 130 
#define  KSTAT_DATA_UINT64 129 
#define  KSTAT_DATA_ULONG 128 
 int /*<<< orphan*/  KSTAT_NAMED_STR_BUFLEN (TYPE_2__*) ; 
 char* KSTAT_NAMED_STR_PTR (TYPE_2__*) ; 
 int /*<<< orphan*/  PANIC (char*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int
kstat_seq_show_named(struct seq_file *f, kstat_named_t *knp)
{
	seq_printf(f, "%-31s %-4d ", knp->name, knp->data_type);

	switch (knp->data_type) {
		case KSTAT_DATA_CHAR:
			knp->value.c[15] = '\0'; /* NULL terminate */
			seq_printf(f, "%-16s", knp->value.c);
			break;
		/*
		 * NOTE - We need to be more careful able what tokens are
		 * used for each arch, for now this is correct for x86_64.
		 */
		case KSTAT_DATA_INT32:
			seq_printf(f, "%d", knp->value.i32);
			break;
		case KSTAT_DATA_UINT32:
			seq_printf(f, "%u", knp->value.ui32);
			break;
		case KSTAT_DATA_INT64:
			seq_printf(f, "%lld", (signed long long)knp->value.i64);
			break;
		case KSTAT_DATA_UINT64:
			seq_printf(f, "%llu",
			    (unsigned long long)knp->value.ui64);
			break;
		case KSTAT_DATA_LONG:
			seq_printf(f, "%ld", knp->value.l);
			break;
		case KSTAT_DATA_ULONG:
			seq_printf(f, "%lu", knp->value.ul);
			break;
		case KSTAT_DATA_STRING:
			KSTAT_NAMED_STR_PTR(knp)
				[KSTAT_NAMED_STR_BUFLEN(knp)-1] = '\0';
			seq_printf(f, "%s", KSTAT_NAMED_STR_PTR(knp));
			break;
		default:
			PANIC("Undefined kstat data type %d\n", knp->data_type);
	}

	seq_printf(f, "\n");

	return (0);
}