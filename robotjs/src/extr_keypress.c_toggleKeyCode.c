#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ kern_return_t ;
typedef  int UInt32 ;
struct TYPE_11__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int* L; } ;
struct TYPE_9__ {TYPE_1__ misc; int /*<<< orphan*/  subType; } ;
struct TYPE_10__ {TYPE_2__ compound; } ;
typedef  TYPE_3__ NXEventData ;
typedef  int MMKeyFlags ;
typedef  int MMKeyCode ;
typedef  TYPE_4__ IOGPoint ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CGKeyCode ;
typedef  int /*<<< orphan*/ * CGEventRef ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CGEventCreateKeyboardEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  CGEventPost (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CGEventSetFlags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CGEventSetType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  False ; 
 scalar_t__ IOHIDPostEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  KEYEVENTF_KEYUP ; 
 int /*<<< orphan*/  K_ALT ; 
 int /*<<< orphan*/  K_CONTROL ; 
 int /*<<< orphan*/  K_META ; 
 int /*<<< orphan*/  K_SHIFT ; 
 int MOD_ALT ; 
 int MOD_CONTROL ; 
 int MOD_META ; 
 int MOD_SHIFT ; 
 int NX_KEYDOWN ; 
 int NX_KEYUP ; 
 int /*<<< orphan*/  NX_SUBTYPE_AUX_CONTROL_BUTTONS ; 
 int /*<<< orphan*/  NX_SYSDEFINED ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  WIN32_KEY_EVENT_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * XGetMainDisplay () ; 
 int /*<<< orphan*/  X_KEY_EVENT (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  X_KEY_EVENT_WAIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  _getAuxiliaryKeyDriver () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  kCGEventKeyDown ; 
 int /*<<< orphan*/  kCGEventKeyUp ; 
 int /*<<< orphan*/  kCGSessionEventTap ; 
 int /*<<< orphan*/  kNXEventDataVersion ; 
 int /*<<< orphan*/  win32KeyEvent (int,int /*<<< orphan*/  const) ; 

void toggleKeyCode(MMKeyCode code, const bool down, MMKeyFlags flags)
{
#if defined(IS_MACOSX)
	/* The media keys all have 1000 added to them to help us detect them. */
	if (code >= 1000) {
		code = code - 1000; /* Get the real keycode. */
		NXEventData   event;
		kern_return_t kr;
		IOGPoint loc = { 0, 0 };
		UInt32 evtInfo = code << 16 | (down?NX_KEYDOWN:NX_KEYUP) << 8;
		bzero(&event, sizeof(NXEventData));
		event.compound.subType = NX_SUBTYPE_AUX_CONTROL_BUTTONS;
		event.compound.misc.L[0] = evtInfo;
		kr = IOHIDPostEvent( _getAuxiliaryKeyDriver(), NX_SYSDEFINED, loc, &event, kNXEventDataVersion, 0, FALSE );
		assert( KERN_SUCCESS == kr );
	} else {
		CGEventRef keyEvent = CGEventCreateKeyboardEvent(NULL,
		                                                 (CGKeyCode)code, down);
		assert(keyEvent != NULL);

		CGEventSetType(keyEvent, down ? kCGEventKeyDown : kCGEventKeyUp);
		CGEventSetFlags(keyEvent, flags);
		CGEventPost(kCGSessionEventTap, keyEvent);
		CFRelease(keyEvent);
	}
#elif defined(IS_WINDOWS)
	const DWORD dwFlags = down ? 0 : KEYEVENTF_KEYUP;

	/* Parse modifier keys. */
	if (flags & MOD_META) WIN32_KEY_EVENT_WAIT(K_META, dwFlags);
	if (flags & MOD_ALT) WIN32_KEY_EVENT_WAIT(K_ALT, dwFlags);
	if (flags & MOD_CONTROL) WIN32_KEY_EVENT_WAIT(K_CONTROL, dwFlags);
	if (flags & MOD_SHIFT) WIN32_KEY_EVENT_WAIT(K_SHIFT, dwFlags);

	win32KeyEvent(code, dwFlags);
#elif defined(USE_X11)
	Display *display = XGetMainDisplay();
	const Bool is_press = down ? True : False; /* Just to be safe. */

	/* Parse modifier keys. */
	if (flags & MOD_META) X_KEY_EVENT_WAIT(display, K_META, is_press);
	if (flags & MOD_ALT) X_KEY_EVENT_WAIT(display, K_ALT, is_press);
	if (flags & MOD_CONTROL) X_KEY_EVENT_WAIT(display, K_CONTROL, is_press);
	if (flags & MOD_SHIFT) X_KEY_EVENT_WAIT(display, K_SHIFT, is_press);

	X_KEY_EVENT(display, code, is_press);
#endif
}