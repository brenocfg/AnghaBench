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
typedef  int /*<<< orphan*/  uint32_t ;
struct msg_tqh {int dummy; } ;
struct msg {int dummy; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_OK ; 
 int /*<<< orphan*/  memcache_fragment_retrieval (struct msg*,int /*<<< orphan*/ ,struct msg_tqh*,int) ; 
 scalar_t__ memcache_retrieval (struct msg*) ; 

rstatus_t
memcache_fragment(struct msg *r, uint32_t ncontinuum, struct msg_tqh *frag_msgq)
{
    if (memcache_retrieval(r)) {
        return memcache_fragment_retrieval(r, ncontinuum, frag_msgq, 1);
    }
    return NC_OK;
}