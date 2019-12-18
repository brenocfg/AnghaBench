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
typedef  scalar_t__ char_u ;
struct TYPE_2__ {scalar_t__ vc_type; } ;

/* Variables and functions */
 scalar_t__ CONV_NONE ; 
 scalar_t__ CSI ; 
 int Ctrl_C ; 
 scalar_t__ ESC ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KE_CURSORHOLD ; 
 scalar_t__ KE_SNIFF ; 
 scalar_t__ KS_EXTRA ; 
 scalar_t__ KS_MODIFIER ; 
 int K_NUL ; 
 scalar_t__ K_SPECIAL ; 
 int MOD_MASK_ALT ; 
 scalar_t__ NUL ; 
 int /*<<< orphan*/  TRUE ; 
 int TYPEAHEADLEN ; 
 scalar_t__ WaitForChar (long) ; 
 int /*<<< orphan*/  before_blocking () ; 
 int convert_input_safe (scalar_t__*,int,int,scalar_t__**,int*) ; 
 scalar_t__ ctrl_c_interrupts ; 
 int /*<<< orphan*/  enc_dbcs ; 
 scalar_t__ fdDump ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int,int) ; 
 int /*<<< orphan*/  fputc (int,scalar_t__) ; 
 int /*<<< orphan*/  fputs (char*,scalar_t__) ; 
 int /*<<< orphan*/  g_fCBrkPressed ; 
 int g_nMouseClick ; 
 int g_xMouse ; 
 int g_yMouse ; 
 int /*<<< orphan*/  got_int ; 
 TYPE_1__ input_conv ; 
 int mb_char2bytes (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  mch_memmove (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  mch_set_winsize_now () ; 
 long p_ut ; 
 scalar_t__ sniff_request_waiting ; 
 int stub1 (scalar_t__,scalar_t__*) ; 
 int tgetch (int*,scalar_t__*) ; 
 int /*<<< orphan*/  trash_input_buf () ; 
 scalar_t__ trigger_cursorhold () ; 
 scalar_t__ typebuf_changed (int) ; 
 int /*<<< orphan*/  vim_free (scalar_t__*) ; 
 scalar_t__ want_sniff_request ; 

int
mch_inchar(
    char_u	*buf,
    int		maxlen,
    long	time,
    int		tb_change_cnt)
{
#ifndef FEAT_GUI_W32	    /* this isn't used for the GUI */

    int		len;
    int		c;
#define TYPEAHEADLEN 20
    static char_u   typeahead[TYPEAHEADLEN];	/* previously typed bytes. */
    static int	    typeaheadlen = 0;
#ifdef FEAT_MBYTE
    static char_u   *rest = NULL;	/* unconverted rest of previous read */
    static int	    restlen = 0;
    int		    unconverted;
#endif

    /* First use any typeahead that was kept because "buf" was too small. */
    if (typeaheadlen > 0)
	goto theend;

#ifdef FEAT_SNIFF
    if (want_sniff_request)
    {
	if (sniff_request_waiting)
	{
	    /* return K_SNIFF */
	    typeahead[typeaheadlen++] = CSI;
	    typeahead[typeaheadlen++] = (char_u)KS_EXTRA;
	    typeahead[typeaheadlen++] = (char_u)KE_SNIFF;
	    sniff_request_waiting = 0;
	    want_sniff_request = 0;
	    goto theend;
	}
	else if (time < 0 || time > 250)
	{
	    /* don't wait too long, a request might be pending */
	    time = 250;
	}
    }
#endif

    if (time >= 0)
    {
	if (!WaitForChar(time))     /* no character available */
	    return 0;
    }
    else    /* time == -1, wait forever */
    {
	mch_set_winsize_now();	/* Allow winsize changes from now on */

	/*
	 * If there is no character available within 2 seconds (default)
	 * write the autoscript file to disk.  Or cause the CursorHold event
	 * to be triggered.
	 */
	if (!WaitForChar(p_ut))
	{
#ifdef FEAT_AUTOCMD
	    if (trigger_cursorhold() && maxlen >= 3)
	    {
		buf[0] = K_SPECIAL;
		buf[1] = KS_EXTRA;
		buf[2] = (int)KE_CURSORHOLD;
		return 3;
	    }
#endif
	    before_blocking();
	}
    }

    /*
     * Try to read as many characters as there are, until the buffer is full.
     */

    /* we will get at least one key. Get more if they are available. */
    g_fCBrkPressed = FALSE;

#ifdef MCH_WRITE_DUMP
    if (fdDump)
	fputc('[', fdDump);
#endif

    /* Keep looping until there is something in the typeahead buffer and more
     * to get and still room in the buffer (up to two bytes for a char and
     * three bytes for a modifier). */
    while ((typeaheadlen == 0 || WaitForChar(0L))
					  && typeaheadlen + 5 <= TYPEAHEADLEN)
    {
	if (typebuf_changed(tb_change_cnt))
	{
	    /* "buf" may be invalid now if a client put something in the
	     * typeahead buffer and "buf" is in the typeahead buffer. */
	    typeaheadlen = 0;
	    break;
	}
#ifdef FEAT_MOUSE
	if (g_nMouseClick != -1)
	{
# ifdef MCH_WRITE_DUMP
	    if (fdDump)
		fprintf(fdDump, "{%02x @ %d, %d}",
			g_nMouseClick, g_xMouse, g_yMouse);
# endif
	    typeahead[typeaheadlen++] = ESC + 128;
	    typeahead[typeaheadlen++] = 'M';
	    typeahead[typeaheadlen++] = g_nMouseClick;
	    typeahead[typeaheadlen++] = g_xMouse + '!';
	    typeahead[typeaheadlen++] = g_yMouse + '!';
	    g_nMouseClick = -1;
	}
	else
#endif
	{
	    char_u	ch2 = NUL;
	    int		modifiers = 0;

	    c = tgetch(&modifiers, &ch2);

#ifdef FEAT_MBYTE
	    /* stolen from fill_input_buf() in ui.c */
	    if (rest != NULL)
	    {
		/* Use remainder of previous call, starts with an invalid
		 * character that may become valid when reading more. */
		if (restlen > TYPEAHEADLEN - typeaheadlen)
		    unconverted = TYPEAHEADLEN - typeaheadlen;
		else
		    unconverted = restlen;
		mch_memmove(typeahead + typeaheadlen, rest, unconverted);
		if (unconverted == restlen)
		{
		    vim_free(rest);
		    rest = NULL;
		}
		else
		{
		    restlen -= unconverted;
		    mch_memmove(rest, rest + unconverted, restlen);
		}
		typeaheadlen += unconverted;
	    }
	    else
		unconverted = 0;
#endif

	    if (typebuf_changed(tb_change_cnt))
	    {
		/* "buf" may be invalid now if a client put something in the
		 * typeahead buffer and "buf" is in the typeahead buffer. */
		typeaheadlen = 0;
		break;
	    }

	    if (c == Ctrl_C && ctrl_c_interrupts)
	    {
#if defined(FEAT_CLIENTSERVER)
		trash_input_buf();
#endif
		got_int = TRUE;
	    }

#ifdef FEAT_MOUSE
	    if (g_nMouseClick == -1)
#endif
	    {
		int	n = 1;

		/* A key may have one or two bytes. */
		typeahead[typeaheadlen] = c;
		if (ch2 != NUL)
		{
		    typeahead[typeaheadlen + 1] = ch2;
		    ++n;
		}
#ifdef FEAT_MBYTE
		/* Only convert normal characters, not special keys.  Need to
		 * convert before applying ALT, otherwise mapping <M-x> breaks
		 * when 'tenc' is set. */
		if (input_conv.vc_type != CONV_NONE
						&& (ch2 == NUL || c != K_NUL))
		{
		    typeaheadlen -= unconverted;
		    n = convert_input_safe(typeahead + typeaheadlen,
				n + unconverted, TYPEAHEADLEN - typeaheadlen,
				rest == NULL ? &rest : NULL, &restlen);
		}
#endif

		/* Use the ALT key to set the 8th bit of the character
		 * when it's one byte, the 8th bit isn't set yet and not
		 * using a double-byte encoding (would become a lead
		 * byte). */
		if ((modifiers & MOD_MASK_ALT)
			&& n == 1
			&& (typeahead[typeaheadlen] & 0x80) == 0
#ifdef FEAT_MBYTE
			&& !enc_dbcs
#endif
		   )
		{
#ifdef FEAT_MBYTE
		    n = (*mb_char2bytes)(typeahead[typeaheadlen] | 0x80,
						    typeahead + typeaheadlen);
#else
		    typeahead[typeaheadlen] |= 0x80;
#endif
		    modifiers &= ~MOD_MASK_ALT;
		}

		if (modifiers != 0)
		{
		    /* Prepend modifiers to the character. */
		    mch_memmove(typeahead + typeaheadlen + 3,
						 typeahead + typeaheadlen, n);
		    typeahead[typeaheadlen++] = K_SPECIAL;
		    typeahead[typeaheadlen++] = (char_u)KS_MODIFIER;
		    typeahead[typeaheadlen++] =  modifiers;
		}

		typeaheadlen += n;

#ifdef MCH_WRITE_DUMP
		if (fdDump)
		    fputc(c, fdDump);
#endif
	    }
	}
    }

#ifdef MCH_WRITE_DUMP
    if (fdDump)
    {
	fputs("]\n", fdDump);
	fflush(fdDump);
    }
#endif

theend:
    /* Move typeahead to "buf", as much as fits. */
    len = 0;
    while (len < maxlen && typeaheadlen > 0)
    {
	buf[len++] = typeahead[0];
	mch_memmove(typeahead, typeahead + 1, --typeaheadlen);
    }
    return len;

#else /* FEAT_GUI_W32 */
    return 0;
#endif /* FEAT_GUI_W32 */
}