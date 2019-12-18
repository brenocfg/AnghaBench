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
struct TYPE_6__ {scalar_t__ p; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int zContentRowid; scalar_t__ eContent; int nCol; int* azCol; char* zContentExprlist; } ;
typedef  TYPE_1__ Fts5Config ;
typedef  TYPE_2__ Fts5Buffer ;

/* Variables and functions */
 scalar_t__ FTS5_CONTENT_EXTERNAL ; 
 scalar_t__ FTS5_CONTENT_NONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferAppendPrintf (int*,TYPE_2__*,char*,int) ; 

__attribute__((used)) static int fts5ConfigMakeExprlist(Fts5Config *p){
  int i;
  int rc = SQLITE_OK;
  Fts5Buffer buf = {0, 0, 0};

  sqlite3Fts5BufferAppendPrintf(&rc, &buf, "T.%Q", p->zContentRowid);
  if( p->eContent!=FTS5_CONTENT_NONE ){
    for(i=0; i<p->nCol; i++){
      if( p->eContent==FTS5_CONTENT_EXTERNAL ){
        sqlite3Fts5BufferAppendPrintf(&rc, &buf, ", T.%Q", p->azCol[i]);
      }else{
        sqlite3Fts5BufferAppendPrintf(&rc, &buf, ", T.c%d", i);
      }
    }
  }

  assert( p->zContentExprlist==0 );
  p->zContentExprlist = (char*)buf.p;
  return rc;
}