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
struct TYPE_4__ {int nIndex; } ;
typedef  TYPE_1__ Fts3Table ;
typedef  int /*<<< orphan*/  Fts3MultiSegReader ;

/* Variables and functions */
 int FTS3_SEGCURSOR_ALL ; 
 int FTS3_SEGCURSOR_PENDING ; 
 int FTS3_SEGDIR_MAXLEVEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3SegReaderCursor (TYPE_1__*,int,int,int,char const*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int sqlite3Fts3SegReaderCursor(
  Fts3Table *p,                   /* FTS3 table handle */
  int iLangid,                    /* Language-id to search */
  int iIndex,                     /* Index to search (from 0 to p->nIndex-1) */
  int iLevel,                     /* Level of segments to scan */
  const char *zTerm,              /* Term to query for */
  int nTerm,                      /* Size of zTerm in bytes */
  int isPrefix,                   /* True for a prefix search */
  int isScan,                     /* True to scan from zTerm to EOF */
  Fts3MultiSegReader *pCsr       /* Cursor object to populate */
){
  assert( iIndex>=0 && iIndex<p->nIndex );
  assert( iLevel==FTS3_SEGCURSOR_ALL
      ||  iLevel==FTS3_SEGCURSOR_PENDING 
      ||  iLevel>=0
  );
  assert( iLevel<FTS3_SEGDIR_MAXLEVEL );
  assert( FTS3_SEGCURSOR_ALL<0 && FTS3_SEGCURSOR_PENDING<0 );
  assert( isPrefix==0 || isScan==0 );

  memset(pCsr, 0, sizeof(Fts3MultiSegReader));
  return fts3SegReaderCursor(
      p, iLangid, iIndex, iLevel, zTerm, nTerm, isPrefix, isScan, pCsr
  );
}