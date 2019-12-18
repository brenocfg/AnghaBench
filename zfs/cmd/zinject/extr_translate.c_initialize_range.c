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
struct TYPE_3__ {int zi_start; unsigned long long zi_end; int zi_object; int zi_level; } ;
typedef  TYPE_1__ zinject_record_t ;
typedef  int err_type_t ;
typedef  int /*<<< orphan*/  dnode_phys_t ;

/* Variables and functions */
#define  TYPE_DATA 129 
#define  TYPE_DNODE 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 void* strtoull (char*,char**,int) ; 

__attribute__((used)) static int
initialize_range(err_type_t type, int level, char *range,
    zinject_record_t *record)
{
	/*
	 * Determine the numeric range from the string.
	 */
	if (range == NULL) {
		/*
		 * If range is unspecified, set the range to [0,-1], which
		 * indicates that the whole object should be treated as an
		 * error.
		 */
		record->zi_start = 0;
		record->zi_end = -1ULL;
	} else {
		char *end;

		/* XXX add support for suffixes */
		record->zi_start = strtoull(range, &end, 10);


		if (*end == '\0')
			record->zi_end = record->zi_start + 1;
		else if (*end == ',')
			record->zi_end = strtoull(end + 1, &end, 10);

		if (*end != '\0') {
			(void) fprintf(stderr, "invalid range '%s': must be "
			    "a numeric range of the form 'start[,end]'\n",
			    range);
			return (-1);
		}
	}

	switch (type) {
	default:
		break;
	case TYPE_DATA:
		break;

	case TYPE_DNODE:
		/*
		 * If this is a request to inject faults into the dnode, then we
		 * must translate the current (objset,object) pair into an
		 * offset within the metadnode for the objset.  Specifying any
		 * kind of range with type 'dnode' is illegal.
		 */
		if (range != NULL) {
			(void) fprintf(stderr, "range cannot be specified when "
			    "type is 'dnode'\n");
			return (-1);
		}

		record->zi_start = record->zi_object * sizeof (dnode_phys_t);
		record->zi_end = record->zi_start + sizeof (dnode_phys_t);
		record->zi_object = 0;
		break;
	}

	record->zi_level = level;

	return (0);
}