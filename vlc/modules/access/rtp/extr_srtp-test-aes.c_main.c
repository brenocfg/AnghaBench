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
 int /*<<< orphan*/  GCRYCTL_DISABLE_SECMEM ; 
 int /*<<< orphan*/  gcry_control (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srtp_test () ; 

int main (void)
{
    gcry_control (GCRYCTL_DISABLE_SECMEM, NULL);
    srtp_test ();
    return 0;
}