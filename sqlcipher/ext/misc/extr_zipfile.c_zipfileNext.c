#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ pVtab; } ;
typedef  TYPE_3__ sqlite3_vtab_cursor ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  ZipfileTab ;
struct TYPE_10__ {scalar_t__ nComment; scalar_t__ nFile; scalar_t__ nExtra; } ;
struct TYPE_12__ {struct TYPE_12__* pNext; TYPE_2__ cds; } ;
typedef  TYPE_4__ ZipfileEntry ;
struct TYPE_9__ {scalar_t__ iOffset; scalar_t__ nSize; } ;
struct TYPE_13__ {scalar_t__ iNextOff; int bEof; scalar_t__ bNoop; TYPE_4__* pCurrent; scalar_t__ pFile; TYPE_1__ eocd; } ;
typedef  TYPE_5__ ZipfileCsr ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ ZIPFILE_CDS_FIXED_SZ ; 
 int /*<<< orphan*/  zipfileEntryFree (TYPE_4__*) ; 
 int zipfileGetEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,TYPE_4__**) ; 

__attribute__((used)) static int zipfileNext(sqlite3_vtab_cursor *cur){
  ZipfileCsr *pCsr = (ZipfileCsr*)cur;
  int rc = SQLITE_OK;

  if( pCsr->pFile ){
    i64 iEof = pCsr->eocd.iOffset + pCsr->eocd.nSize;
    zipfileEntryFree(pCsr->pCurrent);
    pCsr->pCurrent = 0;
    if( pCsr->iNextOff>=iEof ){
      pCsr->bEof = 1;
    }else{
      ZipfileEntry *p = 0;
      ZipfileTab *pTab = (ZipfileTab*)(cur->pVtab);
      rc = zipfileGetEntry(pTab, 0, 0, pCsr->pFile, pCsr->iNextOff, &p);
      if( rc==SQLITE_OK ){
        pCsr->iNextOff += ZIPFILE_CDS_FIXED_SZ;
        pCsr->iNextOff += (int)p->cds.nExtra + p->cds.nFile + p->cds.nComment;
      }
      pCsr->pCurrent = p;
    }
  }else{
    if( !pCsr->bNoop ){
      pCsr->pCurrent = pCsr->pCurrent->pNext;
    }
    if( pCsr->pCurrent==0 ){
      pCsr->bEof = 1;
    }
  }

  pCsr->bNoop = 0;
  return rc;
}