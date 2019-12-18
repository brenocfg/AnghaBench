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
struct TYPE_3__ {int nBlocksize; int nPagesize; scalar_t__ pCompress; } ;
typedef  int LsmPgno ;
typedef  TYPE_1__ FileSystem ;

/* Variables and functions */

__attribute__((used)) static LsmPgno fsLastPageOnBlock(FileSystem *pFS, int iBlock){
  if( pFS->pCompress ){
    return pFS->nBlocksize * (LsmPgno)iBlock - 1 - 4;
  }else{
    const int nPagePerBlock = (pFS->nBlocksize / pFS->nPagesize);
    return iBlock * nPagePerBlock;
  }
}