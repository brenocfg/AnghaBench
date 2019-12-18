#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ pVtab; } ;
typedef  TYPE_2__ sqlite3_vtab_cursor ;
struct TYPE_11__ {scalar_t__ nByte; TYPE_6__* pFd; } ;
typedef  TYPE_3__ VfslogVtab ;
struct TYPE_12__ {char* zTransient; scalar_t__ iOffset; unsigned char* aBuf; int nFile; char** azFile; int iRowid; } ;
typedef  TYPE_4__ VfslogCsr ;
struct TYPE_13__ {TYPE_1__* pMethods; } ;
struct TYPE_9__ {int (* xRead ) (TYPE_6__*,unsigned char*,int,scalar_t__) ;} ;

/* Variables and functions */
 int OS_ACCESS ; 
 int OS_DELETE ; 
 int OS_OPEN ; 
 int SQLITE_OK ; 
 int get32bits (unsigned char*) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc (int) ; 
 scalar_t__ sqlite3_realloc (char**,int) ; 
 int stub1 (TYPE_6__*,unsigned char*,int,scalar_t__) ; 
 int stub2 (TYPE_6__*,char*,int,scalar_t__) ; 
 int stub3 (TYPE_6__*,char*,int,scalar_t__) ; 

__attribute__((used)) static int vlogNext(sqlite3_vtab_cursor *pCursor){
  VfslogCsr *pCsr = (VfslogCsr *)pCursor;
  VfslogVtab *p = (VfslogVtab *)pCursor->pVtab;
  int rc = SQLITE_OK;
  int nRead;

  sqlite3_free(pCsr->zTransient);
  pCsr->zTransient = 0;

  nRead = 24;
  if( pCsr->iOffset+nRead<=p->nByte ){
    int eEvent;
    rc = p->pFd->pMethods->xRead(p->pFd, pCsr->aBuf, nRead, pCsr->iOffset);

    eEvent = get32bits(pCsr->aBuf);
    if( (rc==SQLITE_OK)
     && (eEvent==OS_OPEN || eEvent==OS_DELETE || eEvent==OS_ACCESS) 
    ){
      char buf[4];
      rc = p->pFd->pMethods->xRead(p->pFd, buf, 4, pCsr->iOffset+nRead);
      nRead += 4;
      if( rc==SQLITE_OK ){
        int nStr = get32bits((unsigned char *)buf);
        char *zStr = sqlite3_malloc(nStr+1);
        rc = p->pFd->pMethods->xRead(p->pFd, zStr, nStr, pCsr->iOffset+nRead);
        zStr[nStr] = '\0';
        nRead += nStr;

        if( eEvent==OS_OPEN ){
          int iFileid = get32bits(&pCsr->aBuf[4]);
          if( iFileid>=pCsr->nFile ){
            int nNew = sizeof(pCsr->azFile[0])*(iFileid+1);
            pCsr->azFile = (char **)sqlite3_realloc(pCsr->azFile, nNew);
            nNew -= sizeof(pCsr->azFile[0])*pCsr->nFile;
            memset(&pCsr->azFile[pCsr->nFile], 0, nNew);
            pCsr->nFile = iFileid+1;
          }
          sqlite3_free(pCsr->azFile[iFileid]);
          pCsr->azFile[iFileid] = zStr;
        }else{
          pCsr->zTransient = zStr;
        }
      }
    }
  }

  pCsr->iRowid += 1;
  pCsr->iOffset += nRead;
  return rc;
}