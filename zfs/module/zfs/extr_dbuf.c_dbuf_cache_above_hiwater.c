#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t DB_DBUF_CACHE ; 
 scalar_t__ dbuf_cache_hiwater_bytes () ; 
 TYPE_1__* dbuf_caches ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline boolean_t
dbuf_cache_above_hiwater(void)
{
	return (zfs_refcount_count(&dbuf_caches[DB_DBUF_CACHE].size) >
	    dbuf_cache_hiwater_bytes());
}