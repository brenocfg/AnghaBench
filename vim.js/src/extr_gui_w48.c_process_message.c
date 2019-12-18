#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  char char_u ;
typedef  char UINT ;
struct TYPE_14__ {int /*<<< orphan*/  row; int /*<<< orphan*/  col; scalar_t__ menu_is_active; } ;
struct TYPE_13__ {char key_sym; char vim_code1; int vim_code0; } ;
struct TYPE_12__ {scalar_t__ message; char wParam; scalar_t__ lParam; int /*<<< orphan*/  hwnd; } ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__ MSG ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
#define  CSI 131 
 char Ctrl_AT ; 
 char Ctrl_C ; 
 char Ctrl_HAT ; 
 char Ctrl__ ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILL_X (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILL_Y (int /*<<< orphan*/ ) ; 
 int GetKeyState (char) ; 
 int /*<<< orphan*/  HandleMouseHide (scalar_t__,scalar_t__) ; 
 scalar_t__ IS_SPECIAL (int) ; 
#define  KE_SNIFF 130 
#define  KS_EXTRA 129 
 char KS_MODIFIER ; 
 int K_CSI ; 
 char K_SECOND (int) ; 
#define  K_SPECIAL 128 
 char K_THIRD (int) ; 
 int MOD_MASK_ALT ; 
 int MOD_MASK_CTRL ; 
 int MOD_MASK_SHIFT ; 
 char MapVirtualKey (char,int) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  MyTranslateMessage (TYPE_2__*) ; 
 char NUL ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,scalar_t__,char,scalar_t__) ; 
 scalar_t__ STRLEN (char*) ; 
 int /*<<< orphan*/  State ; 
 int TO_SPECIAL (int,char) ; 
 int /*<<< orphan*/  TRUE ; 
 char VK_CANCEL ; 
 char VK_CONTROL ; 
 char VK_F10 ; 
 char VK_MENU ; 
 char VK_SHIFT ; 
 char VK_SPACE ; 
 scalar_t__ WM_IME_NOTIFY ; 
 scalar_t__ WM_IME_STARTCOMPOSITION ; 
 scalar_t__ WM_KEYDOWN ; 
 scalar_t__ WM_KEYUP ; 
 scalar_t__ WM_NETBEANS ; 
 scalar_t__ WM_OLE ; 
 scalar_t__ WM_SYSKEYDOWN ; 
 scalar_t__ WM_USER ; 
 int /*<<< orphan*/  _OnImeNotify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_to_input_buf (char*,int) ; 
 int char_to_string (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * check_map (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dead_key ; 
 int /*<<< orphan*/  global_ime_set_font (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_ime_set_position (TYPE_1__*) ; 
 int /*<<< orphan*/  got_int ; 
 TYPE_7__ gui ; 
 scalar_t__ im_get_status () ; 
 int /*<<< orphan*/  netbeans_read () ; 
 int /*<<< orphan*/  norm_logfont ; 
 int /*<<< orphan*/  pDispatchMessage (TYPE_2__*) ; 
 int /*<<< orphan*/  pGetMessage (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pIsDialogMessage (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * s_findrep_hwnd ; 
 int /*<<< orphan*/  s_hwnd ; 
 int /*<<< orphan*/  s_textArea ; 
 int simplify_key (int,int*) ; 
 scalar_t__ sniff_request_waiting ; 
 TYPE_3__* special_keys ; 
 int /*<<< orphan*/  trash_input_buf () ; 
 int /*<<< orphan*/  vim_free (char*) ; 
 scalar_t__ want_sniff_request ; 

__attribute__((used)) static void
process_message(void)
{
    MSG		msg;
    UINT	vk = 0;		/* Virtual key */
    char_u	string[40];
    int		i;
    int		modifiers = 0;
    int		key;
#ifdef FEAT_MENU
    static char_u k10[] = {K_SPECIAL, 'k', ';', 0};
#endif

    pGetMessage(&msg, NULL, 0, 0);

#ifdef FEAT_OLE
    /* Look after OLE Automation commands */
    if (msg.message == WM_OLE)
    {
	char_u *str = (char_u *)msg.lParam;
	if (str == NULL || *str == NUL)
	{
	    /* Message can't be ours, forward it.  Fixes problem with Ultramon
	     * 3.0.4 */
	    pDispatchMessage(&msg);
	}
	else
	{
	    add_to_input_buf(str, (int)STRLEN(str));
	    vim_free(str);  /* was allocated in CVim::SendKeys() */
	}
	return;
    }
#endif

#ifdef FEAT_NETBEANS_INTG
    if (msg.message == WM_NETBEANS)
    {
	netbeans_read();
	return;
    }
#endif

#ifdef FEAT_SNIFF
    if (sniff_request_waiting && want_sniff_request)
    {
	static char_u bytes[3] = {CSI, (char_u)KS_EXTRA, (char_u)KE_SNIFF};
	add_to_input_buf(bytes, 3); /* K_SNIFF */
	sniff_request_waiting = 0;
	want_sniff_request = 0;
	/* request is handled in normal.c */
    }
    if (msg.message == WM_USER)
    {
	MyTranslateMessage(&msg);
	pDispatchMessage(&msg);
	return;
    }
#endif

#ifdef MSWIN_FIND_REPLACE
    /* Don't process messages used by the dialog */
    if (s_findrep_hwnd != NULL && pIsDialogMessage(s_findrep_hwnd, &msg))
    {
	HandleMouseHide(msg.message, msg.lParam);
	return;
    }
#endif

    /*
     * Check if it's a special key that we recognise.  If not, call
     * TranslateMessage().
     */
    if (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN)
    {
	vk = (int) msg.wParam;
	/* handle key after dead key, but ignore shift, alt and control */
	if (dead_key && vk != VK_SHIFT && vk != VK_MENU && vk != VK_CONTROL)
	{
	    dead_key = 0;
	    /* handle non-alphabetic keys (ones that hopefully cannot generate
	     * umlaut-characters), unless when control is down */
	    if (vk < 'A' || vk > 'Z' || (GetKeyState(VK_CONTROL) & 0x8000))
	    {
		MSG dm;

		dm.message = msg.message;
		dm.hwnd = msg.hwnd;
		dm.wParam = VK_SPACE;
		MyTranslateMessage(&dm);	/* generate dead character */
		if (vk != VK_SPACE) /* and send current character once more */
		    PostMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		return;
	    }
	}

	/* Check for CTRL-BREAK */
	if (vk == VK_CANCEL)
	{
	    trash_input_buf();
	    got_int = TRUE;
	    string[0] = Ctrl_C;
	    add_to_input_buf(string, 1);
	}

	for (i = 0; special_keys[i].key_sym != 0; i++)
	{
	    /* ignore VK_SPACE when ALT key pressed: system menu */
	    if (special_keys[i].key_sym == vk
		    && (vk != VK_SPACE || !(GetKeyState(VK_MENU) & 0x8000)))
	    {
#ifdef FEAT_MENU
		/* Check for <F10>: Windows selects the menu.  When <F10> is
		 * mapped we want to use the mapping instead. */
		if (vk == VK_F10
			&& gui.menu_is_active
			&& check_map(k10, State, FALSE, TRUE, FALSE,
							  NULL, NULL) == NULL)
		    break;
#endif
		if (GetKeyState(VK_SHIFT) & 0x8000)
		    modifiers |= MOD_MASK_SHIFT;
		/*
		 * Don't use caps-lock as shift, because these are special keys
		 * being considered here, and we only want letters to get
		 * shifted -- webb
		 */
		/*
		if (GetKeyState(VK_CAPITAL) & 0x0001)
		    modifiers ^= MOD_MASK_SHIFT;
		*/
		if (GetKeyState(VK_CONTROL) & 0x8000)
		    modifiers |= MOD_MASK_CTRL;
		if (GetKeyState(VK_MENU) & 0x8000)
		    modifiers |= MOD_MASK_ALT;

		if (special_keys[i].vim_code1 == NUL)
		    key = special_keys[i].vim_code0;
		else
		    key = TO_SPECIAL(special_keys[i].vim_code0,
						   special_keys[i].vim_code1);
		key = simplify_key(key, &modifiers);
		if (key == CSI)
		    key = K_CSI;

		if (modifiers)
		{
		    string[0] = CSI;
		    string[1] = KS_MODIFIER;
		    string[2] = modifiers;
		    add_to_input_buf(string, 3);
		}

		if (IS_SPECIAL(key))
		{
		    string[0] = CSI;
		    string[1] = K_SECOND(key);
		    string[2] = K_THIRD(key);
		    add_to_input_buf(string, 3);
		}
		else
		{
		    int	len;

		    /* Handle "key" as a Unicode character. */
		    len = char_to_string(key, string, 40, FALSE);
		    add_to_input_buf(string, len);
		}
		break;
	    }
	}
	if (special_keys[i].key_sym == 0)
	{
	    /* Some keys need C-S- where they should only need C-.
	     * Ignore 0xff, Windows XP sends it when NUMLOCK has changed since
	     * system startup (Helmut Stiegler, 2003 Oct 3). */
	    if (vk != 0xff
		    && (GetKeyState(VK_CONTROL) & 0x8000)
		    && !(GetKeyState(VK_SHIFT) & 0x8000)
		    && !(GetKeyState(VK_MENU) & 0x8000))
	    {
		/* CTRL-6 is '^'; Japanese keyboard maps '^' to vk == 0xDE */
		if (vk == '6' || MapVirtualKey(vk, 2) == (UINT)'^')
		{
		    string[0] = Ctrl_HAT;
		    add_to_input_buf(string, 1);
		}
		/* vk == 0xBD AZERTY for CTRL-'-', but CTRL-[ for * QWERTY! */
		else if (vk == 0xBD)	/* QWERTY for CTRL-'-' */
		{
		    string[0] = Ctrl__;
		    add_to_input_buf(string, 1);
		}
		/* CTRL-2 is '@'; Japanese keyboard maps '@' to vk == 0xC0 */
		else if (vk == '2' || MapVirtualKey(vk, 2) == (UINT)'@')
		{
		    string[0] = Ctrl_AT;
		    add_to_input_buf(string, 1);
		}
		else
		    MyTranslateMessage(&msg);
	    }
	    else
		MyTranslateMessage(&msg);
	}
    }
#ifdef FEAT_MBYTE_IME
    else if (msg.message == WM_IME_NOTIFY)
	_OnImeNotify(msg.hwnd, (DWORD)msg.wParam, (DWORD)msg.lParam);
    else if (msg.message == WM_KEYUP && im_get_status())
	/* added for non-MS IME (Yasuhiro Matsumoto) */
	MyTranslateMessage(&msg);
#endif
#if !defined(FEAT_MBYTE_IME) && defined(GLOBAL_IME)
/* GIME_TEST */
    else if (msg.message == WM_IME_STARTCOMPOSITION)
    {
	POINT point;

	global_ime_set_font(&norm_logfont);
	point.x = FILL_X(gui.col);
	point.y = FILL_Y(gui.row);
	MapWindowPoints(s_textArea, s_hwnd, &point, 1);
	global_ime_set_position(&point);
    }
#endif

#ifdef FEAT_MENU
    /* Check for <F10>: Default effect is to select the menu.  When <F10> is
     * mapped we need to stop it here to avoid strange effects (e.g., for the
     * key-up event) */
    if (vk != VK_F10 || check_map(k10, State, FALSE, TRUE, FALSE,
							  NULL, NULL) == NULL)
#endif
	pDispatchMessage(&msg);
}