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
struct lemon {int minReduce; int minShiftReduce; int errAction; int accAction; int /*<<< orphan*/  nterminal; } ;
struct TYPE_8__ {TYPE_3__* rp; TYPE_1__* stp; } ;
struct action {int type; TYPE_4__ x; TYPE_2__* sp; } ;
struct TYPE_7__ {int iRule; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {int statenum; } ;

/* Variables and functions */
#define  ACCEPT 132 
#define  ERROR 131 
#define  REDUCE 130 
#define  SHIFT 129 
#define  SHIFTREDUCE 128 

int compute_action(struct lemon *lemp, struct action *ap)
{
  int act;
  switch( ap->type ){
    case SHIFT:  act = ap->x.stp->statenum;                        break;
    case SHIFTREDUCE: {
      /* Since a SHIFT is inherient after a prior REDUCE, convert any
      ** SHIFTREDUCE action with a nonterminal on the LHS into a simple
      ** REDUCE action: */
      if( ap->sp->index>=lemp->nterminal ){
        act = lemp->minReduce + ap->x.rp->iRule;
      }else{
        act = lemp->minShiftReduce + ap->x.rp->iRule;
      }
      break;
    }
    case REDUCE: act = lemp->minReduce + ap->x.rp->iRule;          break;
    case ERROR:  act = lemp->errAction;                            break;
    case ACCEPT: act = lemp->accAction;                            break;
    default:     act = -1; break;
  }
  return act;
}