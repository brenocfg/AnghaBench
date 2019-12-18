#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_4__ {scalar_t__ pVtab; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  pStorage; } ;
typedef  TYPE_2__ Fts5FullTable ;
typedef  TYPE_3__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */
 int sqlite3Fts5StorageSize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5ApiColumnTotalSize(
  Fts5Context *pCtx, 
  int iCol, 
  sqlite3_int64 *pnToken
){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  Fts5FullTable *pTab = (Fts5FullTable*)(pCsr->base.pVtab);
  return sqlite3Fts5StorageSize(pTab->pStorage, iCol, pnToken);
}