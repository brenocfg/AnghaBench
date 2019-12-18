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
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int in_focus; } ;
typedef  int /*<<< orphan*/  TIMERPROC ;
typedef  int /*<<< orphan*/  MSG ;

/* Variables and functions */
 int FAIL ; 
 void* FALSE ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ *,scalar_t__) ; 
 int OK ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 int /*<<< orphan*/  SetActiveWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetForegroundWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ SetTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WM_TIMER ; 
 scalar_t__ _OnTimer ; 
 void* allow_scrollbar ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_mch_start_blink () ; 
 int /*<<< orphan*/  gui_mch_stop_blink () ; 
 scalar_t__ input_available () ; 
 int /*<<< orphan*/  netbeans_parse_messages () ; 
 scalar_t__ pPeekMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_message () ; 
 scalar_t__ s_busy_processing ; 
 int s_button_pending ; 
 int /*<<< orphan*/  s_getting_focus ; 
 int /*<<< orphan*/  s_hwnd ; 
 void* s_need_activate ; 
 void* s_timed_out ; 
 scalar_t__ s_wait_timer ; 

int
gui_mch_wait_for_chars(int wtime)
{
    MSG		msg;
    int		focus;

    s_timed_out = FALSE;

    if (wtime > 0)
    {
	/* Don't do anything while processing a (scroll) message. */
	if (s_busy_processing)
	    return FAIL;
	s_wait_timer = (UINT)SetTimer(NULL, 0, (UINT)wtime,
							 (TIMERPROC)_OnTimer);
    }

    allow_scrollbar = TRUE;

    focus = gui.in_focus;
    while (!s_timed_out)
    {
	/* Stop or start blinking when focus changes */
	if (gui.in_focus != focus)
	{
	    if (gui.in_focus)
		gui_mch_start_blink();
	    else
		gui_mch_stop_blink();
	    focus = gui.in_focus;
	}

	if (s_need_activate)
	{
#ifdef WIN32
	    (void)SetForegroundWindow(s_hwnd);
#else
	    (void)SetActiveWindow(s_hwnd);
#endif
	    s_need_activate = FALSE;
	}

#ifdef FEAT_NETBEANS_INTG
	/* Process the queued netbeans messages. */
	netbeans_parse_messages();
#endif

	/*
	 * Don't use gui_mch_update() because then we will spin-lock until a
	 * char arrives, instead we use GetMessage() to hang until an
	 * event arrives.  No need to check for input_buf_full because we are
	 * returning as soon as it contains a single char -- webb
	 */
	process_message();

	if (input_available())
	{
	    if (s_wait_timer != 0 && !s_timed_out)
	    {
		KillTimer(NULL, s_wait_timer);

		/* Eat spurious WM_TIMER messages */
		while (pPeekMessage(&msg, s_hwnd, WM_TIMER, WM_TIMER, PM_REMOVE))
		    ;
		s_wait_timer = 0;
	    }
	    allow_scrollbar = FALSE;

	    /* Clear pending mouse button, the release event may have been
	     * taken by the dialog window.  But don't do this when getting
	     * focus, we need the mouse-up event then. */
	    if (!s_getting_focus)
		s_button_pending = -1;

	    return OK;
	}
    }
    allow_scrollbar = FALSE;
    return FAIL;
}