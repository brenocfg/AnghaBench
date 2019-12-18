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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  Page ;

/* Variables and functions */
 int SEGMENT_EOF (int,int) ; 
 int /*<<< orphan*/ * lsmFsPageData (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pageGetNRec (int /*<<< orphan*/ *,int) ; 

void lsmSortedExpandBtreePage(Page *pPg, int nOrig){
  u8 *aData;
  int nData;
  int nEntry;
  int iHdr;

  aData = lsmFsPageData(pPg, &nData);
  nEntry = pageGetNRec(aData, nOrig);
  iHdr = SEGMENT_EOF(nOrig, nEntry);
  memmove(&aData[iHdr + (nData-nOrig)], &aData[iHdr], nOrig-iHdr);
}