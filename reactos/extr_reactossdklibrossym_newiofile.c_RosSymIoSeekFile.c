#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_2__ {int /*<<< orphan*/  (* SeekFileProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PROSSYM_OWN_FILECONTEXT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN
RosSymIoSeekFile(PVOID FileContext, ULONG_PTR Position)
{
    PROSSYM_OWN_FILECONTEXT OwnContext = (PROSSYM_OWN_FILECONTEXT)FileContext;
    return OwnContext->SeekFileProc(FileContext, Position);
}