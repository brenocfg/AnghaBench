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
struct TYPE_3__ {int n; int nAlloc; char* z; } ;
typedef  TYPE_1__ StrBuffer ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* sqlite3_realloc64 (char*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int fts3StringAppend(
  StrBuffer *pStr,                /* Buffer to append to */
  const char *zAppend,            /* Pointer to data to append to buffer */
  int nAppend                     /* Size of zAppend in bytes (or -1) */
){
  if( nAppend<0 ){
    nAppend = (int)strlen(zAppend);
  }

  /* If there is insufficient space allocated at StrBuffer.z, use realloc()
  ** to grow the buffer until so that it is big enough to accomadate the
  ** appended data.
  */
  if( pStr->n+nAppend+1>=pStr->nAlloc ){
    sqlite3_int64 nAlloc = pStr->nAlloc+(sqlite3_int64)nAppend+100;
    char *zNew = sqlite3_realloc64(pStr->z, nAlloc);
    if( !zNew ){
      return SQLITE_NOMEM;
    }
    pStr->z = zNew;
    pStr->nAlloc = nAlloc;
  }
  assert( pStr->z!=0 && (pStr->nAlloc >= pStr->n+nAppend+1) );

  /* Append the data to the string buffer. */
  memcpy(&pStr->z[pStr->n], zAppend, nAppend);
  pStr->n += nAppend;
  pStr->z[pStr->n] = '\0';

  return SQLITE_OK;
}