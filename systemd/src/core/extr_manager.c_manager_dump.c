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
struct TYPE_13__ {int /*<<< orphan*/  monotonic; int /*<<< orphan*/  realtime; } ;
typedef  TYPE_1__ dual_timestamp ;
struct TYPE_14__ {TYPE_1__* timestamps; } ;
typedef  scalar_t__ ManagerTimestamp ;
typedef  TYPE_2__ Manager ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int CONST_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  FORMAT_TIMESTAMP_MAX ; 
 scalar_t__ _MANAGER_TIMESTAMP_MAX ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ dual_timestamp_is_set (TYPE_1__ const*) ; 
 char* format_timespan (char*,int,int /*<<< orphan*/ ,int) ; 
 char* format_timestamp (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (TYPE_2__*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  manager_dump_jobs (TYPE_2__*,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  manager_dump_units (TYPE_2__*,TYPE_2__*,char const*) ; 
 char* manager_timestamp_to_string (scalar_t__) ; 
 char* strempty (char const*) ; 
 scalar_t__ timestamp_is_set (int /*<<< orphan*/ ) ; 

void manager_dump(Manager *m, FILE *f, const char *prefix) {
        ManagerTimestamp q;

        assert(m);
        assert(f);

        for (q = 0; q < _MANAGER_TIMESTAMP_MAX; q++) {
                const dual_timestamp *t = m->timestamps + q;
                char buf[CONST_MAX(FORMAT_TIMESPAN_MAX, FORMAT_TIMESTAMP_MAX)];

                if (dual_timestamp_is_set(t))
                        fprintf(f, "%sTimestamp %s: %s\n",
                                strempty(prefix),
                                manager_timestamp_to_string(q),
                                timestamp_is_set(t->realtime) ? format_timestamp(buf, sizeof buf, t->realtime) :
                                                                format_timespan(buf, sizeof buf, t->monotonic, 1));
        }

        manager_dump_units(m, f, prefix);
        manager_dump_jobs(m, f, prefix);
}