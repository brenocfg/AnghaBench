#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t iPage; int curFlags; scalar_t__ eState; int /*<<< orphan*/ * aiIdx; int /*<<< orphan*/  pgnoRoot; TYPE_1__** apPage; struct TYPE_10__* pNext; } ;
struct TYPE_9__ {TYPE_4__* pCursor; } ;
struct TYPE_8__ {TYPE_3__* pBt; } ;
struct TYPE_7__ {int /*<<< orphan*/  pgno; } ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ Btree ;
typedef  TYPE_3__ BtShared ;
typedef  TYPE_4__ BtCursor ;

/* Variables and functions */
 int BTCF_WriteFlag ; 
 scalar_t__ CURSOR_VALID ; 
 int /*<<< orphan*/  sqlite3DebugPrintf (char*,TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void sqlite3BtreeCursorList(Btree *p){
#ifdef SQLITE_DEBUG
  BtCursor *pCur;
  BtShared *pBt = p->pBt;
  for(pCur=pBt->pCursor; pCur; pCur=pCur->pNext){
    MemPage *pPage = pCur->apPage[pCur->iPage];
    char *zMode = (pCur->curFlags & BTCF_WriteFlag) ? "rw" : "ro";
    sqlite3DebugPrintf("CURSOR %p rooted at %4d(%s) currently at %d.%d%s\n",
       pCur, pCur->pgnoRoot, zMode,
       pPage ? pPage->pgno : 0, pCur->aiIdx[pCur->iPage],
       (pCur->eState==CURSOR_VALID) ? "" : " eof"
    );
  }
#endif
}