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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  mac; } ;
struct TYPE_6__ {unsigned int tag_len; TYPE_1__ rtcp; } ;
typedef  TYPE_2__ srtp_session_t ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * rtcp_digest (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int srtp_crypt (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 

int
srtcp_recv (srtp_session_t *s, uint8_t *buf, size_t *lenp)
{
    size_t len = *lenp;

    if (len < (4u + s->tag_len))
        return EINVAL;
    len -= s->tag_len;

    const uint8_t *tag = rtcp_digest (s->rtcp.mac, buf, len);
    if (memcmp (buf + len, tag, s->tag_len))
         return EACCES;

    len -= 4; /* Remove SRTCP index before decryption */
    *lenp = len;
    return srtp_crypt (s, buf, len);
}