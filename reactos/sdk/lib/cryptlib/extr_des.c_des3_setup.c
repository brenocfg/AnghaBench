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
struct TYPE_3__ {int /*<<< orphan*/ * dk; int /*<<< orphan*/ * ek; } ;
typedef  TYPE_1__ des3_key ;

/* Variables and functions */
 int CRYPT_INVALID_KEYSIZE ; 
 int CRYPT_INVALID_ROUNDS ; 
 int CRYPT_OK ; 
 int /*<<< orphan*/  DE1 ; 
 int /*<<< orphan*/  EN0 ; 
 int /*<<< orphan*/  deskey (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int des3_setup(const unsigned char *key, int keylen, int num_rounds, des3_key *des3)
{
    if(num_rounds != 0 && num_rounds != 16) {
        return CRYPT_INVALID_ROUNDS;
    }

    if (keylen != 24) {
        return CRYPT_INVALID_KEYSIZE;
    }

    deskey(key,    EN0, des3->ek[0]);
    deskey(key+8,  DE1, des3->ek[1]);
    deskey(key+16, EN0, des3->ek[2]);

    deskey(key,    DE1, des3->dk[2]);
    deskey(key+8,  EN0, des3->dk[1]);
    deskey(key+16, DE1, des3->dk[0]);

    return CRYPT_OK;
}