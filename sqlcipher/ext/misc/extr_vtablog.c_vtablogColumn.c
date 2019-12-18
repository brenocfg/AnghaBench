#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zVal ;
struct TYPE_5__ {int iInst; } ;
typedef  TYPE_1__ vtablog_vtab ;
struct TYPE_6__ {int iCursor; int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_2__ vtablog_cursor ;
struct TYPE_7__ {scalar_t__ pVtab; } ;
typedef  TYPE_3__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  printf (char*,int,int,int,char*) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vtablogColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  vtablog_cursor *pCur = (vtablog_cursor*)cur;
  vtablog_vtab *pTab = (vtablog_vtab*)cur->pVtab;
  char zVal[50];

  if( i<26 ){
    sqlite3_snprintf(sizeof(zVal),zVal,"%c%d", 
                     "abcdefghijklmnopqrstuvwyz"[i], pCur->iRowid);
  }else{
    sqlite3_snprintf(sizeof(zVal),zVal,"{%d}%d", i, pCur->iRowid);
  }
  printf("vtablogColumn(tab=%d, cursor=%d, i=%d): [%s]\n",
         pTab->iInst, pCur->iCursor, i, zVal);
  sqlite3_result_text(ctx, zVal, -1, SQLITE_TRANSIENT);
  return SQLITE_OK;
}