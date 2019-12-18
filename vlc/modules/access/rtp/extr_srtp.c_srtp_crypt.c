#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int window; int /*<<< orphan*/  salt; int /*<<< orphan*/  cipher; } ;
struct TYPE_6__ {int rtp_seq; int rtp_roc; int flags; TYPE_1__ rtp; } ;
typedef  TYPE_2__ srtp_session_t ;
typedef  int int16_t ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int SRTP_UNENCRYPTED ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int htons (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ rtp_crypt (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,size_t) ; 
 int rtp_seq (int*) ; 
 int srtp_compute_roc (TYPE_2__*,int) ; 

__attribute__((used)) static int srtp_crypt (srtp_session_t *s, uint8_t *buf, size_t len)
{
    assert (s != NULL);
    assert (len >= 12u);

    if ((buf[0] >> 6) != 2)
        return EINVAL;

    /* Computes encryption offset */
    uint16_t offset = 12;
    offset += (buf[0] & 0xf) * 4; // skips CSRC

    if (buf[0] & 0x10)
    {
        uint16_t extlen;

        offset += 4;
        if (len < offset)
            return EINVAL;

        memcpy (&extlen, buf + offset - 2, 2);
        offset += htons (extlen); // skips RTP extension header
    }

    if (len < offset)
        return EINVAL;

    /* Determines RTP 48-bits counter and SSRC */
    uint16_t seq = rtp_seq (buf);
    uint32_t roc = srtp_compute_roc (s, seq), ssrc;
    memcpy (&ssrc, buf + 8, 4);

    /* Updates ROC and sequence (it's safe now) */
    int16_t diff = seq - s->rtp_seq;
    if (diff > 0)
    {
        /* Sequence in the future, good */
        s->rtp.window = s->rtp.window << diff;
        s->rtp.window |= UINT64_C(1);
        s->rtp_seq = seq, s->rtp_roc = roc;
    }
    else
    {
        /* Sequence in the past/present, bad */
        diff = -diff;
        if ((diff >= 64) || ((s->rtp.window >> diff) & 1))
            return EACCES; /* Replay attack */
        s->rtp.window |= UINT64_C(1) << diff;
    }

    /* Encrypt/Decrypt */
    if (s->flags & SRTP_UNENCRYPTED)
        return 0;

    if (rtp_crypt (s->rtp.cipher, ssrc, roc, seq, s->rtp.salt,
                   buf + offset, len - offset))
        return EINVAL;

    return 0;
}