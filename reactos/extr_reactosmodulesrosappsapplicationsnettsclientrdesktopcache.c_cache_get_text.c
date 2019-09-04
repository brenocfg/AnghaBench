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
typedef  size_t uint8 ;
struct TYPE_4__ {int /*<<< orphan*/ * textcache; } ;
struct TYPE_5__ {TYPE_1__ cache; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  DATABLOB ;

/* Variables and functions */

DATABLOB *
cache_get_text(RDPCLIENT * This, uint8 cache_id)
{
	DATABLOB *text;

	text = &This->cache.textcache[cache_id];
	return text;
}