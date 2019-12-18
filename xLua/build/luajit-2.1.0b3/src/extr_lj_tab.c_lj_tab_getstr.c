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
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_5__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Node ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 TYPE_1__* hashstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* nextnode (TYPE_1__*) ; 
 int /*<<< orphan*/ * strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

cTValue *lj_tab_getstr(GCtab *t, GCstr *key)
{
  Node *n = hashstr(t, key);
  do {
    if (tvisstr(&n->key) && strV(&n->key) == key)
      return &n->val;
  } while ((n = nextnode(n)));
  return NULL;
}