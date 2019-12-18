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
typedef  int /*<<< orphan*/ * remap_fun_t ;
struct TYPE_3__ {int i_format; } ;
typedef  TYPE_1__ audio_format_t ;

/* Variables and functions */
 int /*<<< orphan*/ * RemapAddFL32 ; 
 int /*<<< orphan*/ * RemapAddFL64 ; 
 int /*<<< orphan*/ * RemapAddS16N ; 
 int /*<<< orphan*/ * RemapAddS32N ; 
 int /*<<< orphan*/ * RemapAddU8 ; 
 int /*<<< orphan*/ * RemapCopyFL32 ; 
 int /*<<< orphan*/ * RemapCopyFL64 ; 
 int /*<<< orphan*/ * RemapCopyS16N ; 
 int /*<<< orphan*/ * RemapCopyS32N ; 
 int /*<<< orphan*/ * RemapCopyU8 ; 
#define  VLC_CODEC_FL32 132 
#define  VLC_CODEC_FL64 131 
#define  VLC_CODEC_S16N 130 
#define  VLC_CODEC_S32N 129 
#define  VLC_CODEC_U8 128 

__attribute__((used)) static inline remap_fun_t GetRemapFun( audio_format_t *p_format, bool b_add )
{
    if( b_add )
    {
        switch( p_format->i_format )
        {
            case VLC_CODEC_U8:
                return RemapAddU8;
            case VLC_CODEC_S16N:
                return RemapAddS16N;
            case VLC_CODEC_S32N:
                return RemapAddS32N;
            case VLC_CODEC_FL32:
                return RemapAddFL32;
            case VLC_CODEC_FL64:
                return RemapAddFL64;
        }
    }
    else
    {
        switch( p_format->i_format )
        {
            case VLC_CODEC_U8:
                return RemapCopyU8;
            case VLC_CODEC_S16N:
                return RemapCopyS16N;
            case VLC_CODEC_S32N:
                return RemapCopyS32N;
            case VLC_CODEC_FL32:
                return RemapCopyFL32;
            case VLC_CODEC_FL64:
                return RemapCopyFL64;
        }
    }

    return NULL;
}