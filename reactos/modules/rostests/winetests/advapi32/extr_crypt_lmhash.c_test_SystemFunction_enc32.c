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
typedef  int (* descrypt ) (int /*<<< orphan*/ ,unsigned char*,unsigned char*) ;

/* Variables and functions */
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  des_ciphertext32 ; 
 int /*<<< orphan*/  des_plaintext ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  win_skip (char*,int) ; 

__attribute__((used)) static void test_SystemFunction_enc32(descrypt func, int num)
{
    unsigned char key[4], output[0x11];
    int r;

    if (!func)
    {
        win_skip("SystemFunction%03d is not available\n", num);
        return;
    }

    memset(output, 0, sizeof output);

    /* two keys are generated using 4 bytes, repeated 4 times ... */
    memcpy(key, "foo", 4);

    r = func(des_plaintext, key, output);
    ok( r == STATUS_SUCCESS, "wrong error code (%d)\n", num);

    ok( !memcmp( output, des_ciphertext32, sizeof des_ciphertext32), "ciphertext wrong (%d)\n", num);
}