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
typedef  char uint8_t ;
typedef  int uint32_t ;
struct msg {int mlen; int /*<<< orphan*/  mhdr; } ;
struct mbuf {char* pos; char* last; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CRLF_LEN ; 
 int /*<<< orphan*/  LOG_VVERB ; 
 scalar_t__ NC_ERROR ; 
 scalar_t__ NC_OK ; 
 struct mbuf* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct mbuf* STAILQ_NEXT (struct mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ mbuf_empty (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_insert (int /*<<< orphan*/ *,struct mbuf*) ; 
 int mbuf_length (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_put (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_remove (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ msg_append (struct msg*,char*,int) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static rstatus_t
redis_copy_bulk(struct msg *dst, struct msg *src)
{
    struct mbuf *mbuf, *nbuf;
    uint8_t *p;
    uint32_t len = 0;
    uint32_t bytes = 0;
    rstatus_t status;

    for (mbuf = STAILQ_FIRST(&src->mhdr);
         mbuf && mbuf_empty(mbuf);
         mbuf = STAILQ_FIRST(&src->mhdr)) {

        mbuf_remove(&src->mhdr, mbuf);
        mbuf_put(mbuf);
    }

    mbuf = STAILQ_FIRST(&src->mhdr);
    if (mbuf == NULL) {
        return NC_ERROR;
    }

    p = mbuf->pos;
    ASSERT(*p == '$');
    p++;

    if (p[0] == '-' && p[1] == '1') {
        len = 1 + 2 + CRLF_LEN;             /* $-1\r\n */
        p = mbuf->pos + len;
    } else {
        len = 0;
        for (; p < mbuf->last && isdigit(*p); p++) {
            len = len * 10 + (uint32_t)(*p - '0');
        }
        len += CRLF_LEN * 2;
        len += (p - mbuf->pos);
    }
    bytes = len;

    /* copy len bytes to dst */
    for (; mbuf;) {
        if (mbuf_length(mbuf) <= len) {     /* steal this buf from src to dst */
            nbuf = STAILQ_NEXT(mbuf, next);
            mbuf_remove(&src->mhdr, mbuf);
            if (dst != NULL) {
                mbuf_insert(&dst->mhdr, mbuf);
            } else {
                mbuf_put(mbuf);
            }
            len -= mbuf_length(mbuf);
            mbuf = nbuf;
        } else {                             /* split it */
            if (dst != NULL) {
                status = msg_append(dst, mbuf->pos, len);
                if (status != NC_OK) {
                    return status;
                }
            }
            mbuf->pos += len;
            break;
        }
    }

    if (dst != NULL) {
        dst->mlen += bytes;
    }
    src->mlen -= bytes;
    log_debug(LOG_VVERB, "redis_copy_bulk copy bytes: %d", bytes);
    return NC_OK;
}