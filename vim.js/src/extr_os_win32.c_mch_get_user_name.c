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
typedef  int /*<<< orphan*/  char_u ;
typedef  int DWORD ;

/* Variables and functions */
 int FAIL ; 
 scalar_t__ GetUserName (char*,int*) ; 
 int /*<<< orphan*/  NUL ; 
 int OK ; 
 int /*<<< orphan*/  vim_strncpy (int /*<<< orphan*/ *,char*,int) ; 

int
mch_get_user_name(
    char_u  *s,
    int	    len)
{
    char szUserName[256 + 1];	/* UNLEN is 256 */
    DWORD cch = sizeof szUserName;

    if (GetUserName(szUserName, &cch))
    {
	vim_strncpy(s, szUserName, len - 1);
	return OK;
    }
    s[0] = NUL;
    return FAIL;
}