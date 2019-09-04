#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16 ;
struct TYPE_4__ {int /*<<< orphan*/ ** cursorcache; } ;
struct TYPE_5__ {TYPE_1__ cache; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/ * HCURSOR ;

/* Variables and functions */
 size_t NUM_ELEMENTS (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  error (char*,size_t) ; 

HCURSOR
cache_get_cursor(RDPCLIENT * This, uint16 cache_idx)
{
	HCURSOR cursor;

	if (cache_idx < NUM_ELEMENTS(This->cache.cursorcache))
	{
		cursor = This->cache.cursorcache[cache_idx];
		if (cursor != NULL)
			return cursor;
	}

	error("get cursor %d\n", cache_idx);
	return NULL;
}