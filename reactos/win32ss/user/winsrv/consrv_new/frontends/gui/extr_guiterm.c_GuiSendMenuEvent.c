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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  dwCommandId; } ;
struct TYPE_6__ {TYPE_1__ MenuEvent; } ;
struct TYPE_7__ {TYPE_2__ Event; int /*<<< orphan*/  EventType; } ;
typedef  int /*<<< orphan*/  PCONSOLE ;
typedef  TYPE_3__ INPUT_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConioProcessInputEvent (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  MENU_EVENT ; 

__attribute__((used)) static VOID
GuiSendMenuEvent(PCONSOLE Console, UINT CmdId)
{
    INPUT_RECORD er;

    er.EventType = MENU_EVENT;
    er.Event.MenuEvent.dwCommandId = CmdId;

    ConioProcessInputEvent(Console, &er);
}