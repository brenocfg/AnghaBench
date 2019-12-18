#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_9__ {scalar_t__ xCmp; char* zName; } ;
struct TYPE_8__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  ENC (int /*<<< orphan*/ *) ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* sqlite3GetCollSeq (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,char const*) ; 

int sqlite3CheckCollSeq(Parse *pParse, CollSeq *pColl){
  if( pColl && pColl->xCmp==0 ){
    const char *zName = pColl->zName;
    sqlite3 *db = pParse->db;
    CollSeq *p = sqlite3GetCollSeq(pParse, ENC(db), pColl, zName);
    if( !p ){
      return SQLITE_ERROR;
    }
    assert( p==pColl );
  }
  return SQLITE_OK;
}