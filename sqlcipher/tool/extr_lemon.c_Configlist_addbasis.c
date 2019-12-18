#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rule {int dummy; } ;
struct config {int dot; struct config* bp; struct config* next; scalar_t__ bplp; scalar_t__ fplp; scalar_t__ stp; int /*<<< orphan*/  fws; struct rule* rp; } ;

/* Variables and functions */
 struct config* Configtable_find (struct config*) ; 
 int /*<<< orphan*/  Configtable_insert (struct config*) ; 
 int /*<<< orphan*/  SetNew () ; 
 int /*<<< orphan*/  assert (int) ; 
 struct config** basisend ; 
 struct config** currentend ; 
 struct config* newconfig () ; 

struct config *Configlist_addbasis(struct rule *rp, int dot)
{
  struct config *cfp, model;

  assert( basisend!=0 );
  assert( currentend!=0 );
  model.rp = rp;
  model.dot = dot;
  cfp = Configtable_find(&model);
  if( cfp==0 ){
    cfp = newconfig();
    cfp->rp = rp;
    cfp->dot = dot;
    cfp->fws = SetNew();
    cfp->stp = 0;
    cfp->fplp = cfp->bplp = 0;
    cfp->next = 0;
    cfp->bp = 0;
    *currentend = cfp;
    currentend = &cfp->next;
    *basisend = cfp;
    basisend = &cfp->bp;
    Configtable_insert(cfp);
  }
  return cfp;
}