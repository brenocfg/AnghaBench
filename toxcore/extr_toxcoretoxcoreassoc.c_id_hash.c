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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int hash_t ;
struct TYPE_3__ {int candidates_bucket_size; } ;
typedef  TYPE_1__ Assoc ;

/* Variables and functions */
 int crypto_box_PUBLICKEYBYTES ; 

__attribute__((used)) static hash_t id_hash(const Assoc *assoc, const uint8_t *id)
{
    uint32_t i, res = 0x19a64e82;

    for (i = 0; i < crypto_box_PUBLICKEYBYTES; i++)
        res = ((res << 1) ^ id[i]) + (res >> 31);

    /* can't have zero as hash, a) marks an unused spot,
     * b) collision function is multiplicative */
    if (!(res % assoc->candidates_bucket_size))
        res++;

    return res;
}