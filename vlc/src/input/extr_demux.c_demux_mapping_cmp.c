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
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ demux_mapping ;

/* Variables and functions */
 int vlc_ascii_strcasecmp (void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int demux_mapping_cmp( const void *k, const void *v )
{
    demux_mapping* entry = v;
    return vlc_ascii_strcasecmp( k, entry->key );
}