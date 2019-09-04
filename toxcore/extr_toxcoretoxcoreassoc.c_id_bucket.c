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
typedef  int uint8_t ;
typedef  int bucket_t ;

/* Variables and functions */

__attribute__((used)) static bucket_t id_bucket(const uint8_t *id, uint8_t bits)
{
    /* return the first "bits" bits of id */
    bucket_t retval = 0;

    uint8_t pos = 0;

    while (bits > 8) {
        retval = (retval << 8) | id[pos++];
        bits -= 8;
    }

    return (retval << bits) | (id[pos] >> (8 - bits));
}