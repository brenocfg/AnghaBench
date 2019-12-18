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
typedef  char char_u ;

/* Variables and functions */
 char NUL ; 
 scalar_t__ STRLEN (char*) ; 
 int mb_ptr2len (char*) ; 
 int /*<<< orphan*/  mch_memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int stub1 (char*) ; 
 int /*<<< orphan*/ * vim_strchr (char*,char) ; 

__attribute__((used)) static void
unescape_shellxquote(char_u *p, char_u *escaped)
{
    int	    l = (int)STRLEN(p);
    int	    n;

    while (*p != NUL)
    {
	if (*p == '^' && vim_strchr(escaped, p[1]) != NULL)
	    mch_memmove(p, p + 1, l--);
#ifdef FEAT_MBYTE
	n = (*mb_ptr2len)(p);
#else
	n = 1;
#endif
	p += n;
	l -= n;
    }
}