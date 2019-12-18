#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nSrc; char* zSourceStr; int /*<<< orphan*/  nOpen; TYPE_2__* pClosable; scalar_t__ nMaxOpen; scalar_t__ bSwarm; TYPE_2__* aSrc; } ;
typedef  TYPE_1__ UnionTab ;
struct TYPE_12__ {scalar_t__ db; struct TYPE_12__* pNextClosable; } ;
typedef  TYPE_2__ UnionSrc ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_close (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*) ; 
 scalar_t__ sqlite3_stricmp (char*,char*) ; 
 int /*<<< orphan*/  unionCloseSources (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  unionInvokeOpenClose (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int unionOpenDatabaseInner (TYPE_1__*,TYPE_2__*,char**) ; 
 char* unionSourceToStr (int*,TYPE_1__*,TYPE_2__*,char**) ; 

__attribute__((used)) static int unionOpenDatabase(UnionTab *pTab, int iSrc, char **pzErr){
  int rc = SQLITE_OK;
  UnionSrc *pSrc = &pTab->aSrc[iSrc];

  assert( pTab->bSwarm && iSrc<pTab->nSrc );
  if( pSrc->db==0 ){
    unionCloseSources(pTab, pTab->nMaxOpen-1);
    rc = unionOpenDatabaseInner(pTab, pSrc, pzErr);
    if( rc==SQLITE_OK ){
      char *z = unionSourceToStr(&rc, pTab, pSrc, pzErr);
      if( rc==SQLITE_OK ){
        if( pTab->zSourceStr==0 ){
          pTab->zSourceStr = z;
        }else{
          if( sqlite3_stricmp(z, pTab->zSourceStr) ){
            *pzErr = sqlite3_mprintf("source table schema mismatch");
            rc = SQLITE_ERROR;
          }
          sqlite3_free(z);
        }
      }
    }

    if( rc==SQLITE_OK ){
      pSrc->pNextClosable = pTab->pClosable;
      pTab->pClosable = pSrc;
      pTab->nOpen++;
    }else{
      sqlite3_close(pSrc->db);
      pSrc->db = 0;
      unionInvokeOpenClose(pTab, pSrc, 1, 0);
    }
  }

  return rc;
}