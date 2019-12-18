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
struct TYPE_3__ {char* zTerm; scalar_t__ bPrefix; struct TYPE_3__* pSynonym; } ;
typedef  TYPE_1__ Fts5ExprTerm ;

/* Variables and functions */
 char* sqlite3_malloc64 (int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *fts5ExprTermPrint(Fts5ExprTerm *pTerm){
  sqlite3_int64 nByte = 0;
  Fts5ExprTerm *p;
  char *zQuoted;

  /* Determine the maximum amount of space required. */
  for(p=pTerm; p; p=p->pSynonym){
    nByte += (int)strlen(pTerm->zTerm) * 2 + 3 + 2;
  }
  zQuoted = sqlite3_malloc64(nByte);

  if( zQuoted ){
    int i = 0;
    for(p=pTerm; p; p=p->pSynonym){
      char *zIn = p->zTerm;
      zQuoted[i++] = '"';
      while( *zIn ){
        if( *zIn=='"' ) zQuoted[i++] = '"';
        zQuoted[i++] = *zIn++;
      }
      zQuoted[i++] = '"';
      if( p->pSynonym ) zQuoted[i++] = '|';
    }
    if( pTerm->bPrefix ){
      zQuoted[i++] = ' ';
      zQuoted[i++] = '*';
    }
    zQuoted[i++] = '\0';
  }
  return zQuoted;
}