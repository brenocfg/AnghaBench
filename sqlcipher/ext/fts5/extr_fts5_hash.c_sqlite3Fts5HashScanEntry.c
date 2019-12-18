#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {TYPE_1__* pScan; } ;
struct TYPE_7__ {int nData; } ;
typedef  TYPE_1__ Fts5HashEntry ;
typedef  TYPE_2__ Fts5Hash ;

/* Variables and functions */
 char* fts5EntryKey (TYPE_1__*) ; 
 int /*<<< orphan*/  fts5HashAddPoslistSize (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

void sqlite3Fts5HashScanEntry(
  Fts5Hash *pHash,
  const char **pzTerm,            /* OUT: term (nul-terminated) */
  const u8 **ppDoclist,           /* OUT: pointer to doclist */
  int *pnDoclist                  /* OUT: size of doclist in bytes */
){
  Fts5HashEntry *p;
  if( (p = pHash->pScan) ){
    char *zKey = fts5EntryKey(p);
    int nTerm = (int)strlen(zKey);
    fts5HashAddPoslistSize(pHash, p, 0);
    *pzTerm = zKey;
    *ppDoclist = (const u8*)&zKey[nTerm+1];
    *pnDoclist = p->nData - (sizeof(Fts5HashEntry) + nTerm + 1);
  }else{
    *pzTerm = 0;
    *ppDoclist = 0;
    *pnDoclist = 0;
  }
}