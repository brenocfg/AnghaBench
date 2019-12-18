#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_renderer_item_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  input_thread_events_cb ;
typedef  int /*<<< orphan*/  input_resource_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/ * Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INPUT_CREATE_OPTION_NONE ; 

input_thread_t *input_Create( vlc_object_t *p_parent,
                              input_thread_events_cb events_cb, void *events_data,
                              input_item_t *p_item,
                              input_resource_t *p_resource,
                              vlc_renderer_item_t *p_renderer )
{
    return Create( p_parent, events_cb, events_data, p_item,
                   INPUT_CREATE_OPTION_NONE, p_resource, p_renderer );
}