#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_channel; } ;
struct TYPE_5__ {TYPE_2__ cc; } ;
struct TYPE_7__ {scalar_t__ i_codec; TYPE_1__ subs; } ;
typedef  TYPE_3__ es_format_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_CEA608 ; 
 scalar_t__ VLC_CODEC_CEA708 ; 

__attribute__((used)) static inline int EsOutGetClosedCaptionsChannel( const es_format_t *p_fmt )
{
    int i_channel;
    if( p_fmt->i_codec == VLC_CODEC_CEA608 && p_fmt->subs.cc.i_channel < 4 )
        i_channel = p_fmt->subs.cc.i_channel;
    else if( p_fmt->i_codec == VLC_CODEC_CEA708 && p_fmt->subs.cc.i_channel < 64 )
        i_channel = p_fmt->subs.cc.i_channel;
    else
        i_channel = -1;
    return i_channel;
}