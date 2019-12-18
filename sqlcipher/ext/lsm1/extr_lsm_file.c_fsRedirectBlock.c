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
struct TYPE_5__ {int n; TYPE_1__* a; } ;
struct TYPE_4__ {int iFrom; int iTo; } ;
typedef  TYPE_2__ Redirect ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int fsRedirectBlock(Redirect *p, int iBlk){
  if( p ){
    int i;
    for(i=0; i<p->n; i++){
      if( iBlk==p->a[i].iFrom ) return p->a[i].iTo;
    }
  }
  assert( iBlk!=0 );
  return iBlk;
}