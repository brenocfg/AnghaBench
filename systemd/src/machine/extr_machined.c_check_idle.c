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
struct TYPE_3__ {int /*<<< orphan*/  machines; scalar_t__ operations; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int hashmap_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_gc (TYPE_1__*,int) ; 

__attribute__((used)) static bool check_idle(void *userdata) {
        Manager *m = userdata;

        if (m->operations)
                return false;

        manager_gc(m, true);

        return hashmap_isempty(m->machines);
}