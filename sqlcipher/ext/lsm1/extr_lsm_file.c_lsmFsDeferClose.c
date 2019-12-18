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
struct TYPE_6__ {TYPE_1__* pLsmFile; scalar_t__ fdDb; } ;
struct TYPE_5__ {scalar_t__ pNext; scalar_t__ pFile; } ;
typedef  TYPE_1__ LsmFile ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

LsmFile *lsmFsDeferClose(FileSystem *pFS){
  LsmFile *p = pFS->pLsmFile;
  assert( p->pNext==0 );
  p->pFile = pFS->fdDb;
  pFS->fdDb = 0;
  pFS->pLsmFile = 0;
  return p;
}