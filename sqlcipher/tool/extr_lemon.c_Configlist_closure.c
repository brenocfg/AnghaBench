#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol {scalar_t__ type; int nsubsym; scalar_t__ lambda; int /*<<< orphan*/  firstset; TYPE_1__** subsym; int /*<<< orphan*/  index; struct rule* rule; int /*<<< orphan*/  name; } ;
struct rule {int nrhs; struct symbol** rhs; struct rule* nextlhs; int /*<<< orphan*/  line; } ;
struct lemon {int /*<<< orphan*/  errorcnt; int /*<<< orphan*/  filename; struct symbol* errsym; } ;
struct config {int dot; int /*<<< orphan*/  fplp; int /*<<< orphan*/  fws; struct rule* rp; struct config* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 struct config* Configlist_add (struct rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ErrorMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ LEMON_FALSE ; 
 scalar_t__ MULTITERMINAL ; 
 scalar_t__ NONTERMINAL ; 
 int /*<<< orphan*/  Plink_add (int /*<<< orphan*/ *,struct config*) ; 
 int /*<<< orphan*/  SetAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetUnion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TERMINAL ; 
 int /*<<< orphan*/  assert (int) ; 
 struct config* current ; 
 scalar_t__ currentend ; 

void Configlist_closure(struct lemon *lemp)
{
  struct config *cfp, *newcfp;
  struct rule *rp, *newrp;
  struct symbol *sp, *xsp;
  int i, dot;

  assert( currentend!=0 );
  for(cfp=current; cfp; cfp=cfp->next){
    rp = cfp->rp;
    dot = cfp->dot;
    if( dot>=rp->nrhs ) continue;
    sp = rp->rhs[dot];
    if( sp->type==NONTERMINAL ){
      if( sp->rule==0 && sp!=lemp->errsym ){
        ErrorMsg(lemp->filename,rp->line,"Nonterminal \"%s\" has no rules.",
          sp->name);
        lemp->errorcnt++;
      }
      for(newrp=sp->rule; newrp; newrp=newrp->nextlhs){
        newcfp = Configlist_add(newrp,0);
        for(i=dot+1; i<rp->nrhs; i++){
          xsp = rp->rhs[i];
          if( xsp->type==TERMINAL ){
            SetAdd(newcfp->fws,xsp->index);
            break;
          }else if( xsp->type==MULTITERMINAL ){
            int k;
            for(k=0; k<xsp->nsubsym; k++){
              SetAdd(newcfp->fws, xsp->subsym[k]->index);
            }
            break;
          }else{
            SetUnion(newcfp->fws,xsp->firstset);
            if( xsp->lambda==LEMON_FALSE ) break;
          }
        }
        if( i==rp->nrhs ) Plink_add(&cfp->fplp,newcfp);
      }
    }
  }
  return;
}