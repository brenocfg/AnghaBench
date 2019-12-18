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
struct TYPE_3__ {int nCol; int* aiCol; } ;
typedef  TYPE_1__ Fts5Colset ;

/* Variables and functions */

__attribute__((used)) static int fts5IndexColsetTest(Fts5Colset *pColset, int iCol){
  int i;
  for(i=0; i<pColset->nCol; i++){
    if( pColset->aiCol[i]==iCol ) return 1;
  }
  return 0;
}