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
struct TYPE_6__ {TYPE_1__* p_input_item; } ;
typedef  TYPE_2__ libvlc_media_t ;
struct TYPE_5__ {int /*<<< orphan*/  event_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_duration_changed ; 
 int /*<<< orphan*/  input_item_meta_changed ; 
 int /*<<< orphan*/  vlc_InputItemDurationChanged ; 
 int /*<<< orphan*/  vlc_InputItemMetaChanged ; 
 int /*<<< orphan*/  vlc_event_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void install_input_item_observer( libvlc_media_t *p_md )
{
    vlc_event_attach( &p_md->p_input_item->event_manager,
                      vlc_InputItemMetaChanged,
                      input_item_meta_changed,
                      p_md );
    vlc_event_attach( &p_md->p_input_item->event_manager,
                      vlc_InputItemDurationChanged,
                      input_item_duration_changed,
                      p_md );
}