#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {size_t hmask; int /*<<< orphan*/  node; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ Node ;
typedef  TYPE_2__ GCtab ;

/* Variables and functions */
 size_t countint (int /*<<< orphan*/ *,size_t*) ; 
 TYPE_1__* noderef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t counthash(const GCtab *t, uint32_t *bins, uint32_t *narray)
{
  uint32_t total, na, i, hmask = t->hmask;
  Node *node = noderef(t->node);
  for (total = na = 0, i = 0; i <= hmask; i++) {
    Node *n = &node[i];
    if (!tvisnil(&n->val)) {
      na += countint(&n->key, bins);
      total++;
    }
  }
  *narray += na;
  return total;
}