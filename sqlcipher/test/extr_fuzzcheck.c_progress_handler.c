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
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_2__ {scalar_t__ iCutoffTime; scalar_t__ iLastCb; scalar_t__ mxInterval; scalar_t__ nCb; scalar_t__ mxCb; int timeoutHit; } ;
typedef  TYPE_1__ FuzzCtx ;

/* Variables and functions */
 int eVerbosity ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ timeOfDay () ; 

__attribute__((used)) static int progress_handler(void *pClientData) {
  FuzzCtx *p = (FuzzCtx*)pClientData;
  sqlite3_int64 iNow = timeOfDay();
  int rc = iNow>=p->iCutoffTime;
  sqlite3_int64 iDiff = iNow - p->iLastCb;
  if( iDiff > p->mxInterval ) p->mxInterval = iDiff;
  p->nCb++;
  if( rc==0 && p->mxCb>0 && p->mxCb<=p->nCb ) rc = 1;
  if( rc && !p->timeoutHit && eVerbosity>=2 ){
    printf("Timeout on progress callback %d\n", p->nCb);
    fflush(stdout);
    p->timeoutHit = 1;
  }
  return rc;
}