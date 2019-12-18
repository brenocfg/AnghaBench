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
struct TYPE_6__ {TYPE_1__** apHash; int /*<<< orphan*/  nHash; } ;
struct TYPE_5__ {struct TYPE_5__* pHashNext; int /*<<< orphan*/  iPg; } ;
typedef  TYPE_1__ Page ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int fsHashKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsPageRemoveFromHash(FileSystem *pFS, Page *pPg){
  int iHash;
  Page **pp;

  iHash = fsHashKey(pFS->nHash, pPg->iPg);
  for(pp=&pFS->apHash[iHash]; *pp!=pPg; pp=&(*pp)->pHashNext);
  *pp = pPg->pHashNext;
  pPg->pHashNext = 0;
}