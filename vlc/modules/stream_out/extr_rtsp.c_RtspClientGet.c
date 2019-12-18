#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {int sessionc; TYPE_2__** sessionv; } ;
typedef  TYPE_1__ rtsp_stream_t ;
struct TYPE_6__ {scalar_t__ id; } ;
typedef  TYPE_2__ rtsp_session_t ;

/* Variables and functions */
 scalar_t__ errno ; 
 scalar_t__ strtoull (char const*,char**,int) ; 

__attribute__((used)) static
rtsp_session_t *RtspClientGet( rtsp_stream_t *rtsp, const char *name )
{
    char *end;
    uint64_t id;
    int i;

    if( name == NULL )
        return NULL;

    errno = 0;
    id = strtoull( name, &end, 0x10 );
    if( errno || *end )
        return NULL;

    /* FIXME: use a hash/dictionary */
    for( i = 0; i < rtsp->sessionc; i++ )
    {
        if( rtsp->sessionv[i]->id == id )
            return rtsp->sessionv[i];
    }
    return NULL;
}