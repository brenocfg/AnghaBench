#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int eStage; int /*<<< orphan*/  nFrame; int /*<<< orphan*/  nStep; int /*<<< orphan*/  nPhaseOneStep; int /*<<< orphan*/  nProgress; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int const i64 ;

/* Variables and functions */
#define  RBU_STAGE_CKPT 131 
#define  RBU_STAGE_DONE 130 
#define  RBU_STAGE_MOVE 129 
#define  RBU_STAGE_OAL 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void sqlite3rbu_bp_progress(sqlite3rbu *p, int *pnOne, int *pnTwo){
  const int MAX_PROGRESS = 10000;
  switch( p->eStage ){
    case RBU_STAGE_OAL:
      if( p->nPhaseOneStep>0 ){
        *pnOne = (int)(MAX_PROGRESS * (i64)p->nProgress/(i64)p->nPhaseOneStep);
      }else{
        *pnOne = -1;
      }
      *pnTwo = 0;
      break;

    case RBU_STAGE_MOVE:
      *pnOne = MAX_PROGRESS;
      *pnTwo = 0;
      break;

    case RBU_STAGE_CKPT:
      *pnOne = MAX_PROGRESS;
      *pnTwo = (int)(MAX_PROGRESS * (i64)p->nStep / (i64)p->nFrame);
      break;

    case RBU_STAGE_DONE:
      *pnOne = MAX_PROGRESS;
      *pnTwo = MAX_PROGRESS;
      break;

    default:
      assert( 0 );
  }
}