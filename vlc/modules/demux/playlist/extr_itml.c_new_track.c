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
struct TYPE_5__ {scalar_t__ duration; int /*<<< orphan*/ * location; int /*<<< orphan*/ * trackNum; int /*<<< orphan*/ * genre; int /*<<< orphan*/ * album; int /*<<< orphan*/ * artist; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ track_elem_t ;

/* Variables and functions */
 scalar_t__ likely (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static track_elem_t *new_track()
{
    track_elem_t *p_track = malloc( sizeof *p_track );
    if( likely( p_track ) )
    {
        p_track->name = NULL;
        p_track->artist = NULL;
        p_track->album = NULL;
        p_track->genre = NULL;
        p_track->trackNum = NULL;
        p_track->location = NULL;
        p_track->duration = 0;
    }
    return p_track;
}