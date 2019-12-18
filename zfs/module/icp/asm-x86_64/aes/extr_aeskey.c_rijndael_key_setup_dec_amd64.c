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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  aes_decrypt_key128 (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_decrypt_key192 (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_decrypt_key256 (unsigned char*,int /*<<< orphan*/ *) ; 

int
rijndael_key_setup_dec_amd64(uint32_t rk[], const uint32_t cipherKey[],
    int keyBits)
{
	switch (keyBits) {
	case 128:
		aes_decrypt_key128((unsigned char *)&cipherKey[0], rk);
		return (10);
	case 192:
		aes_decrypt_key192((unsigned char *)&cipherKey[0], rk);
		return (12);
	case 256:
		aes_decrypt_key256((unsigned char *)&cipherKey[0], rk);
		return (14);
	default: /* should never get here */
		break;
	}

	return (0);
}