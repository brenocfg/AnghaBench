#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {size_t n; int /*<<< orphan*/ * z; } ;
struct TYPE_6__ {size_t iBuf; TYPE_1__ buf; } ;
typedef  int /*<<< orphan*/  LsmString ;
typedef  TYPE_2__ LogReader ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  logReaderBlob (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int lsmVarintGet32 (int /*<<< orphan*/ *,int*) ; 
 int lsmVarintSize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void logReaderVarint(
  LogReader *p, 
  LsmString *pBuf,
  int *piVal,                     /* OUT: Value read from log */
  int *pRc                        /* IN/OUT: Error code */
){
  if( *pRc==LSM_OK ){
    u8 *aVarint;
    if( p->buf.n==p->iBuf ){
      logReaderBlob(p, 0, 10, &aVarint, pRc);
      if( LSM_OK==*pRc ) p->iBuf -= (10 - lsmVarintGet32(aVarint, piVal));
    }else{
      logReaderBlob(p, pBuf, lsmVarintSize(p->buf.z[p->iBuf]), &aVarint, pRc);
      if( LSM_OK==*pRc ) lsmVarintGet32(aVarint, piVal);
    }
  }
}