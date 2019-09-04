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
 unsigned char* _mbsspnp (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_mbsspnp( void)
{
    unsigned char str1[]="cabernet";
    unsigned char str2[]="shiraz";
    unsigned char set[]="abc";
    unsigned char empty[]="";
    unsigned char full[]="abcenrt";
    unsigned char* ret;
    ret=_mbsspnp( str1, set);
    ok( ret[0]=='e', "_mbsspnp returns %c should be e\n", ret[0]);
    ret=_mbsspnp( str2, set);
    ok( ret[0]=='s', "_mbsspnp returns %c should be s\n", ret[0]);
    ret=_mbsspnp( str1, empty);
    ok( ret[0]=='c', "_mbsspnp returns %c should be c\n", ret[0]);
    ret=_mbsspnp( str1, full);
    ok( ret==NULL, "_mbsspnp returns %p should be NULL\n", ret);
}