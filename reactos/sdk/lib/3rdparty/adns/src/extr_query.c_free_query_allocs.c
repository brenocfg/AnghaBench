#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_1__ allocnode ;
typedef  TYPE_2__* adns_query ;
struct TYPE_9__ {TYPE_1__* head; } ;
struct TYPE_8__ {TYPE_1__* query_dgram; int /*<<< orphan*/  search_vb; int /*<<< orphan*/  vb; TYPE_6__ allocations; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (TYPE_6__) ; 
 int /*<<< orphan*/  adns__vbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_children (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void free_query_allocs(adns_query qu) {
  allocnode *an, *ann;

  cancel_children(qu);
  for (an= qu->allocations.head; an; an= ann) { ann= an->next; free(an); }
  LIST_INIT(qu->allocations);
  adns__vbuf_free(&qu->vb);
  adns__vbuf_free(&qu->search_vb);
  free(qu->query_dgram);
  qu->query_dgram= 0;
}