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
struct TYPE_6__ {TYPE_1__* pTok; TYPE_1__* pDfltTok; } ;
struct TYPE_5__ {int /*<<< orphan*/  zName; struct TYPE_5__* pNext; } ;
typedef  TYPE_1__ Fts5TokenizerModule ;
typedef  TYPE_2__ Fts5Global ;

/* Variables and functions */
 scalar_t__ sqlite3_stricmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Fts5TokenizerModule *fts5LocateTokenizer(
  Fts5Global *pGlobal, 
  const char *zName
){
  Fts5TokenizerModule *pMod = 0;

  if( zName==0 ){
    pMod = pGlobal->pDfltTok;
  }else{
    for(pMod=pGlobal->pTok; pMod; pMod=pMod->pNext){
      if( sqlite3_stricmp(zName, pMod->zName)==0 ) break;
    }
  }

  return pMod;
}