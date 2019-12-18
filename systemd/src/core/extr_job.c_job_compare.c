#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UnitDependency ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ ignore_order; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int IN_SET (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ JOB_NOP ; 
 scalar_t__ JOB_RESTART ; 
 scalar_t__ JOB_STOP ; 
 scalar_t__ UNIT_AFTER ; 
 scalar_t__ UNIT_BEFORE ; 
 scalar_t__ _JOB_TYPE_MAX_IN_TRANSACTION ; 
 int /*<<< orphan*/  assert (int) ; 

int job_compare(Job *a, Job *b, UnitDependency assume_dep) {
        assert(a->type < _JOB_TYPE_MAX_IN_TRANSACTION);
        assert(b->type < _JOB_TYPE_MAX_IN_TRANSACTION);
        assert(IN_SET(assume_dep, UNIT_AFTER, UNIT_BEFORE));

        /* Trivial cases first */
        if (a->type == JOB_NOP || b->type == JOB_NOP)
                return 0;

        if (a->ignore_order || b->ignore_order)
                return 0;

        if (assume_dep == UNIT_AFTER)
                return -job_compare(b, a, UNIT_BEFORE);

        /* Let's make it simple, JOB_STOP goes always first (in case both ua and ub stop,
         * then ub's stop goes first anyway).
         * JOB_RESTART is JOB_STOP in disguise (before it is patched to JOB_START). */
        if (IN_SET(b->type, JOB_STOP, JOB_RESTART))
                return 1;
        else
                return -1;
}