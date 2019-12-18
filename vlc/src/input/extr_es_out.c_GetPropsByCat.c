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
struct TYPE_3__ {int /*<<< orphan*/  video; int /*<<< orphan*/  sub; int /*<<< orphan*/  audio; } ;
typedef  TYPE_1__ es_out_sys_t ;
typedef  int /*<<< orphan*/  es_out_es_props_t ;

/* Variables and functions */
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 

__attribute__((used)) static es_out_es_props_t * GetPropsByCat( es_out_sys_t *p_sys, int i_cat )
{
    switch( i_cat )
    {
    case AUDIO_ES:
        return &p_sys->audio;
    case SPU_ES:
        return &p_sys->sub;
    case VIDEO_ES:
        return &p_sys->video;
    }
    return NULL;
}