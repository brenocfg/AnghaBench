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
struct state {struct config* bp; scalar_t__ ap; scalar_t__ statenum; struct config* cfp; } ;
struct lemon {int /*<<< orphan*/  nstate; } ;
struct config {scalar_t__ bplp; scalar_t__ fplp; struct config* bp; } ;

/* Variables and functions */
 struct config* Configlist_basis () ; 
 int /*<<< orphan*/  Configlist_closure (struct lemon*) ; 
 int /*<<< orphan*/  Configlist_eat (struct config*) ; 
 struct config* Configlist_return () ; 
 int /*<<< orphan*/  Configlist_sort () ; 
 int /*<<< orphan*/  Configlist_sortbasis () ; 
 int /*<<< orphan*/  MemoryCheck (struct state*) ; 
 int /*<<< orphan*/  Plink_copy (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  Plink_delete (scalar_t__) ; 
 struct state* State_find (struct config*) ; 
 int /*<<< orphan*/  State_insert (struct state*,struct config*) ; 
 struct state* State_new () ; 
 int /*<<< orphan*/  buildshifts (struct lemon*,struct state*) ; 

struct state *getstate(struct lemon *lemp)
{
  struct config *cfp, *bp;
  struct state *stp;

  /* Extract the sorted basis of the new state.  The basis was constructed
  ** by prior calls to "Configlist_addbasis()". */
  Configlist_sortbasis();
  bp = Configlist_basis();

  /* Get a state with the same basis */
  stp = State_find(bp);
  if( stp ){
    /* A state with the same basis already exists!  Copy all the follow-set
    ** propagation links from the state under construction into the
    ** preexisting state, then return a pointer to the preexisting state */
    struct config *x, *y;
    for(x=bp, y=stp->bp; x && y; x=x->bp, y=y->bp){
      Plink_copy(&y->bplp,x->bplp);
      Plink_delete(x->fplp);
      x->fplp = x->bplp = 0;
    }
    cfp = Configlist_return();
    Configlist_eat(cfp);
  }else{
    /* This really is a new state.  Construct all the details */
    Configlist_closure(lemp);    /* Compute the configuration closure */
    Configlist_sort();           /* Sort the configuration closure */
    cfp = Configlist_return();   /* Get a pointer to the config list */
    stp = State_new();           /* A new state structure */
    MemoryCheck(stp);
    stp->bp = bp;                /* Remember the configuration basis */
    stp->cfp = cfp;              /* Remember the configuration closure */
    stp->statenum = lemp->nstate++; /* Every state gets a sequence number */
    stp->ap = 0;                 /* No actions, yet. */
    State_insert(stp,stp->bp);   /* Add to the state table */
    buildshifts(lemp,stp);       /* Recursively compute successor states */
  }
  return stp;
}