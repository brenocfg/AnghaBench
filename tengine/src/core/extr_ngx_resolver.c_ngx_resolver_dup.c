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
typedef  int /*<<< orphan*/  ngx_resolver_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_memcpy (void*,void*,size_t) ; 
 void* ngx_resolver_alloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void *
ngx_resolver_dup(ngx_resolver_t *r, void *src, size_t size)
{
    void  *dst;

    dst = ngx_resolver_alloc(r, size);

    if (dst == NULL) {
        return dst;
    }

    ngx_memcpy(dst, src, size);

    return dst;
}