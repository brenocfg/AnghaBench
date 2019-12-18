#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* psz_filepath; char const* psz_url; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */

__attribute__((used)) static const char *StreamLocation( const stream_t *s )
{
    return s->psz_filepath ? s->psz_filepath : s->psz_url;
}