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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  gcry_cipher_hd_t ;
struct TYPE_3__ {size_t const quot; int rem; } ;
typedef  TYPE_1__ div_t ;

/* Variables and functions */
 TYPE_1__ div (size_t,size_t const) ; 
 scalar_t__ gcry_cipher_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t const,int /*<<< orphan*/ *,size_t const) ; 
 scalar_t__ gcry_cipher_setctr (int /*<<< orphan*/ ,void const*,size_t const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
do_ctr_crypt (gcry_cipher_hd_t hd, const void *ctr, uint8_t *data, size_t len)
{
    const size_t ctrlen = 16;
    div_t d = div (len, ctrlen);

    if (gcry_cipher_setctr (hd, ctr, ctrlen)
     || gcry_cipher_encrypt (hd, data, d.quot * ctrlen, NULL, 0))
        return -1;

    if (d.rem)
    {
        /* Truncated last block */
        uint8_t dummy[ctrlen];
        data += d.quot * ctrlen;
        memcpy (dummy, data, d.rem);
        memset (dummy + d.rem, 0, ctrlen - d.rem);

        if (gcry_cipher_encrypt (hd, dummy, ctrlen, data, ctrlen))
            return -1;
        memcpy (data, dummy, d.rem);
    }

    return 0;
}