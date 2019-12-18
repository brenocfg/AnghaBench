#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  current_location; } ;
typedef  TYPE_1__ sd_journal ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  detach_location (TYPE_1__*) ; 
 int /*<<< orphan*/  zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_location(sd_journal *j) {
        assert(j);

        detach_location(j);
        zero(j->current_location);
}