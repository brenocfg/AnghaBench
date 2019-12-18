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
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */
 int CMDLINE ; 
 int Ctrl_C ; 
 int FALSE ; 
 int K_ZERO ; 
 int MB_BYTE2LEN_CHECK (int) ; 
 int State ; 
 void* TRUE ; 
 int /*<<< orphan*/  VIM_ISDIGIT (int) ; 
 int /*<<< orphan*/  add_to_showcmd (int) ; 
 int /*<<< orphan*/  allow_keys ; 
 void* dont_scroll ; 
 scalar_t__ enc_dbcs ; 
 int got_int ; 
 TYPE_1__ gui ; 
 int hex2nr (int) ; 
 int /*<<< orphan*/  no_mapping ; 
 int plain_vgetc () ; 
 int /*<<< orphan*/  vim_isxdigit (int) ; 
 int /*<<< orphan*/  vungetc (int) ; 

int
get_literal()
{
    int		cc;
    int		nc;
    int		i;
    int		hex = FALSE;
    int		octal = FALSE;
#ifdef FEAT_MBYTE
    int		unicode = 0;
#endif

    if (got_int)
	return Ctrl_C;

#ifdef FEAT_GUI
    /*
     * In GUI there is no point inserting the internal code for a special key.
     * It is more useful to insert the string "<KEY>" instead.	This would
     * probably be useful in a text window too, but it would not be
     * vi-compatible (maybe there should be an option for it?) -- webb
     */
    if (gui.in_use)
	++allow_keys;
#endif
#ifdef USE_ON_FLY_SCROLL
    dont_scroll = TRUE;		/* disallow scrolling here */
#endif
    ++no_mapping;		/* don't map the next key hits */
    cc = 0;
    i = 0;
    for (;;)
    {
	nc = plain_vgetc();
#ifdef FEAT_CMDL_INFO
	if (!(State & CMDLINE)
# ifdef FEAT_MBYTE
		&& MB_BYTE2LEN_CHECK(nc) == 1
# endif
	   )
	    add_to_showcmd(nc);
#endif
	if (nc == 'x' || nc == 'X')
	    hex = TRUE;
	else if (nc == 'o' || nc == 'O')
	    octal = TRUE;
#ifdef FEAT_MBYTE
	else if (nc == 'u' || nc == 'U')
	    unicode = nc;
#endif
	else
	{
	    if (hex
#ifdef FEAT_MBYTE
		    || unicode != 0
#endif
		    )
	    {
		if (!vim_isxdigit(nc))
		    break;
		cc = cc * 16 + hex2nr(nc);
	    }
	    else if (octal)
	    {
		if (nc < '0' || nc > '7')
		    break;
		cc = cc * 8 + nc - '0';
	    }
	    else
	    {
		if (!VIM_ISDIGIT(nc))
		    break;
		cc = cc * 10 + nc - '0';
	    }

	    ++i;
	}

	if (cc > 255
#ifdef FEAT_MBYTE
		&& unicode == 0
#endif
		)
	    cc = 255;		/* limit range to 0-255 */
	nc = 0;

	if (hex)		/* hex: up to two chars */
	{
	    if (i >= 2)
		break;
	}
#ifdef FEAT_MBYTE
	else if (unicode)	/* Unicode: up to four or eight chars */
	{
	    if ((unicode == 'u' && i >= 4) || (unicode == 'U' && i >= 8))
		break;
	}
#endif
	else if (i >= 3)	/* decimal or octal: up to three chars */
	    break;
    }
    if (i == 0)	    /* no number entered */
    {
	if (nc == K_ZERO)   /* NUL is stored as NL */
	{
	    cc = '\n';
	    nc = 0;
	}
	else
	{
	    cc = nc;
	    nc = 0;
	}
    }

    if (cc == 0)	/* NUL is stored as NL */
	cc = '\n';
#ifdef FEAT_MBYTE
    if (enc_dbcs && (cc & 0xff) == 0)
	cc = '?';	/* don't accept an illegal DBCS char, the NUL in the
			   second byte will cause trouble! */
#endif

    --no_mapping;
#ifdef FEAT_GUI
    if (gui.in_use)
	--allow_keys;
#endif
    if (nc)
	vungetc(nc);
    got_int = FALSE;	    /* CTRL-C typed after CTRL-V is not an interrupt */
    return cc;
}