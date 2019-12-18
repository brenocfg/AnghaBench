#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_10__ {scalar_t__ rc; int nWorkUnit; TYPE_1__* pConfig; } ;
struct TYPE_9__ {int nWriteCounter; int nLevel; } ;
struct TYPE_8__ {scalar_t__ nAutomerge; } ;
typedef  TYPE_2__ Fts5Structure ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  fts5IndexMerge (TYPE_3__*,TYPE_2__**,int,scalar_t__) ; 

__attribute__((used)) static void fts5IndexAutomerge(
  Fts5Index *p,                   /* FTS5 backend object */
  Fts5Structure **ppStruct,       /* IN/OUT: Current structure of index */
  int nLeaf                       /* Number of output leaves just written */
){
  if( p->rc==SQLITE_OK && p->pConfig->nAutomerge>0 ){
    Fts5Structure *pStruct = *ppStruct;
    u64 nWrite;                   /* Initial value of write-counter */
    int nWork;                    /* Number of work-quanta to perform */
    int nRem;                     /* Number of leaf pages left to write */

    /* Update the write-counter. While doing so, set nWork. */
    nWrite = pStruct->nWriteCounter;
    nWork = (int)(((nWrite + nLeaf) / p->nWorkUnit) - (nWrite / p->nWorkUnit));
    pStruct->nWriteCounter += nLeaf;
    nRem = (int)(p->nWorkUnit * nWork * pStruct->nLevel);

    fts5IndexMerge(p, ppStruct, nRem, p->pConfig->nAutomerge);
  }
}