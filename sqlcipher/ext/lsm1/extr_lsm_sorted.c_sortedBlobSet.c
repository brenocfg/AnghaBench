#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_4__ {int nData; int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ LsmBlob ;

/* Variables and functions */
 int LSM_NOMEM ; 
 int LSM_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ sortedBlobGrow (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static int sortedBlobSet(lsm_env *pEnv, LsmBlob *pBlob, void *pData, int nData){
  if( sortedBlobGrow(pEnv, pBlob, nData) ) return LSM_NOMEM;
  memcpy(pBlob->pData, pData, nData);
  pBlob->nData = nData;
  return LSM_OK;
}