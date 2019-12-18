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
struct TYPE_6__ {unsigned int id; } ;
typedef  TYPE_1__ sd_resolve_query ;
struct TYPE_7__ {TYPE_1__** query_array; } ;
typedef  TYPE_2__ sd_resolve ;

/* Variables and functions */
 unsigned int QUERIES_MAX ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

__attribute__((used)) static sd_resolve_query *lookup_query(sd_resolve *resolve, unsigned id) {
        sd_resolve_query *q;

        assert(resolve);

        q = resolve->query_array[id % QUERIES_MAX];
        if (q)
                if (q->id == id)
                        return q;

        return NULL;
}