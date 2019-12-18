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
typedef  int /*<<< orphan*/  expect ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  pSystemFunction006 (char*,char*) ; 

__attribute__((used)) static void test_SystemFunction006(void)
{
    char lmhash[16 + 1];

    char passwd[] = { 's','e','c','r','e','t', 0, 0, 0, 0, 0, 0, 0, 0 };
    unsigned char expect[] = 
        { 0x85, 0xf5, 0x28, 0x9f, 0x09, 0xdc, 0xa7, 0xeb,
          0xaa, 0xd3, 0xb4, 0x35, 0xb5, 0x14, 0x04, 0xee };

    pSystemFunction006( passwd, lmhash );

    ok( !memcmp( lmhash, expect, sizeof(expect) ),
        "lmhash: %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
        lmhash[0], lmhash[1], lmhash[2], lmhash[3], lmhash[4], lmhash[5],
        lmhash[6], lmhash[7], lmhash[8], lmhash[9], lmhash[10], lmhash[11],
        lmhash[12], lmhash[13], lmhash[14], lmhash[15] );
}