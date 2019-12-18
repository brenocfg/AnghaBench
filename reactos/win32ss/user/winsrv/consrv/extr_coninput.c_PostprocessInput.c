#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  ReadWaitQueue; } ;
typedef  TYPE_1__* PCONSRV_CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CsrDereferenceWait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CsrNotifyWait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID
PostprocessInput(PCONSRV_CONSOLE Console)
{
    CsrNotifyWait(&Console->ReadWaitQueue,
                  FALSE,
                  NULL,
                  NULL);
    if (!IsListEmpty(&Console->ReadWaitQueue))
    {
        CsrDereferenceWait(&Console->ReadWaitQueue);
    }
}