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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ Transaction ;
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/ * hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transaction_delete_job (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void transaction_delete_unit(Transaction *tr, Unit *u) {
        Job *j;

        /* Deletes all jobs associated with a certain unit from the
         * transaction */

        while ((j = hashmap_get(tr->jobs, u)))
                transaction_delete_job(tr, j, true);
}