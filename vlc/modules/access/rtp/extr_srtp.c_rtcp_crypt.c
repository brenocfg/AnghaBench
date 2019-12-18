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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  gcry_cipher_hd_t ;

/* Variables and functions */
 int rtp_crypt (int /*<<< orphan*/ ,int,int,int,int const*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
rtcp_crypt (gcry_cipher_hd_t hd, uint32_t ssrc, uint32_t index,
            const uint32_t *salt, uint8_t *data, size_t len)
{
    return rtp_crypt (hd, ssrc, index >> 16, index & 0xffff, salt, data, len);
}