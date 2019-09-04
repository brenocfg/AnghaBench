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
typedef  int (* descrypt ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*) ;

/* Variables and functions */
 int STATUS_SUCCESS ; 
 int STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/ * des_ciphertext ; 
 int /*<<< orphan*/ * des_key ; 
 int /*<<< orphan*/  des_plaintext ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*,int) ; 

__attribute__((used)) static void test_SystemFunction_decrypt(descrypt func, int num)
{
    unsigned char output[0x11];
    int r;

    if (!func)
    {
        win_skip("SystemFunction%03d is not available\n", num);
        return;
    }

    r = func(NULL, NULL, NULL);
    ok( r == STATUS_UNSUCCESSFUL, "wrong error code\n");

    memset(output, 0, sizeof output);

    r = func(des_ciphertext, des_key, output);
    ok( r == STATUS_SUCCESS, "wrong error code\n");
    ok( !memcmp(des_plaintext, output, sizeof des_plaintext), "plaintext wrong (%d)\n", num);
}