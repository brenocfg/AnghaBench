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
struct TYPE_2__ {scalar_t__ i_start; } ;
typedef  TYPE_1__ webvtt_dom_tag_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static int timedtagsArrayCmp( const void *a, const void *b )
{
    const webvtt_dom_tag_t *ta = *((const webvtt_dom_tag_t **) a);
    const webvtt_dom_tag_t *tb = *((const webvtt_dom_tag_t **) b);
    const int64_t result = ta->i_start - tb->i_start;
    return result == 0 ? 0 : result > 0 ? 1 : -1;
}