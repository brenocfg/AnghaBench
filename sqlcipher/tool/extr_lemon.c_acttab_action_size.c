#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nAction; TYPE_1__* aAction; } ;
typedef  TYPE_2__ acttab ;
struct TYPE_4__ {scalar_t__ lookahead; } ;

/* Variables and functions */

int acttab_action_size(acttab *p){
  int n = p->nAction;
  while( n>0 && p->aAction[n-1].lookahead<0 ){ n--; }
  return n;
}