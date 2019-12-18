#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct state {struct action* ap; struct config* cfp; } ;
struct rule {int /*<<< orphan*/  ruleline; scalar_t__ canReduce; struct rule* next; } ;
struct lemon {int nstate; int nterminal; int /*<<< orphan*/  errorcnt; int /*<<< orphan*/  filename; struct rule* rule; struct state** sorted; int /*<<< orphan*/  nconflict; TYPE_2__* startRule; scalar_t__ start; struct symbol** symbols; } ;
struct config {scalar_t__ dot; TYPE_1__* rp; int /*<<< orphan*/  fws; struct config* next; } ;
struct TYPE_8__ {TYPE_3__* rp; } ;
struct action {scalar_t__ sp; scalar_t__ type; TYPE_4__ x; struct action* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  canReduce; } ;
struct TYPE_6__ {struct symbol* lhs; } ;
struct TYPE_5__ {scalar_t__ nrhs; } ;

/* Variables and functions */
 scalar_t__ ACCEPT ; 
 int /*<<< orphan*/  Action_add (struct action**,scalar_t__,struct symbol*,char*) ; 
 struct action* Action_sort (struct action*) ; 
 int /*<<< orphan*/  ErrorMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LEMON_FALSE ; 
 int /*<<< orphan*/  LEMON_TRUE ; 
 scalar_t__ REDUCE ; 
 scalar_t__ SetFind (int /*<<< orphan*/ ,int) ; 
 struct symbol* Symbol_find (scalar_t__) ; 
 scalar_t__ resolve_conflict (struct action*,struct action*) ; 

void FindActions(struct lemon *lemp)
{
  int i,j;
  struct config *cfp;
  struct state *stp;
  struct symbol *sp;
  struct rule *rp;

  /* Add all of the reduce actions
  ** A reduce action is added for each element of the followset of
  ** a configuration which has its dot at the extreme right.
  */
  for(i=0; i<lemp->nstate; i++){   /* Loop over all states */
    stp = lemp->sorted[i];
    for(cfp=stp->cfp; cfp; cfp=cfp->next){  /* Loop over all configurations */
      if( cfp->rp->nrhs==cfp->dot ){        /* Is dot at extreme right? */
        for(j=0; j<lemp->nterminal; j++){
          if( SetFind(cfp->fws,j) ){
            /* Add a reduce action to the state "stp" which will reduce by the
            ** rule "cfp->rp" if the lookahead symbol is "lemp->symbols[j]" */
            Action_add(&stp->ap,REDUCE,lemp->symbols[j],(char *)cfp->rp);
          }
        }
      }
    }
  }

  /* Add the accepting token */
  if( lemp->start ){
    sp = Symbol_find(lemp->start);
    if( sp==0 ) sp = lemp->startRule->lhs;
  }else{
    sp = lemp->startRule->lhs;
  }
  /* Add to the first state (which is always the starting state of the
  ** finite state machine) an action to ACCEPT if the lookahead is the
  ** start nonterminal.  */
  Action_add(&lemp->sorted[0]->ap,ACCEPT,sp,0);

  /* Resolve conflicts */
  for(i=0; i<lemp->nstate; i++){
    struct action *ap, *nap;
    stp = lemp->sorted[i];
    /* assert( stp->ap ); */
    stp->ap = Action_sort(stp->ap);
    for(ap=stp->ap; ap && ap->next; ap=ap->next){
      for(nap=ap->next; nap && nap->sp==ap->sp; nap=nap->next){
         /* The two actions "ap" and "nap" have the same lookahead.
         ** Figure out which one should be used */
         lemp->nconflict += resolve_conflict(ap,nap);
      }
    }
  }

  /* Report an error for each rule that can never be reduced. */
  for(rp=lemp->rule; rp; rp=rp->next) rp->canReduce = LEMON_FALSE;
  for(i=0; i<lemp->nstate; i++){
    struct action *ap;
    for(ap=lemp->sorted[i]->ap; ap; ap=ap->next){
      if( ap->type==REDUCE ) ap->x.rp->canReduce = LEMON_TRUE;
    }
  }
  for(rp=lemp->rule; rp; rp=rp->next){
    if( rp->canReduce ) continue;
    ErrorMsg(lemp->filename,rp->ruleline,"This rule can not be reduced.\n");
    lemp->errorcnt++;
  }
}