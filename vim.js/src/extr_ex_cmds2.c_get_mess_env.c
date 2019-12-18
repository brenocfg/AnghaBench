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
typedef  scalar_t__ char_u ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 scalar_t__ NUL ; 
 scalar_t__ VIM_ISDIGIT (scalar_t__) ; 
 scalar_t__ get_locale_val (int /*<<< orphan*/ ) ; 
 scalar_t__* mch_getenv (scalar_t__*) ; 

__attribute__((used)) static char_u *
get_mess_env()
{
    char_u	*p;

    p = mch_getenv((char_u *)"LC_ALL");
    if (p == NULL || *p == NUL)
    {
	p = mch_getenv((char_u *)"LC_MESSAGES");
	if (p == NULL || *p == NUL)
	{
	    p = mch_getenv((char_u *)"LANG");
	    if (p != NULL && VIM_ISDIGIT(*p))
		p = NULL;		/* ignore something like "1043" */
# ifdef HAVE_GET_LOCALE_VAL
	    if (p == NULL || *p == NUL)
		p = (char_u *)get_locale_val(LC_CTYPE);
# endif
	}
    }
    return p;
}