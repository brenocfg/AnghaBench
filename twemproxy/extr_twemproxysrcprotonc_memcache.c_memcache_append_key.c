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
struct msg {int mlen; int /*<<< orphan*/  keys; } ;
struct mbuf {int last; } ;
struct keypos {int start; int end; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 struct keypos* array_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_copy (struct mbuf*,int /*<<< orphan*/ *,int) ; 
 struct mbuf* msg_ensure_mbuf (struct msg*,int) ; 

__attribute__((used)) static rstatus_t
memcache_append_key(struct msg *r, uint8_t *key, uint32_t keylen)
{
    struct mbuf *mbuf;
    struct keypos *kpos;

    mbuf = msg_ensure_mbuf(r, keylen + 2);
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

    mbuf_copy(mbuf, (uint8_t *)" ", 1);
    r->mlen += 1;
    return NC_OK;
}