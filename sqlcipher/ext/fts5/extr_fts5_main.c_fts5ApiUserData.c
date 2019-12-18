#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pAux; } ;
struct TYPE_3__ {void* pUserData; } ;
typedef  TYPE_2__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */

__attribute__((used)) static void *fts5ApiUserData(Fts5Context *pCtx){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  return pCsr->pAux->pUserData;
}