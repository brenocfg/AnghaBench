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
struct TYPE_3__ {int /*<<< orphan*/  track_id; } ;
typedef  TYPE_1__ rtsp_stream_id_t ;

/* Variables and functions */
 int asprintf (char**,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

char *RtspAppendTrackPath( rtsp_stream_id_t *id, const char *base )
{
    const char *sep = strlen( base ) > 0 && base[strlen( base ) - 1] == '/' ?
                      "" : "/";
    char *url;

    if( asprintf( &url, "%s%strackID=%u", base, sep, id->track_id ) == -1 )
        url = NULL;
    return url;
}