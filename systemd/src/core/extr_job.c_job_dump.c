#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int id; int /*<<< orphan*/  irreversible; int /*<<< orphan*/  state; int /*<<< orphan*/  type; TYPE_1__* unit; } ;
struct TYPE_9__ {char* id; } ;
typedef  TYPE_2__ Job ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (TYPE_2__*,char*,char const*,int,char const*,char*,char*,char const*,char*,char const*,char*,char const*,char*) ; 
 int /*<<< orphan*/  job_may_gc (TYPE_2__*) ; 
 char* job_state_to_string (int /*<<< orphan*/ ) ; 
 char* job_type_to_string (int /*<<< orphan*/ ) ; 
 char* strempty (char const*) ; 
 char* yes_no (int /*<<< orphan*/ ) ; 

void job_dump(Job *j, FILE *f, const char *prefix) {
        assert(j);
        assert(f);

        prefix = strempty(prefix);

        fprintf(f,
                "%s-> Job %u:\n"
                "%s\tAction: %s -> %s\n"
                "%s\tState: %s\n"
                "%s\tIrreversible: %s\n"
                "%s\tMay GC: %s\n",
                prefix, j->id,
                prefix, j->unit->id, job_type_to_string(j->type),
                prefix, job_state_to_string(j->state),
                prefix, yes_no(j->irreversible),
                prefix, yes_no(job_may_gc(j)));
}