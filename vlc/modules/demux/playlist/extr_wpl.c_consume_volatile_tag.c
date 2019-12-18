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
struct TYPE_3__ {int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int consume_tag (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ likely (char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int consume_volatile_tag( stream_t* p_demux, char const* psz_tag )
{
    char* psz_copy = strdup( psz_tag );
    int ret = VLC_ENOMEM;

    if( likely( psz_copy ) )
        ret = consume_tag( p_demux->p_sys, psz_copy );

    free( psz_copy );
    return ret;
}