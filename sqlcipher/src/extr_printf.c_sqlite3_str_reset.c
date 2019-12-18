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
struct TYPE_4__ {scalar_t__ zText; scalar_t__ nChar; scalar_t__ nAlloc; int /*<<< orphan*/  printfFlags; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ StrAccum ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_PRINTF_MALLOCED ; 
 scalar_t__ isMalloced (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,scalar_t__) ; 

void sqlite3_str_reset(StrAccum *p){
  if( isMalloced(p) ){
    sqlite3DbFree(p->db, p->zText);
    p->printfFlags &= ~SQLITE_PRINTF_MALLOCED;
  }
  p->nAlloc = 0;
  p->nChar = 0;
  p->zText = 0;
}