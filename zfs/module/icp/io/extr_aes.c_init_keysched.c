#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ck_format; int ck_length; int /*<<< orphan*/  ck_data; } ;
typedef  TYPE_1__ crypto_key_t ;

/* Variables and functions */
 int AES_MAXBITS ; 
 int AES_MINBITS ; 
#define  CRYPTO_KEY_RAW 128 
 int CRYPTO_KEY_SIZE_RANGE ; 
 int CRYPTO_KEY_TYPE_INCONSISTENT ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  aes_init_keysched (int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static int
init_keysched(crypto_key_t *key, void *newbie)
{
	/*
	 * Only keys by value are supported by this module.
	 */
	switch (key->ck_format) {
	case CRYPTO_KEY_RAW:
		if (key->ck_length < AES_MINBITS ||
		    key->ck_length > AES_MAXBITS) {
			return (CRYPTO_KEY_SIZE_RANGE);
		}

		/* key length must be either 128, 192, or 256 */
		if ((key->ck_length & 63) != 0)
			return (CRYPTO_KEY_SIZE_RANGE);
		break;
	default:
		return (CRYPTO_KEY_TYPE_INCONSISTENT);
	}

	aes_init_keysched(key->ck_data, key->ck_length, newbie);
	return (CRYPTO_SUCCESS);
}