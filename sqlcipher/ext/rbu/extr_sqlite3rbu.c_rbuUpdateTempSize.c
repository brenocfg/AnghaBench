#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ szTemp; scalar_t__ szTempLimit; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  void* sqlite3_int64 ;
struct TYPE_5__ {void* sz; TYPE_1__* pRbu; } ;
typedef  TYPE_2__ rbu_file ;
typedef  scalar_t__ i64 ;

/* Variables and functions */
 int SQLITE_FULL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int rbuUpdateTempSize(rbu_file *pFd, sqlite3_int64 nNew){
  sqlite3rbu *pRbu = pFd->pRbu;
  i64 nDiff = nNew - pFd->sz;
  pRbu->szTemp += nDiff;
  pFd->sz = nNew;
  assert( pRbu->szTemp>=0 );
  if( pRbu->szTempLimit && pRbu->szTemp>pRbu->szTempLimit ) return SQLITE_FULL;
  return SQLITE_OK;
}