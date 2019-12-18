#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sessionv; int /*<<< orphan*/  sessionc; } ;
typedef  TYPE_1__ rtsp_stream_t ;
struct TYPE_8__ {int /*<<< orphan*/ * trackv; scalar_t__ trackc; int /*<<< orphan*/  id; TYPE_1__* stream; } ;
typedef  TYPE_2__ rtsp_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  vlc_rand_bytes (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
rtsp_session_t *RtspClientNew( rtsp_stream_t *rtsp )
{
    rtsp_session_t *s = malloc( sizeof( *s ) );
    if( s == NULL )
        return NULL;

    s->stream = rtsp;
    vlc_rand_bytes (&s->id, sizeof (s->id));
    s->trackc = 0;
    s->trackv = NULL;

    TAB_APPEND( rtsp->sessionc, rtsp->sessionv, s );

    return s;
}