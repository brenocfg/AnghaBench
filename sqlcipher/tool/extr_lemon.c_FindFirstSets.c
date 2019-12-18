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
struct symbol {scalar_t__ lambda; scalar_t__ type; int nsubsym; int /*<<< orphan*/  firstset; TYPE_2__** subsym; int /*<<< orphan*/  index; } ;
struct rule {int nrhs; struct symbol** rhs; struct symbol* lhs; struct rule* next; } ;
struct lemon {int nsymbol; int nterminal; struct rule* rule; TYPE_1__** symbols; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int /*<<< orphan*/  firstset; scalar_t__ lambda; } ;

/* Variables and functions */
 scalar_t__ LEMON_FALSE ; 
 scalar_t__ LEMON_TRUE ; 
 scalar_t__ MULTITERMINAL ; 
 scalar_t__ NONTERMINAL ; 
 scalar_t__ SetAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetNew () ; 
 scalar_t__ SetUnion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TERMINAL ; 
 int /*<<< orphan*/  assert (int) ; 

void FindFirstSets(struct lemon *lemp)
{
  int i, j;
  struct rule *rp;
  int progress;

  for(i=0; i<lemp->nsymbol; i++){
    lemp->symbols[i]->lambda = LEMON_FALSE;
  }
  for(i=lemp->nterminal; i<lemp->nsymbol; i++){
    lemp->symbols[i]->firstset = SetNew();
  }

  /* First compute all lambdas */
  do{
    progress = 0;
    for(rp=lemp->rule; rp; rp=rp->next){
      if( rp->lhs->lambda ) continue;
      for(i=0; i<rp->nrhs; i++){
        struct symbol *sp = rp->rhs[i];
        assert( sp->type==NONTERMINAL || sp->lambda==LEMON_FALSE );
        if( sp->lambda==LEMON_FALSE ) break;
      }
      if( i==rp->nrhs ){
        rp->lhs->lambda = LEMON_TRUE;
        progress = 1;
      }
    }
  }while( progress );

  /* Now compute all first sets */
  do{
    struct symbol *s1, *s2;
    progress = 0;
    for(rp=lemp->rule; rp; rp=rp->next){
      s1 = rp->lhs;
      for(i=0; i<rp->nrhs; i++){
        s2 = rp->rhs[i];
        if( s2->type==TERMINAL ){
          progress += SetAdd(s1->firstset,s2->index);
          break;
        }else if( s2->type==MULTITERMINAL ){
          for(j=0; j<s2->nsubsym; j++){
            progress += SetAdd(s1->firstset,s2->subsym[j]->index);
          }
          break;
        }else if( s1==s2 ){
          if( s1->lambda==LEMON_FALSE ) break;
        }else{
          progress += SetUnion(s1->firstset,s2->firstset);
          if( s2->lambda==LEMON_FALSE ) break;
        }
      }
    }
  }while( progress );
  return;
}