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
struct TYPE_6__ {scalar_t__ pFS; TYPE_3__* pDatabase; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_8__ {TYPE_2__* pLsmFile; } ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ LsmFile ;
typedef  TYPE_3__ Database ;

/* Variables and functions */
 TYPE_2__* lsmFsDeferClose (scalar_t__) ; 

__attribute__((used)) static void dbDeferClose(lsm_db *pDb){
  if( pDb->pFS ){
    LsmFile *pLsmFile;
    Database *p = pDb->pDatabase;
    pLsmFile = lsmFsDeferClose(pDb->pFS);
    pLsmFile->pNext = p->pLsmFile;
    p->pLsmFile = pLsmFile;
  }
}