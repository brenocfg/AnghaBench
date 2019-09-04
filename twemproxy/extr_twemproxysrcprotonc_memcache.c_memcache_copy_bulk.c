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
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CRLF_LEN ; 
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 struct mbuf* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct mbuf* STAILQ_NEXT (struct mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mbuf_copy (struct mbuf*,char*,int) ; 
 scalar_t__ mbuf_empty (struct mbuf*) ; 
 struct mbuf* mbuf_get () ; 
 int /*<<< orphan*/  mbuf_insert (int /*<<< orphan*/ *,struct mbuf*) ; 
 int mbuf_length (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_put (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_remove (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static rstatus_t
memcache_copy_bulk(struct msg *dst, struct msg *src)
{
    struct mbuf *mbuf, *nbuf;
    uint8_t *p;
    uint32_t len = 0;
    uint32_t bytes = 0;
    uint32_t i = 0;

    for (mbuf = STAILQ_FIRST(&src->mhdr);
         mbuf && mbuf_empty(mbuf);
         mbuf = STAILQ_FIRST(&src->mhdr)) {

        mbuf_remove(&src->mhdr, mbuf);
        mbuf_put(mbuf);
    }

    mbuf = STAILQ_FIRST(&src->mhdr);
    if (mbuf == NULL) {
        return NC_OK;           /* key not exists */
    }
    p = mbuf->pos;

    /*
     * get : VALUE key 0 len\r\nval\r\n
     * gets: VALUE key 0 len cas\r\nval\r\n
     */
    ASSERT(*p == 'V');
    for (i = 0; i < 3; i++) {                 /*  eat 'VALUE key 0 '  */
        for (; *p != ' ';) {
            p++;
        }
        p++;
    }

    len = 0;
    for (; p < mbuf->last && isdigit(*p); p++) {
        len = len * 10 + (uint32_t)(*p - '0');
    }

    for (; p < mbuf->last && ('\r' != *p); p++) { /* eat cas for gets */
        ;
    }

    len += CRLF_LEN * 2;
    len += (p - mbuf->pos);

    bytes = len;

    /* copy len bytes to dst */
    for (; mbuf;) {
        if (mbuf_length(mbuf) <= len) {   /* steal this mbuf from src to dst */
            nbuf = STAILQ_NEXT(mbuf, next);
            mbuf_remove(&src->mhdr, mbuf);
            mbuf_insert(&dst->mhdr, mbuf);
            len -= mbuf_length(mbuf);
            mbuf = nbuf;
        } else {                        /* split it */
            nbuf = mbuf_get();
            if (nbuf == NULL) {
                return NC_ENOMEM;
            }
            mbuf_copy(nbuf, mbuf->pos, len);
            mbuf_insert(&dst->mhdr, nbuf);
            mbuf->pos += len;
            break;
        }
    }

    dst->mlen += bytes;
    src->mlen -= bytes;
    log_debug(LOG_VVERB, "memcache_copy_bulk copy bytes: %d", bytes);
    return NC_OK;
}