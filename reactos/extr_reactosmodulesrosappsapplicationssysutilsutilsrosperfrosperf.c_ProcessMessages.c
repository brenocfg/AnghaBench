#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ message; int /*<<< orphan*/  wParam; } ;
typedef  TYPE_1__ MSG ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessageW (TYPE_1__*) ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageW (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TranslateMessage (TYPE_1__*) ; 
 scalar_t__ WM_QUIT ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ProcessMessages(void)
{
  MSG Msg;

  while (PeekMessageW(&Msg, NULL, 0, 0, PM_REMOVE))
    {
      if (WM_QUIT == Msg.message)
        {
          exit(Msg.wParam);
        }
      TranslateMessage(&Msg);
      DispatchMessageW(&Msg);
    }
}