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
struct TYPE_3__ {int /*<<< orphan*/  dk; int /*<<< orphan*/  ek; } ;
typedef  TYPE_1__ des_key ;

/* Variables and functions */
 int CRYPT_INVALID_KEYSIZE ; 
 int CRYPT_INVALID_ROUNDS ; 
 int CRYPT_OK ; 
 int /*<<< orphan*/  DE1 ; 
 int /*<<< orphan*/  EN0 ; 
 int /*<<< orphan*/  deskey (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int des_setup(const unsigned char *key, int keylen, int num_rounds, des_key *des)
{
    if (num_rounds != 0 && num_rounds != 16) {
        return CRYPT_INVALID_ROUNDS;
    }

    if (keylen != 8) {
        return CRYPT_INVALID_KEYSIZE;
    }

    deskey(key, EN0, des->ek);
    deskey(key, DE1, des->dk);

    return CRYPT_OK;
}