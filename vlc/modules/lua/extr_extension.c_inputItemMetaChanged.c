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
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ vlc_event_t ;
typedef  int /*<<< orphan*/  extension_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_UPDATE_META ; 
 int /*<<< orphan*/  PushCommandUnique (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_InputItemMetaChanged ; 

__attribute__((used)) static void inputItemMetaChanged( const vlc_event_t *p_event,
                                  void *data )
{
    assert( p_event && p_event->type == vlc_InputItemMetaChanged );

    extension_t *p_ext = ( extension_t* ) data;
    assert( p_ext != NULL );

    PushCommandUnique( p_ext, CMD_UPDATE_META );
}