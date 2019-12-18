#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  iSize; } ;
typedef  TYPE_2__ quotaGroup ;
struct TYPE_8__ {TYPE_1__** ppPrev; TYPE_1__* pNext; scalar_t__ iSize; TYPE_2__* pGroup; } ;
typedef  TYPE_3__ quotaFile ;
struct TYPE_6__ {struct TYPE_6__** ppPrev; } ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 

__attribute__((used)) static void quotaRemoveFile(quotaFile *pFile){
  quotaGroup *pGroup = pFile->pGroup;
  pGroup->iSize -= pFile->iSize;
  *pFile->ppPrev = pFile->pNext;
  if( pFile->pNext ) pFile->pNext->ppPrev = pFile->ppPrev;
  sqlite3_free(pFile);
}