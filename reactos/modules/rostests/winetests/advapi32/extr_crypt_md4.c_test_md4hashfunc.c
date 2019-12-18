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
typedef  int (* md4hashfunc ) (int /*<<< orphan*/ ,unsigned char*,unsigned char*) ;

/* Variables and functions */
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_md4hashfunc(md4hashfunc func)
{
    unsigned char expected[0x10] = {
        0x48, 0x7c, 0x3f, 0x5e, 0x2b, 0x0d, 0x6a, 0x79,
        0x32, 0x4e, 0xcd, 0xbe, 0x9c, 0x15, 0x16, 0x6f };
    unsigned char in[0x10], output[0x10];
    int r;

    memset(in, 0, sizeof in);
    memset(output, 0, sizeof output);
    r = func(0, in, output);
    ok( r == STATUS_SUCCESS, "wrong error code\n");
    ok( !memcmp(expected, output, sizeof output), "output wrong\n");
}