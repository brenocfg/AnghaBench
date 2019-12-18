#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_3__ {int nSegment; int /*<<< orphan*/ ** apSegment; } ;
typedef  int /*<<< orphan*/  Fts3SegReader ;
typedef  TYPE_1__ Fts3MultiSegReader ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3Fts3SegReaderFree (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_realloc64 (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int fts3SegReaderCursorAppend(
  Fts3MultiSegReader *pCsr, 
  Fts3SegReader *pNew
){
  if( (pCsr->nSegment%16)==0 ){
    Fts3SegReader **apNew;
    sqlite3_int64 nByte = (pCsr->nSegment + 16)*sizeof(Fts3SegReader*);
    apNew = (Fts3SegReader **)sqlite3_realloc64(pCsr->apSegment, nByte);
    if( !apNew ){
      sqlite3Fts3SegReaderFree(pNew);
      return SQLITE_NOMEM;
    }
    pCsr->apSegment = apNew;
  }
  pCsr->apSegment[pCsr->nSegment++] = pNew;
  return SQLITE_OK;
}