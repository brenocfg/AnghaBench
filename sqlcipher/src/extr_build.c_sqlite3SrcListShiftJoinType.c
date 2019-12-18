#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nSrc; TYPE_2__* a; } ;
struct TYPE_5__ {int /*<<< orphan*/  jointype; } ;
struct TYPE_6__ {TYPE_1__ fg; } ;
typedef  TYPE_3__ SrcList ;

/* Variables and functions */

void sqlite3SrcListShiftJoinType(SrcList *p){
  if( p ){
    int i;
    for(i=p->nSrc-1; i>0; i--){
      p->a[i].fg.jointype = p->a[i-1].fg.jointype;
    }
    p->a[0].fg.jointype = 0;
  }
}