#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nPrefix; int otherError; scalar_t__ mallocFailed; int /*<<< orphan*/  pStmt; scalar_t__ zPrefix; } ;
typedef  TYPE_1__ nextCharContext ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  nextCharAppend (TYPE_1__*,unsigned int) ; 
 int readUtf8 (unsigned char const*,unsigned int*) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ) ; 
 unsigned char* sqlite3_column_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 
 int writeUtf8 (unsigned char*,unsigned int) ; 

__attribute__((used)) static void findNextChars(nextCharContext *p){
  unsigned cPrev = 0;
  unsigned char zPrev[8];
  int n, rc;
  
  for(;;){
    sqlite3_bind_text(p->pStmt, 1, (char*)p->zPrefix, p->nPrefix,
                      SQLITE_STATIC);
    n = writeUtf8(zPrev, cPrev+1);
    sqlite3_bind_text(p->pStmt, 2, (char*)zPrev, n, SQLITE_STATIC);
    rc = sqlite3_step(p->pStmt);
    if( rc==SQLITE_DONE ){
      sqlite3_reset(p->pStmt);
      return;
    }else if( rc!=SQLITE_ROW ){
      p->otherError = rc;
      return;
    }else{
      const unsigned char *zOut = sqlite3_column_text(p->pStmt, 0);
      unsigned cNext;
      n = readUtf8(zOut+p->nPrefix, &cNext);
      sqlite3_reset(p->pStmt);
      nextCharAppend(p, cNext);
      cPrev = cNext;
      if( p->mallocFailed ) return;
    }
  }
}