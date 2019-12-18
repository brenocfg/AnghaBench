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
typedef  int i64 ;
typedef  int /*<<< orphan*/  MetaPage ;

/* Variables and functions */
 int CKPT_HDR_ID_LSW ; 
 int CKPT_HDR_ID_MSW ; 
 int /*<<< orphan*/ * lsmFsMetaPageData (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ lsmGetU32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static i64 ckptLoadId(MetaPage *pPg){
  i64 ret = 0;
  if( pPg ){
    int nData;
    u8 *aData = lsmFsMetaPageData(pPg, &nData);
    ret = (((i64)lsmGetU32(&aData[CKPT_HDR_ID_MSW*4])) << 32) + 
          ((i64)lsmGetU32(&aData[CKPT_HDR_ID_LSW*4]));
  }
  return ret;
}