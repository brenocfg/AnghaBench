#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long x; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {TYPE_1__ rc4; } ;
typedef  TYPE_2__ prng_state ;

/* Variables and functions */
 int CRYPT_OK ; 

int rc4_add_entropy(const unsigned char *buf, unsigned long len, prng_state *prng)
{
    /* trim as required */
    if (prng->rc4.x + len > 256) {
       if (prng->rc4.x == 256) {
          /* I can't possibly accept another byte, ok maybe a mint wafer... */
          return CRYPT_OK;
       } else {
          /* only accept part of it */
          len = 256 - prng->rc4.x;
       }       
    }

    while (len--) {
       prng->rc4.buf[prng->rc4.x++] = *buf++;
    }

    return CRYPT_OK;
}