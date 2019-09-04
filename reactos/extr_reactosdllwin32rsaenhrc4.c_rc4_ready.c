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
struct TYPE_4__ {unsigned char* buf; int x; int /*<<< orphan*/  y; } ;
struct TYPE_5__ {TYPE_1__ rc4; } ;
typedef  TYPE_2__ prng_state ;

/* Variables and functions */
 int CRYPT_OK ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

int rc4_ready(prng_state *prng)
{
    unsigned char key[256], tmp, *s;
    int keylen, x, y, j;

    /* extract the key */
    s = prng->rc4.buf;
    memcpy(key, s, 256);
    keylen = prng->rc4.x;

    /* make RC4 perm and shuffle */
    for (x = 0; x < 256; x++) {
        s[x] = x;
    }

    for (j = x = y = 0; x < 256; x++) {
        y = (y + prng->rc4.buf[x] + key[j++]) & 255;
        if (j == keylen) {
           j = 0; 
        }
        tmp = s[x]; s[x] = s[y]; s[y] = tmp;
    }
    prng->rc4.x = 0;
    prng->rc4.y = 0;

    return CRYPT_OK;
}