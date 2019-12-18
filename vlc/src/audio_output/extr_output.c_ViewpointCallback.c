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
struct TYPE_4__ {int /*<<< orphan*/ * p_address; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  aout_ChangeViewpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ViewpointCallback (vlc_object_t *obj, const char *var,
                              vlc_value_t prev, vlc_value_t cur, void *data)
{
    if( cur.p_address != NULL )
        aout_ChangeViewpoint((audio_output_t *)obj, cur.p_address );
    (void) var; (void) data; (void) prev;
    return VLC_SUCCESS;
}