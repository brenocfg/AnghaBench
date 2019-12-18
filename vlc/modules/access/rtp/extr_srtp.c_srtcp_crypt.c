#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int window; int /*<<< orphan*/  salt; } ;
struct TYPE_5__ {int window; int /*<<< orphan*/  cipher; } ;
struct TYPE_7__ {int flags; int rtcp_index; TYPE_2__ rtp; TYPE_1__ rtcp; } ;
typedef  TYPE_3__ srtp_session_t ;
typedef  int int32_t ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int SRTCP_UNENCRYPTED ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int ntohl (int) ; 
 scalar_t__ rtcp_crypt (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*,size_t) ; 

__attribute__((used)) static int srtcp_crypt (srtp_session_t *s, uint8_t *buf, size_t len)
{
    assert (s != NULL);

    /* 8-bytes unencrypted header, and 4-bytes unencrypted footer */
    if ((len < 12) || ((buf[0] >> 6) != 2))
        return EINVAL;

    uint32_t index;
    memcpy (&index, buf + len, 4);
    index = ntohl (index);
    if (((index >> 31) != 0) != ((s->flags & SRTCP_UNENCRYPTED) == 0))
        return EINVAL; // E-bit mismatch

    index &= ~(1 << 31); // clear E-bit for counter

    /* Updates SRTCP index (safe here) */
    int32_t diff = index - s->rtcp_index;
    if (diff > 0)
    {
        /* Packet in the future, good */
        s->rtcp.window = s->rtcp.window << diff;
        s->rtcp.window |= UINT64_C(1);
        s->rtcp_index = index;
    }
    else
    {
        /* Packet in the past/present, bad */
        diff = -diff;
        if ((diff >= 64) || ((s->rtcp.window >> diff) & 1))
            return EACCES; // replay attack!
        s->rtp.window |= UINT64_C(1) << diff;
    }

    /* Crypts SRTCP */
    if (s->flags & SRTCP_UNENCRYPTED)
        return 0;

    uint32_t ssrc;
    memcpy (&ssrc, buf + 4, 4);

    if (rtcp_crypt (s->rtcp.cipher, ssrc, index, s->rtp.salt,
                    buf + 8, len - 8))
        return EINVAL;
    return 0;
}