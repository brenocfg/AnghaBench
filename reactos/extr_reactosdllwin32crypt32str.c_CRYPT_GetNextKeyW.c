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
struct X500TokenW {char* start; char* end; } ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_E_INVALID_X500_STRING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 scalar_t__ isspaceW (char) ; 

__attribute__((used)) static BOOL CRYPT_GetNextKeyW(LPCWSTR str, struct X500TokenW *token,
 LPCWSTR *ppszError)
{
    BOOL ret = TRUE;

    while (*str && isspaceW(*str))
        str++;
    if (*str)
    {
        token->start = str;
        while (*str && *str != '=' && !isspaceW(*str))
            str++;
        if (*str && (*str == '=' || isspaceW(*str)))
            token->end = str;
        else
        {
            TRACE("missing equals char at %s\n", debugstr_w(token->start));
            if (ppszError)
                *ppszError = token->start;
            SetLastError(CRYPT_E_INVALID_X500_STRING);
            ret = FALSE;
        }
    }
    else
        token->start = NULL;
    return ret;
}