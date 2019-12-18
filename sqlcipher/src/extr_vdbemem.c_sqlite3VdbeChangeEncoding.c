#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int flags; int enc; TYPE_1__* db; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int MEM_Str ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_UTF16BE ; 
 int SQLITE_UTF16LE ; 
 int SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_2__*) ; 
 int sqlite3VdbeMemTranslate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

int sqlite3VdbeChangeEncoding(Mem *pMem, int desiredEnc){
#ifndef SQLITE_OMIT_UTF16
  int rc;
#endif
  assert( !sqlite3VdbeMemIsRowSet(pMem) );
  assert( desiredEnc==SQLITE_UTF8 || desiredEnc==SQLITE_UTF16LE
           || desiredEnc==SQLITE_UTF16BE );
  if( !(pMem->flags&MEM_Str) || pMem->enc==desiredEnc ){
    return SQLITE_OK;
  }
  assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
#ifdef SQLITE_OMIT_UTF16
  return SQLITE_ERROR;
#else

  /* MemTranslate() may return SQLITE_OK or SQLITE_NOMEM. If NOMEM is returned,
  ** then the encoding of the value may not have changed.
  */
  rc = sqlite3VdbeMemTranslate(pMem, (u8)desiredEnc);
  assert(rc==SQLITE_OK    || rc==SQLITE_NOMEM);
  assert(rc==SQLITE_OK    || pMem->enc!=desiredEnc);
  assert(rc==SQLITE_NOMEM || pMem->enc==desiredEnc);
  return rc;
#endif
}