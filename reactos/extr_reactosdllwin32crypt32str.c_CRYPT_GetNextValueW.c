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
typedef  int WCHAR ;
typedef  char* LPCWSTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CERT_NAME_STR_NO_QUOTING_FLAG ; 
 int /*<<< orphan*/  CRYPT_E_INVALID_X500_STRING ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 scalar_t__ isspaceW (char) ; 

__attribute__((used)) static BOOL CRYPT_GetNextValueW(LPCWSTR str, DWORD dwFlags, LPCWSTR separators,
 WCHAR *separator_used, struct X500TokenW *token, LPCWSTR *ppszError)
{
    BOOL ret = TRUE;

    TRACE("(%s, %s, %p, %p)\n", debugstr_w(str), debugstr_w(separators), token,
     ppszError);

    *separator_used = 0;
    while (*str && isspaceW(*str))
        str++;
    if (*str)
    {
        token->start = str;
        if (!(dwFlags & CERT_NAME_STR_NO_QUOTING_FLAG) && *str == '"')
        {
            token->end = NULL;
            str++;
            while (!token->end && ret)
            {
                while (*str && *str != '"')
                    str++;
                if (*str == '"')
                {
                    if (*(str + 1) != '"')
                        token->end = str + 1;
                    else
                        str += 2;
                }
                else
                {
                    TRACE("unterminated quote at %s\n", debugstr_w(str));
                    if (ppszError)
                        *ppszError = str;
                    SetLastError(CRYPT_E_INVALID_X500_STRING);
                    ret = FALSE;
                }
            }
        }
        else
        {
            WCHAR map[256] = { 0 };

            while (*separators)
                map[*separators++] = 1;
            while (*str && (*str >= 0xff || !map[*str]))
                str++;
            token->end = str;
            if (map[*str]) *separator_used = *str;
        }
    }
    else
    {
        TRACE("missing value at %s\n", debugstr_w(str));
        if (ppszError)
            *ppszError = str;
        SetLastError(CRYPT_E_INVALID_X500_STRING);
        ret = FALSE;
    }
    return ret;
}