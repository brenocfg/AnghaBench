#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int flags; unsigned int tag_len; int rtp_rcc; int /*<<< orphan*/  rtp; int /*<<< orphan*/  rtcp; } ;
typedef  TYPE_1__ srtp_session_t ;

/* Variables and functions */
 int GCRY_CIPHER_AES ; 
 int GCRY_CIPHER_NONE ; 
 int GCRY_MD_NONE ; 
 int GCRY_MD_SHA1 ; 
#define  SRTP_AUTH_HMAC_SHA1 131 
#define  SRTP_AUTH_NULL 130 
#define  SRTP_ENCR_AES_CM 129 
#define  SRTP_ENCR_NULL 128 
 unsigned int SRTP_FLAGS_MASK ; 
 int SRTP_PRF_AES_CM ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 unsigned int gcry_md_get_algo_dlen (int) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ proto_create (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  proto_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ rcc_mode (TYPE_1__*) ; 

srtp_session_t *
srtp_create (int encr, int auth, unsigned tag_len, int prf, unsigned flags)
{
    if ((flags & ~SRTP_FLAGS_MASK))
        return NULL;

    int cipher, md;
    switch (encr)
    {
        case SRTP_ENCR_NULL:
            cipher = GCRY_CIPHER_NONE;
            break;

        case SRTP_ENCR_AES_CM:
            cipher = GCRY_CIPHER_AES;
            break;

        default:
            return NULL;
    }

    switch (auth)
    {
        case SRTP_AUTH_NULL:
            md = GCRY_MD_NONE;
            break;

        case SRTP_AUTH_HMAC_SHA1:
            md = GCRY_MD_SHA1;
            break;

        default:
            return NULL;
    }

    if (tag_len > gcry_md_get_algo_dlen (md))
        return NULL;

    if (prf != SRTP_PRF_AES_CM)
        return NULL;

    srtp_session_t *s = malloc (sizeof (*s));
    if (s == NULL)
        return NULL;

    memset (s, 0, sizeof (*s));
    s->flags = flags;
    s->tag_len = tag_len;
    s->rtp_rcc = 1; /* Default RCC rate */
    if (rcc_mode (s))
    {
        if (tag_len < 4)
            goto error;
    }

    if (proto_create (&s->rtp, cipher, md) == 0)
    {
        if (proto_create (&s->rtcp, cipher, md) == 0)
            return s;
        proto_destroy (&s->rtp);
    }

error:
    free (s);
    return NULL;
}