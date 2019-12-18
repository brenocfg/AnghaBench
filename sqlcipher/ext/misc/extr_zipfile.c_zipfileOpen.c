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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {TYPE_2__* pCsrList; scalar_t__ iNextCsrid; } ;
typedef  TYPE_1__ ZipfileTab ;
struct TYPE_6__ {struct TYPE_6__* pCsrNext; scalar_t__ iId; } ;
typedef  TYPE_2__ ZipfileCsr ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* sqlite3_malloc (int) ; 

__attribute__((used)) static int zipfileOpen(sqlite3_vtab *p, sqlite3_vtab_cursor **ppCsr){
  ZipfileTab *pTab = (ZipfileTab*)p;
  ZipfileCsr *pCsr;
  pCsr = sqlite3_malloc(sizeof(*pCsr));
  *ppCsr = (sqlite3_vtab_cursor*)pCsr;
  if( pCsr==0 ){
    return SQLITE_NOMEM;
  }
  memset(pCsr, 0, sizeof(*pCsr));
  pCsr->iId = ++pTab->iNextCsrid;
  pCsr->pCsrNext = pTab->pCsrList;
  pTab->pCsrList = pCsr;
  return SQLITE_OK;
}