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
struct TYPE_5__ {int b_xds; int i_class; int b_future; int b_meta_changed; int /*<<< orphan*/  meta; TYPE_1__** pkt; scalar_t__ i_type; } ;
typedef  TYPE_2__ xds_t ;
struct TYPE_4__ {int b_started; } ;

/* Variables and functions */
 int XDS_MAX_CLASS_COUNT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void XdsInit( xds_t *h )
{
    h->b_xds = false;
    h->i_class = XDS_MAX_CLASS_COUNT;
    h->i_type = 0;
    h->b_future = false;
    for( int i = 0; i < XDS_MAX_CLASS_COUNT; i++ )
    {
        for( int j = 0; j < 128; j++ )
            h->pkt[i][j].b_started = false;
    }
    h->b_meta_changed = false;
    memset( &h->meta, 0, sizeof(h->meta) );
}