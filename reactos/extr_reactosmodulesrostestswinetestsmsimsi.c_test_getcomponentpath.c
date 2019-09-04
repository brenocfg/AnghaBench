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
typedef  scalar_t__ INSTALLSTATE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ INSTALLSTATE_INVALIDARG ; 
 scalar_t__ INSTALLSTATE_UNKNOWN ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pMsiGetComponentPathA (char*,char*,char*,int*) ; 

__attribute__((used)) static void test_getcomponentpath(void)
{
    INSTALLSTATE r;
    char buffer[0x100];
    DWORD sz;

    if(!pMsiGetComponentPathA)
        return;

    r = pMsiGetComponentPathA( NULL, NULL, NULL, NULL );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return value\n");

    r = pMsiGetComponentPathA( "bogus", "bogus", NULL, NULL );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return value\n");

    r = pMsiGetComponentPathA( "bogus", "{00000000-0000-0000-000000000000}", NULL, NULL );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return value\n");

    sz = sizeof buffer;
    buffer[0]=0;
    r = pMsiGetComponentPathA( "bogus", "{00000000-0000-0000-000000000000}", buffer, &sz );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return value\n");

    r = pMsiGetComponentPathA( "{00000000-78E1-11D2-B60F-006097C998E7}",
        "{00000000-0000-0000-0000-000000000000}", buffer, &sz );
    ok( r == INSTALLSTATE_UNKNOWN, "wrong return value\n");

    r = pMsiGetComponentPathA( "{00000409-78E1-11D2-B60F-006097C998E7}",
        "{00000000-0000-0000-0000-00000000}", buffer, &sz );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return value\n");

    r = pMsiGetComponentPathA( "{00000409-78E1-11D2-B60F-006097C998E7}",
        "{029E403D-A86A-1D11-5B5B0006799C897E}", buffer, &sz );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return value\n");

    r = pMsiGetComponentPathA( "{00000000-78E1-11D2-B60F-006097C9987e}",
                            "{00000000-A68A-11d1-5B5B-0006799C897E}", buffer, &sz );
    ok( r == INSTALLSTATE_UNKNOWN, "wrong return value\n");
}