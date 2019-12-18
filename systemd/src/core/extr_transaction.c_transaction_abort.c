#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ Transaction ;
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * hashmap_first (int /*<<< orphan*/ ) ; 
 TYPE_1__* hashmap_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transaction_delete_job (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void transaction_abort(Transaction *tr) {
        Job *j;

        assert(tr);

        while ((j = hashmap_first(tr->jobs)))
                transaction_delete_job(tr, j, false);

        assert(hashmap_isempty(tr->jobs));
}