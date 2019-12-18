#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int n; int /*<<< orphan*/ * z; } ;
struct TYPE_5__ {int iCksumBuf; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; TYPE_1__ buf; } ;
typedef  TYPE_2__ LogWriter ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  logCksumUnaligned (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void logUpdateCksum(LogWriter *pLog, int nBuf){
  assert( (pLog->iCksumBuf % 8)==0 );
  assert( pLog->iCksumBuf<=nBuf );
  assert( (nBuf % 8)==0 || nBuf==pLog->buf.n );
  if( nBuf>pLog->iCksumBuf ){
    logCksumUnaligned(
        &pLog->buf.z[pLog->iCksumBuf], nBuf-pLog->iCksumBuf, 
        &pLog->cksum0, &pLog->cksum1
    );
  }
  pLog->iCksumBuf = nBuf;
}