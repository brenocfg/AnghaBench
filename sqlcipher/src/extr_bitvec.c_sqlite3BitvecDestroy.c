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
struct TYPE_5__ {TYPE_2__** apSub; } ;
struct TYPE_6__ {TYPE_1__ u; scalar_t__ iDivisor; } ;
typedef  TYPE_2__ Bitvec ;

/* Variables and functions */
 unsigned int BITVEC_NPTR ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

void sqlite3BitvecDestroy(Bitvec *p){
  if( p==0 ) return;
  if( p->iDivisor ){
    unsigned int i;
    for(i=0; i<BITVEC_NPTR; i++){
      sqlite3BitvecDestroy(p->u.apSub[i]);
    }
  }
  sqlite3_free(p);
}