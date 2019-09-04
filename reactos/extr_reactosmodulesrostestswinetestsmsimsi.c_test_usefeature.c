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

/* Variables and functions */
 scalar_t__ INSTALLSTATE_INVALIDARG ; 
 scalar_t__ MsiQueryFeatureStateA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pMsiUseFeatureExA (char*,char*,int,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_usefeature(void)
{
    INSTALLSTATE r;

    if (!pMsiUseFeatureExA)
    {
        win_skip("MsiUseFeatureExA not implemented\n");
        return;
    }

    r = MsiQueryFeatureStateA(NULL, NULL);
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return val\n");

    r = MsiQueryFeatureStateA("{9085040-6000-11d3-8cfe-0150048383c9}" ,NULL);
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return val\n");

    r = pMsiUseFeatureExA(NULL,NULL,0,0);
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return val\n");

    r = pMsiUseFeatureExA(NULL, "WORDVIEWFiles", -2, 1 );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return val\n");

    r = pMsiUseFeatureExA("{90850409-6000-11d3-8cfe-0150048383c9}", 
                         NULL, -2, 0 );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return val\n");

    r = pMsiUseFeatureExA("{9085040-6000-11d3-8cfe-0150048383c9}", 
                         "WORDVIEWFiles", -2, 0 );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return val\n");

    r = pMsiUseFeatureExA("{0085040-6000-11d3-8cfe-0150048383c9}", 
                         "WORDVIEWFiles", -2, 0 );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return val\n");

    r = pMsiUseFeatureExA("{90850409-6000-11d3-8cfe-0150048383c9}", 
                         "WORDVIEWFiles", -2, 1 );
    ok( r == INSTALLSTATE_INVALIDARG, "wrong return val\n");
}