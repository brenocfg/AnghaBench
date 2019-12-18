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
typedef  int WCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pNcIsValidConnectionName (int*) ; 
 int /*<<< orphan*/ * wcspbrk (int*,char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int*) ; 

__attribute__((used)) static void test_BadLetters(void)
{
    BOOL ret;

    WCHAR buf[3] = { 0 };
    int i;

    for (i = 1; i <= 0xFFFF; ++i)
    {
        buf[0] = (WCHAR)i;
        buf[1] = buf[2] = L'\0';

        if (wcspbrk(buf, L"\\/:\t*? <>|\"") != NULL)
        {
            ret = pNcIsValidConnectionName(buf);
            ok(ret == FALSE, "Expected %s (%i) to fail.\n", wine_dbgstr_w(buf), i);

            /* How about two of a kind? */
            buf[1] = (WCHAR)i;
            ret = pNcIsValidConnectionName(buf);
            ok(ret == FALSE, "Expected %s (%i) to fail.\n", wine_dbgstr_w(buf), i);

            /* And something (bad) combined with a space? */
            buf[1] = L' ';
            ret = pNcIsValidConnectionName(buf);
            ok(ret == FALSE, "Expected %s (%i) to fail.\n", wine_dbgstr_w(buf), i);


            /* Something bad combined with a letter */
            buf[1] = L'a';
            ret = pNcIsValidConnectionName(buf);
            if ((WCHAR)i == L' ')
                ok(ret == TRUE, "Expected %s (%i) to succeed.\n", wine_dbgstr_w(buf), i);
            else
                ok(ret == FALSE, "Expected %s (%i) to fail.\n", wine_dbgstr_w(buf), i);
        }
        else
        {
            ret = pNcIsValidConnectionName(buf);
            ok(ret == TRUE, "Expected %s (%i) to succeed.\n", wine_dbgstr_w(buf), i);

            buf[1] = (WCHAR)i;
            ret = pNcIsValidConnectionName(buf);
            ok(ret == TRUE, "Expected %s (%i) to succeed.\n", wine_dbgstr_w(buf), i);

            buf[1] = L'a';
            ret = pNcIsValidConnectionName(buf);
            ok(ret == TRUE, "Expected %s (%i) to succeed.\n", wine_dbgstr_w(buf), i);

            buf[1] = L' ';
            ret = pNcIsValidConnectionName(buf);
            ok(ret == TRUE, "Expected %s (%i) to succeed.\n", wine_dbgstr_w(buf), i);
        }
    }
}