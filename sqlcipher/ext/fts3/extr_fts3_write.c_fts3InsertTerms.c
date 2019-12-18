#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_4__ {int nColumn; scalar_t__* abNotindexed; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 int fts3PendingTermsAdd (TYPE_1__*,int,char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3InsertTerms(
  Fts3Table *p, 
  int iLangid, 
  sqlite3_value **apVal, 
  u32 *aSz
){
  int i;                          /* Iterator variable */
  for(i=2; i<p->nColumn+2; i++){
    int iCol = i-2;
    if( p->abNotindexed[iCol]==0 ){
      const char *zText = (const char *)sqlite3_value_text(apVal[i]);
      int rc = fts3PendingTermsAdd(p, iLangid, zText, iCol, &aSz[iCol]);
      if( rc!=SQLITE_OK ){
        return rc;
      }
      aSz[p->nColumn] += sqlite3_value_bytes(apVal[i]);
    }
  }
  return SQLITE_OK;
}