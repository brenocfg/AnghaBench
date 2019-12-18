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

/* Variables and functions */
 int _getmbcp () ; 
 int _mbsspn (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  _setmbcp (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_mbsspn( void)
{
    unsigned char str1[]="cabernet";
    unsigned char str2[]="shiraz";
    unsigned char set[]="abc";
    unsigned char empty[]="";
    unsigned char mbstr[]=" 2019\x94\x4e" "6\x8c\x8e" "29\x93\xfa";
    unsigned char mbset1[]="0123456789 \x94\x4e";
    unsigned char mbset2[]=" \x94\x4e\x8c\x8e";
    unsigned char mbset3[]="\x8e";
    int ret, cp = _getmbcp();

    ret=_mbsspn( str1, set);
    ok( ret==3, "_mbsspn returns %d should be 3\n", ret);
    ret=_mbsspn( str2, set);
    ok( ret==0, "_mbsspn returns %d should be 0\n", ret);
    ret=_mbsspn( str1, empty);
    ok( ret==0, "_mbsspn returns %d should be 0\n", ret);

    _setmbcp( 932);
    ret=_mbsspn( mbstr, mbset1);
    ok( ret==8, "_mbsspn returns %d should be 8\n", ret);
    ret=_mbsspn( mbstr, mbset2);
    ok( ret==1, "_mbsspn returns %d should be 1\n", ret);
    ret=_mbsspn( mbstr+8, mbset1);
    ok( ret==0, "_mbsspn returns %d should be 0\n", ret);
    ret=_mbsspn( mbstr+8, mbset2);
    ok( ret==2, "_mbsspn returns %d should be 2\n", ret);
    ret=_mbsspn( mbstr, mbset3);
    ok( ret==14, "_mbsspn returns %d should be 14\n", ret);

    _setmbcp( cp);
}