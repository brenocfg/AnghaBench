#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct state {int iDfltReduce; scalar_t__ autoReduce; scalar_t__ pDfltReduce; int statenum; scalar_t__ nNtAct; scalar_t__ nTknAct; struct action* ap; void* iNtOfst; void* iTknOfst; } ;
struct lemon {int nstate; scalar_t__ nterminal; scalar_t__ nsymbol; int nxstate; struct state** sorted; } ;
struct TYPE_4__ {scalar_t__ rp; } ;
struct action {TYPE_2__ x; TYPE_1__* sp; struct action* next; } ;
struct TYPE_3__ {scalar_t__ index; } ;

/* Variables and functions */
 void* NO_OFFSET ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_action (struct lemon*,struct action*) ; 
 int /*<<< orphan*/  qsort (struct state**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stateResortCompare ; 

void ResortStates(struct lemon *lemp)
{
  int i;
  struct state *stp;
  struct action *ap;

  for(i=0; i<lemp->nstate; i++){
    stp = lemp->sorted[i];
    stp->nTknAct = stp->nNtAct = 0;
    stp->iDfltReduce = -1; /* Init dflt action to "syntax error" */
    stp->iTknOfst = NO_OFFSET;
    stp->iNtOfst = NO_OFFSET;
    for(ap=stp->ap; ap; ap=ap->next){
      int iAction = compute_action(lemp,ap);
      if( iAction>=0 ){
        if( ap->sp->index<lemp->nterminal ){
          stp->nTknAct++;
        }else if( ap->sp->index<lemp->nsymbol ){
          stp->nNtAct++;
        }else{
          assert( stp->autoReduce==0 || stp->pDfltReduce==ap->x.rp );
          stp->iDfltReduce = iAction;
        }
      }
    }
  }
  qsort(&lemp->sorted[1], lemp->nstate-1, sizeof(lemp->sorted[0]),
        stateResortCompare);
  for(i=0; i<lemp->nstate; i++){
    lemp->sorted[i]->statenum = i;
  }
  lemp->nxstate = lemp->nstate;
  while( lemp->nxstate>1 && lemp->sorted[lemp->nxstate-1]->autoReduce ){
    lemp->nxstate--;
  }
}