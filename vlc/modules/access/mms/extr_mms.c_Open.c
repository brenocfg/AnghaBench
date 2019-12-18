#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int MMSHOpen (TYPE_1__*) ; 
 int MMSTUOpen (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    stream_t *p_access = (stream_t*)p_this;

    /* use specified method */
    if( !strncmp( p_access->psz_name, "mmsu", 4 ) )
        return  MMSTUOpen ( p_access );
    else if( !strncmp( p_access->psz_name, "mmst", 4 ) )
        return  MMSTUOpen ( p_access );
    else if( !strncmp( p_access->psz_name, "mmsh", 4 ) )
        return  MMSHOpen ( p_access );

    if( MMSTUOpen ( p_access ) )
    {   /* try mmsh if mmstu failed */
        return  MMSHOpen ( p_access );
    }
    return VLC_SUCCESS;
}