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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  srtp_session_t ;
typedef  int /*<<< orphan*/  bsalt ;
typedef  int /*<<< orphan*/  bkey ;

/* Variables and functions */
 int EINVAL ; 
 int hexstring (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ srtp_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

int
srtp_setkeystring (srtp_session_t *s, const char *key, const char *salt)
{
    uint8_t bkey[16]; /* TODO/NOTE: hard-coded for AES */
    uint8_t bsalt[14]; /* TODO/NOTE: hard-coded for the PRF-AES-CM */
    ssize_t bkeylen = hexstring (key, bkey, sizeof (bkey));
    ssize_t bsaltlen = hexstring (salt, bsalt, sizeof (bsalt));

    if ((bkeylen == -1) || (bsaltlen == -1))
        return EINVAL;
    return srtp_setkey (s, bkey, bkeylen, bsalt, bsaltlen) ? EINVAL : 0;
}