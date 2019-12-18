#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_5__ {int /*<<< orphan*/  MouseEvent; int /*<<< orphan*/  KeyEvent; } ;
struct TYPE_6__ {scalar_t__ EventType; TYPE_1__ Event; } ;
typedef  TYPE_2__ INPUT_RECORD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ FOCUS_EVENT ; 
 scalar_t__ KEY_EVENT ; 
 scalar_t__ MOUSE_EVENT ; 
 scalar_t__ ReadConsoleInput (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINDOW_BUFFER_SIZE_EVENT ; 
 int /*<<< orphan*/  WaitForChar (long) ; 
 int /*<<< orphan*/  create_conin () ; 
 scalar_t__ decode_key_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ decode_mouse_event (int /*<<< orphan*/ *) ; 
 scalar_t__ did_create_conin ; 
 int /*<<< orphan*/  g_hConIn ; 
 int g_nMouseClick ; 
 int /*<<< orphan*/  handle_focus_event (TYPE_2__) ; 
 scalar_t__ input_available () ; 
 int /*<<< orphan*/  read_error_exit () ; 
 int /*<<< orphan*/  shell_resized () ; 

__attribute__((used)) static char_u
tgetch(int *pmodifiers, char_u *pch2)
{
    char_u ch;

    for (;;)
    {
	INPUT_RECORD ir;
	DWORD cRecords = 0;

#ifdef FEAT_CLIENTSERVER
	(void)WaitForChar(-1L);
	if (input_available())
	    return 0;
# ifdef FEAT_MOUSE
	if (g_nMouseClick != -1)
	    return 0;
# endif
#endif
	if (ReadConsoleInput(g_hConIn, &ir, 1, &cRecords) == 0)
	{
	    if (did_create_conin)
		read_error_exit();
	    create_conin();
	    continue;
	}

	if (ir.EventType == KEY_EVENT)
	{
	    if (decode_key_event(&ir.Event.KeyEvent, &ch, pch2,
							    pmodifiers, TRUE))
		return ch;
	}
	else if (ir.EventType == FOCUS_EVENT)
	    handle_focus_event(ir);
	else if (ir.EventType == WINDOW_BUFFER_SIZE_EVENT)
	    shell_resized();
#ifdef FEAT_MOUSE
	else if (ir.EventType == MOUSE_EVENT)
	{
	    if (decode_mouse_event(&ir.Event.MouseEvent))
		return 0;
	}
#endif
    }
}