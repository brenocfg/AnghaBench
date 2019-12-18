#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  db; scalar_t__ pOpenClose; scalar_t__ bHasContext; } ;
typedef  TYPE_1__ UnionTab ;
struct TYPE_6__ {int /*<<< orphan*/  zContext; int /*<<< orphan*/  zFile; } ;
typedef  TYPE_2__ UnionSrc ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  sqlite3_bind_int (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  sqlite3_bind_text (scalar_t__,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_step (scalar_t__) ; 

__attribute__((used)) static int unionInvokeOpenClose(
  UnionTab *pTab, 
  UnionSrc *pSrc, 
  int bClose,
  char **pzErr
){
  int rc = SQLITE_OK;
  if( pTab->pOpenClose ){
    sqlite3_bind_text(pTab->pOpenClose, 1, pSrc->zFile, -1, SQLITE_STATIC);
    if( pTab->bHasContext ){
      sqlite3_bind_text(pTab->pOpenClose, 2, pSrc->zContext, -1, SQLITE_STATIC);
    }
    sqlite3_bind_int(pTab->pOpenClose, 2+pTab->bHasContext, bClose);
    sqlite3_step(pTab->pOpenClose);
    if( SQLITE_OK!=(rc = sqlite3_reset(pTab->pOpenClose)) ){
      if( pzErr ){
        *pzErr = sqlite3_mprintf("%s", sqlite3_errmsg(pTab->db));
      }
    }
  }
  return rc;
}