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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int get16bits (char const*) ; 

uint32_t
hash_hsieh(const char *key, size_t key_length)
{
    uint32_t hash = 0, tmp;
    int rem;

    if (key_length <= 0 || key == NULL) {
        return 0;
    }

    rem = key_length & 3;
    key_length >>= 2;

    /* Main loop */
    for (;key_length > 0; key_length--) {
        hash += get16bits (key);
        tmp = (get16bits (key+2) << 11) ^ hash;
        hash = (hash << 16) ^ tmp;
        key += 2*sizeof (uint16_t);
        hash += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
    case 3:
        hash += get16bits (key);
        hash ^= hash << 16;
        hash ^= (uint32_t)key[sizeof (uint16_t)] << 18;
        hash += hash >> 11;
        break;

    case 2:
        hash += get16bits (key);
        hash ^= hash << 11;
        hash += hash >> 17;
        break;

    case 1:
        hash += (unsigned char)(*key);
        hash ^= hash << 10;
        hash += hash >> 1;

    default:
        break;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}