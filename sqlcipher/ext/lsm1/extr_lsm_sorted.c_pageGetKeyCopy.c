#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_5__ {void* pData; int nData; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__ LsmBlob ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * pageGetKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int*,TYPE_1__*) ; 
 int sortedBlobSet (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pageGetKeyCopy(
  lsm_env *pEnv,                  /* Environment handle */
  Segment *pSeg,                  /* Segment pPg belongs to */
  Page *pPg,                      /* Page to read from */
  int iCell,                      /* Index of cell on page to read */
  int *piTopic,                   /* OUT: Topic associated with this key */
  LsmBlob *pBlob                  /* If required, use this for dynamic memory */
){
  int rc = LSM_OK;
  int nKey;
  u8 *aKey;

  aKey = pageGetKey(pSeg, pPg, iCell, piTopic, &nKey, pBlob);
  assert( (void *)aKey!=pBlob->pData || nKey==pBlob->nData );
  if( (void *)aKey!=pBlob->pData ){
    rc = sortedBlobSet(pEnv, pBlob, aKey, nKey);
  }

  return rc;
}