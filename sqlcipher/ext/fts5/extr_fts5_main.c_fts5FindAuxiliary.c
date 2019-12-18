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
struct TYPE_8__ {int /*<<< orphan*/  zFunc; struct TYPE_8__* pNext; } ;
struct TYPE_7__ {TYPE_1__* pGlobal; } ;
struct TYPE_6__ {TYPE_3__* pAux; } ;
typedef  TYPE_2__ Fts5FullTable ;
typedef  TYPE_3__ Fts5Auxiliary ;

/* Variables and functions */
 scalar_t__ sqlite3_stricmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Fts5Auxiliary *fts5FindAuxiliary(Fts5FullTable *pTab, const char *zName){
  Fts5Auxiliary *pAux;

  for(pAux=pTab->pGlobal->pAux; pAux; pAux=pAux->pNext){
    if( sqlite3_stricmp(zName, pAux->zFunc)==0 ) return pAux;
  }

  /* No function of the specified name was found. Return 0. */
  return 0;
}