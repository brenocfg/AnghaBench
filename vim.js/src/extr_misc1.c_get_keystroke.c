#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  long_u ;
typedef  void* char_u ;

/* Variables and functions */
 int CMDLINE ; 
 int ESC ; 
 int FALSE ; 
 int KEYLEN_REMOVED ; 
 void* KS_MODIFIER ; 
 int K_HOR_SCROLLBAR ; 
 int K_IGNORE ; 
 int K_LEFTMOUSE ; 
 int K_SPECIAL ; 
 int K_VER_SCROLLBAR ; 
 int MB_BYTE2LEN (int) ; 
 void* NUL ; 
 int State ; 
 int TO_SPECIAL (void*,void*) ; 
 void** alloc (int) ; 
 int check_termcode (int,void**,int,int*) ; 
 int /*<<< orphan*/  cursor_on () ; 
 int /*<<< orphan*/  do_outofmem_msg (int /*<<< orphan*/ ) ; 
 int fix_input_buffer (void**,int,int) ; 
 scalar_t__ has_mbyte ; 
 int intr_char ; 
 scalar_t__ is_mouse_key (int) ; 
 int mapped_ctrl_c ; 
 int mb_ptr2char (void**) ; 
 int /*<<< orphan*/  mch_memmove (void**,void**,size_t) ; 
 void* mod_mask ; 
 scalar_t__ must_redraw ; 
 int /*<<< orphan*/  need_wait_return ; 
 int /*<<< orphan*/  out_flush () ; 
 int p_tm ; 
 int /*<<< orphan*/  p_ttimeout ; 
 int p_ttm ; 
 int /*<<< orphan*/  setcursor () ; 
 int stub1 (void**) ; 
 int ui_inchar (void**,int,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_screen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_free (void**) ; 
 void** vim_realloc (void**,int) ; 

int
get_keystroke()
{
    char_u	*buf = NULL;
    int		buflen = 150;
    int		maxlen;
    int		len = 0;
    int		n;
    int		save_mapped_ctrl_c = mapped_ctrl_c;
    int		waited = 0;

    mapped_ctrl_c = FALSE;	/* mappings are not used here */
    for (;;)
    {
	cursor_on();
	out_flush();

	/* Leave some room for check_termcode() to insert a key code into (max
	 * 5 chars plus NUL).  And fix_input_buffer() can triple the number of
	 * bytes. */
	maxlen = (buflen - 6 - len) / 3;
	if (buf == NULL)
	    buf = alloc(buflen);
	else if (maxlen < 10)
	{
	    /* Need some more space. This might happen when receiving a long
	     * escape sequence. */
	    buflen += 100;
	    buf = vim_realloc(buf, buflen);
	    maxlen = (buflen - 6 - len) / 3;
	}
	if (buf == NULL)
	{
	    do_outofmem_msg((long_u)buflen);
	    return ESC;  /* panic! */
	}

	/* First time: blocking wait.  Second time: wait up to 100ms for a
	 * terminal code to complete. */
	n = ui_inchar(buf + len, maxlen, len == 0 ? -1L : 100L, 0);
	if (n > 0)
	{
	    /* Replace zero and CSI by a special key code. */
	    n = fix_input_buffer(buf + len, n, FALSE);
	    len += n;
	    waited = 0;
	}
	else if (len > 0)
	    ++waited;	    /* keep track of the waiting time */

	/* Incomplete termcode and not timed out yet: get more characters */
	if ((n = check_termcode(1, buf, buflen, &len)) < 0
	       && (!p_ttimeout || waited * 100L < (p_ttm < 0 ? p_tm : p_ttm)))
	    continue;

	if (n == KEYLEN_REMOVED)  /* key code removed */
	{
	    if (must_redraw != 0 && !need_wait_return && (State & CMDLINE) == 0)
	    {
		/* Redrawing was postponed, do it now. */
		update_screen(0);
		setcursor(); /* put cursor back where it belongs */
	    }
	    continue;
	}
	if (n > 0)		/* found a termcode: adjust length */
	    len = n;
	if (len == 0)		/* nothing typed yet */
	    continue;

	/* Handle modifier and/or special key code. */
	n = buf[0];
	if (n == K_SPECIAL)
	{
	    n = TO_SPECIAL(buf[1], buf[2]);
	    if (buf[1] == KS_MODIFIER
		    || n == K_IGNORE
#ifdef FEAT_MOUSE
		    || (is_mouse_key(n) && n != K_LEFTMOUSE)
#endif
#ifdef FEAT_GUI
		    || n == K_VER_SCROLLBAR
		    || n == K_HOR_SCROLLBAR
#endif
	       )
	    {
		if (buf[1] == KS_MODIFIER)
		    mod_mask = buf[2];
		len -= 3;
		if (len > 0)
		    mch_memmove(buf, buf + 3, (size_t)len);
		continue;
	    }
	    break;
	}
#ifdef FEAT_MBYTE
	if (has_mbyte)
	{
	    if (MB_BYTE2LEN(n) > len)
		continue;	/* more bytes to get */
	    buf[len >= buflen ? buflen - 1 : len] = NUL;
	    n = (*mb_ptr2char)(buf);
	}
#endif
#ifdef UNIX
	if (n == intr_char)
	    n = ESC;
#endif
	break;
    }
    vim_free(buf);

    mapped_ctrl_c = save_mapped_ctrl_c;
    return n;
}