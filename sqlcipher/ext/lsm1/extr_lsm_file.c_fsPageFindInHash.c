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
struct TYPE_5__ {scalar_t__ iPg; struct TYPE_5__* pHashNext; } ;
typedef  TYPE_1__ Page ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int fsHashKey (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static Page *fsPageFindInHash(FileSystem *pFS, LsmPgno iPg, int *piHash){
  Page *p;                        /* Return value */
  int iHash = fsHashKey(pFS->nHash, iPg);

  if( piHash ) *piHash = iHash;
  for(p=pFS->apHash[iHash]; p; p=p->pHashNext){
    if( p->iPg==iPg) break;
  }
  return p;
}