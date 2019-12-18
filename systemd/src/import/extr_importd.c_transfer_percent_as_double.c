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
struct TYPE_4__ {unsigned int progress_percent; } ;
typedef  TYPE_1__ Transfer ;

/* Variables and functions */
 double DBL_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static double transfer_percent_as_double(Transfer *t) {
        assert(t);

        if (t->progress_percent == (unsigned) -1)
                return -DBL_MAX;

        return (double) t->progress_percent / 100.0;
}