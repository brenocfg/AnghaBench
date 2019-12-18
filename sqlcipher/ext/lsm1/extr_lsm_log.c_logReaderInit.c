#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pEnv; int /*<<< orphan*/  pFS; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_13__ {scalar_t__ n; } ;
struct TYPE_12__ {int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; TYPE_1__* aRegion; } ;
struct TYPE_11__ {scalar_t__ iBuf; scalar_t__ iCksumBuf; TYPE_5__ buf; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; int /*<<< orphan*/  iOff; int /*<<< orphan*/  pFS; } ;
struct TYPE_9__ {int /*<<< orphan*/  iStart; } ;
typedef  TYPE_3__ LogReader ;
typedef  TYPE_4__ DbLog ;

/* Variables and functions */
 int /*<<< orphan*/  lsmStringInit (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void logReaderInit(
  lsm_db *pDb,                    /* Database handle */
  DbLog *pLog,                    /* Log object associated with pDb */
  int bInitBuf,                   /* True if p->buf is uninitialized */
  LogReader *p                    /* Initialize this LogReader object */
){
  p->pFS = pDb->pFS;
  p->iOff = pLog->aRegion[2].iStart;
  p->cksum0 = pLog->cksum0;
  p->cksum1 = pLog->cksum1;
  if( bInitBuf ){ lsmStringInit(&p->buf, pDb->pEnv); }
  p->buf.n = 0;
  p->iCksumBuf = 0;
  p->iBuf = 0;
}