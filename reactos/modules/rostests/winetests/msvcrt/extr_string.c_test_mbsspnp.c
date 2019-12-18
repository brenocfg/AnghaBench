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
 unsigned char* _mbsspnp (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  _setmbcp (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_mbsspnp( void)
{
    unsigned char str1[]="cabernet";
    unsigned char str2[]="shiraz";
    unsigned char set[]="abc";
    unsigned char empty[]="";
    unsigned char full[]="abcenrt";
    unsigned char mbstr[]=" 2019\x94\x4e" "6\x8c\x8e" "29\x93\xfa";
    unsigned char mbset1[]="0123456789 \x94\x4e";
    unsigned char mbset2[]=" \x94\x4e\x8c\x8e";
    unsigned char* ret;
    int cp = _getmbcp();

    ret=_mbsspnp( str1, set);
    ok( ret[0]=='e', "_mbsspnp returns %c should be e\n", ret[0]);
    ret=_mbsspnp( str2, set);
    ok( ret[0]=='s', "_mbsspnp returns %c should be s\n", ret[0]);
    ret=_mbsspnp( str1, empty);
    ok( ret[0]=='c', "_mbsspnp returns %c should be c\n", ret[0]);
    ret=_mbsspnp( str1, full);
    ok( ret==NULL, "_mbsspnp returns %p should be NULL\n", ret);

    _setmbcp( 932);
    ret=_mbsspnp( mbstr, mbset1);
    ok( ret==mbstr+8, "_mbsspnp returns %p should be %p\n", ret, mbstr+8);
    ret=_mbsspnp( mbstr, mbset2);
    ok( ret==mbstr+1, "_mbsspnp returns %p should be %p\n", ret, mbstr+1);
    ret=_mbsspnp( mbstr+8, mbset1);
    ok( ret==mbstr+8, "_mbsspnp returns %p should be %p\n", ret, mbstr+8);
    ret=_mbsspnp( mbstr+8, mbset2);
    ok( ret==mbstr+10, "_mbsspnp returns %p should be %p\n", ret, mbstr+10);

    _setmbcp( cp);
}