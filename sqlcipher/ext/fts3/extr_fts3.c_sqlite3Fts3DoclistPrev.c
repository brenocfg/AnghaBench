#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3GetReverseVarint (char**,char*,scalar_t__*) ; 
 int /*<<< orphan*/  fts3PoslistCopy (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  fts3ReversePoslist (char*,char**) ; 
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char*,scalar_t__*) ; 

void sqlite3Fts3DoclistPrev(
  int bDescIdx,                   /* True if the doclist is desc */
  char *aDoclist,                 /* Pointer to entire doclist */
  int nDoclist,                   /* Length of aDoclist in bytes */
  char **ppIter,                  /* IN/OUT: Iterator pointer */
  sqlite3_int64 *piDocid,         /* IN/OUT: Docid pointer */
  int *pnList,                    /* OUT: List length pointer */
  u8 *pbEof                       /* OUT: End-of-file flag */
){
  char *p = *ppIter;

  assert( nDoclist>0 );
  assert( *pbEof==0 );
  assert( p || *piDocid==0 );
  assert( !p || (p>aDoclist && p<&aDoclist[nDoclist]) );

  if( p==0 ){
    sqlite3_int64 iDocid = 0;
    char *pNext = 0;
    char *pDocid = aDoclist;
    char *pEnd = &aDoclist[nDoclist];
    int iMul = 1;

    while( pDocid<pEnd ){
      sqlite3_int64 iDelta;
      pDocid += sqlite3Fts3GetVarint(pDocid, &iDelta);
      iDocid += (iMul * iDelta);
      pNext = pDocid;
      fts3PoslistCopy(0, &pDocid);
      while( pDocid<pEnd && *pDocid==0 ) pDocid++;
      iMul = (bDescIdx ? -1 : 1);
    }

    *pnList = (int)(pEnd - pNext);
    *ppIter = pNext;
    *piDocid = iDocid;
  }else{
    int iMul = (bDescIdx ? -1 : 1);
    sqlite3_int64 iDelta;
    fts3GetReverseVarint(&p, aDoclist, &iDelta);
    *piDocid -= (iMul * iDelta);

    if( p==aDoclist ){
      *pbEof = 1;
    }else{
      char *pSave = p;
      fts3ReversePoslist(aDoclist, &p);
      *pnList = (int)(pSave - p);
    }
    *ppIter = p;
  }
}