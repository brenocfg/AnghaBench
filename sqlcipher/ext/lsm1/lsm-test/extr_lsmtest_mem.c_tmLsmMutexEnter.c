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
struct TYPE_6__ {scalar_t__ pMutex; } ;
typedef  TYPE_2__ TmGlobal ;
struct TYPE_7__ {int /*<<< orphan*/  pMutex; TYPE_1__* pEnv; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* xMutexEnter ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ LsmMutex ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tmLsmMutexEnter(TmGlobal *pTm){
  LsmMutex *p = (LsmMutex *)pTm->pMutex;
  p->pEnv->xMutexEnter(p->pMutex);
}