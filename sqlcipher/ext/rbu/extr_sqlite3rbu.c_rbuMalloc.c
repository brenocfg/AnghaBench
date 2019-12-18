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
struct TYPE_3__ {scalar_t__ rc; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;

/* Variables and functions */
 scalar_t__ SQLITE_NOMEM ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sqlite3_malloc64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *rbuMalloc(sqlite3rbu *p, sqlite3_int64 nByte){
  void *pRet = 0;
  if( p->rc==SQLITE_OK ){
    assert( nByte>0 );
    pRet = sqlite3_malloc64(nByte);
    if( pRet==0 ){
      p->rc = SQLITE_NOMEM;
    }else{
      memset(pRet, 0, nByte);
    }
  }
  return pRet;
}