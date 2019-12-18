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
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  KeepAliveStop (TYPE_1__*) ; 
 int /*<<< orphan*/  MMSClose (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_UrlClean (int /*<<< orphan*/ *) ; 

void MMSTUClose( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;

    KeepAliveStop( p_access );

    /* close connection with server */
    MMSClose( p_access );

    /* free memory */
    vlc_UrlClean( &p_sys->url );

    free( p_sys );
}