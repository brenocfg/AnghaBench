#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nMetasize; int nBlocksize; int nPagesize; scalar_t__ pCompress; } ;
typedef  int LsmPgno ;
typedef  TYPE_1__ FileSystem ;

/* Variables and functions */

__attribute__((used)) static LsmPgno fsFirstPageOnBlock(FileSystem *pFS, int iBlock){
  LsmPgno iPg;
  if( pFS->pCompress ){
    if( iBlock==1 ){
      iPg = pFS->nMetasize * 2 + 4;
    }else{
      iPg = pFS->nBlocksize * (LsmPgno)(iBlock-1) + 4;
    }
  }else{
    const int nPagePerBlock = (pFS->nBlocksize / pFS->nPagesize);
    if( iBlock==1 ){
      iPg = 1 + ((pFS->nMetasize*2 + pFS->nPagesize - 1) / pFS->nPagesize);
    }else{
      iPg = 1 + (iBlock-1) * nPagePerBlock;
    }
  }
  return iPg;
}