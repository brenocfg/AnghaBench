#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pVtab; } ;
struct TYPE_8__ {TYPE_2__ base; } ;
struct TYPE_7__ {TYPE_1__* pConfig; } ;
struct TYPE_5__ {int nCol; } ;
typedef  TYPE_3__ Fts5Table ;
typedef  TYPE_4__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */

__attribute__((used)) static int fts5ApiColumnCount(Fts5Context *pCtx){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  return ((Fts5Table*)(pCsr->base.pVtab))->pConfig->nCol;
}