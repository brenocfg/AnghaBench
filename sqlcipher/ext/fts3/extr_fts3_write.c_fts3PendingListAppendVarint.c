#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_7__ {int nSpace; char* aData; int nData; } ;
typedef  TYPE_1__ PendingList ;

/* Variables and functions */
 int FTS3_VARINT_MAX ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ sqlite3Fts3PutVarint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 TYPE_1__* sqlite3_malloc (int) ; 
 TYPE_1__* sqlite3_realloc (TYPE_1__*,int) ; 

__attribute__((used)) static int fts3PendingListAppendVarint(
  PendingList **pp,               /* IN/OUT: Pointer to PendingList struct */
  sqlite3_int64 i                 /* Value to append to data */
){
  PendingList *p = *pp;

  /* Allocate or grow the PendingList as required. */
  if( !p ){
    p = sqlite3_malloc(sizeof(*p) + 100);
    if( !p ){
      return SQLITE_NOMEM;
    }
    p->nSpace = 100;
    p->aData = (char *)&p[1];
    p->nData = 0;
  }
  else if( p->nData+FTS3_VARINT_MAX+1>p->nSpace ){
    int nNew = p->nSpace * 2;
    p = sqlite3_realloc(p, sizeof(*p) + nNew);
    if( !p ){
      sqlite3_free(*pp);
      *pp = 0;
      return SQLITE_NOMEM;
    }
    p->nSpace = nNew;
    p->aData = (char *)&p[1];
  }

  /* Append the new serialized varint to the end of the list. */
  p->nData += sqlite3Fts3PutVarint(&p->aData[p->nData], i);
  p->aData[p->nData] = '\0';
  *pp = p;
  return SQLITE_OK;
}