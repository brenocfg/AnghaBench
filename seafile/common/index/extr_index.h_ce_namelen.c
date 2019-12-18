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
struct cache_entry {size_t ce_flags; scalar_t__ name; } ;

/* Variables and functions */
 size_t CE_NAMEMASK ; 
 size_t strlen (scalar_t__) ; 

__attribute__((used)) static inline size_t ce_namelen(const struct cache_entry *ce)
{
    size_t len = ce->ce_flags & CE_NAMEMASK;
    if (len < CE_NAMEMASK)
        return len;
    return strlen(ce->name + CE_NAMEMASK) + CE_NAMEMASK;
}