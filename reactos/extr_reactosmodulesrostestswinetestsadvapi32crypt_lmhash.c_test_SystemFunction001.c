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
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pSystemFunction001 (unsigned char*,unsigned char*,unsigned char*) ; 

__attribute__((used)) static void test_SystemFunction001(void)
{
    unsigned char key[8] = { 0xff, 0x37, 0x50, 0xbc, 0xc2, 0xb2, 0x24, 0 };
    unsigned char data[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
    unsigned char expected[8] = { 0xc3, 0x37, 0xcd, 0x5c, 0xbd, 0x44, 0xfc, 0x97 };
    unsigned char output[16];
    NTSTATUS r;

    r = pSystemFunction001(0,0,0);
    ok( r == STATUS_UNSUCCESSFUL, "wrong error code\n");

    memset(output, 0, sizeof output);

    r = pSystemFunction001(data,key,output);
    ok( r == STATUS_SUCCESS, "wrong error code\n");

    ok(!memcmp(output, expected, sizeof expected), "response wrong\n");
}