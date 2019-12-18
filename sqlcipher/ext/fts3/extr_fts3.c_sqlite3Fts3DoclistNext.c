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
 int /*<<< orphan*/  fts3PoslistCopy (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char*,scalar_t__*) ; 

void sqlite3Fts3DoclistNext(
  int bDescIdx,                   /* True if the doclist is desc */
  char *aDoclist,                 /* Pointer to entire doclist */
  int nDoclist,                   /* Length of aDoclist in bytes */
  char **ppIter,                  /* IN/OUT: Iterator pointer */
  sqlite3_int64 *piDocid,         /* IN/OUT: Docid pointer */
  u8 *pbEof                       /* OUT: End-of-file flag */
){
  char *p = *ppIter;

  assert( nDoclist>0 );
  assert( *pbEof==0 );
  assert( p || *piDocid==0 );
  assert( !p || (p>=aDoclist && p<=&aDoclist[nDoclist]) );

  if( p==0 ){
    p = aDoclist;
    p += sqlite3Fts3GetVarint(p, piDocid);
  }else{
    fts3PoslistCopy(0, &p);
    while( p<&aDoclist[nDoclist] && *p==0 ) p++; 
    if( p>=&aDoclist[nDoclist] ){
      *pbEof = 1;
    }else{
      sqlite3_int64 iVar;
      p += sqlite3Fts3GetVarint(p, &iVar);
      *piDocid += ((bDescIdx ? -1 : 1) * iVar);
    }
  }

  *ppIter = p;
}