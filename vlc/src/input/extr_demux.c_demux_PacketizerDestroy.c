#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ p_description; int /*<<< orphan*/  fmt_out; int /*<<< orphan*/  fmt_in; scalar_t__ p_module; } ;
typedef  TYPE_1__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_meta_Delete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

void demux_PacketizerDestroy( decoder_t *p_packetizer )
{
    if( p_packetizer->p_module )
        module_unneed( p_packetizer, p_packetizer->p_module );
    es_format_Clean( &p_packetizer->fmt_in );
    es_format_Clean( &p_packetizer->fmt_out );
    if( p_packetizer->p_description )
        vlc_meta_Delete( p_packetizer->p_description );
    vlc_object_delete(p_packetizer);
}