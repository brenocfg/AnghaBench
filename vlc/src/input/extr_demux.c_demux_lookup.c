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
typedef  int /*<<< orphan*/  demux_mapping ;

/* Variables and functions */
 int /*<<< orphan*/ * bsearch (char const*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demux_mapping_cmp ; 

__attribute__((used)) static demux_mapping* demux_lookup( char const* key,
                                    demux_mapping* data, size_t size )
{
    return bsearch( key, data, size, sizeof( *data ), demux_mapping_cmp );
}