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
typedef  scalar_t__ uint32_t ;
struct msg {int /*<<< orphan*/  mlen; int /*<<< orphan*/  keys; } ;
struct mbuf {scalar_t__ last; } ;
struct keypos {scalar_t__ end; scalar_t__ start; } ;
typedef  int /*<<< orphan*/  rstatus_t ;
typedef  int /*<<< orphan*/  printbuf ;

/* Variables and functions */
 scalar_t__ CRLF ; 
 scalar_t__ CRLF_LEN ; 
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 struct keypos* array_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_copy (struct mbuf*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct mbuf* msg_ensure_mbuf (struct msg*,scalar_t__) ; 
 scalar_t__ nc_snprintf (int /*<<< orphan*/ *,int,char*,scalar_t__) ; 

__attribute__((used)) static rstatus_t
redis_append_key(struct msg *r, uint8_t *key, uint32_t keylen)
{
    uint32_t len;
    struct mbuf *mbuf;
    uint8_t printbuf[32];
    struct keypos *kpos;

    /* 1. keylen */
    len = (uint32_t)nc_snprintf(printbuf, sizeof(printbuf), "$%d\r\n", keylen);
    mbuf = msg_ensure_mbuf(r, len);
    if (mbuf == NULL) {
        return NC_ENOMEM;
    }
    mbuf_copy(mbuf, printbuf, len);
    r->mlen += len;

    /* 2. key */
    mbuf = msg_ensure_mbuf(r, keylen);
    if (mbuf == NULL) {
        return NC_ENOMEM;
    }

    kpos = array_push(r->keys);
    if (kpos == NULL) {
        return NC_ENOMEM;
    }

    kpos->start = mbuf->last;
    kpos->end = mbuf->last + keylen;
    mbuf_copy(mbuf, key, keylen);
    r->mlen += keylen;

    /* 3. CRLF */
    mbuf = msg_ensure_mbuf(r, CRLF_LEN);
    if (mbuf == NULL) {
        return NC_ENOMEM;
    }
    mbuf_copy(mbuf, (uint8_t *)CRLF, CRLF_LEN);
    r->mlen += (uint32_t)CRLF_LEN;

    return NC_OK;
}