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
 int /*<<< orphan*/ * lsmFsPageData (int /*<<< orphan*/ *,int*) ; 
 int pageGetNRec (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pageObjGetNRec(Page *pPg){
  int nData;
  u8 *aData = lsmFsPageData(pPg, &nData);
  return pageGetNRec(aData, nData);
}