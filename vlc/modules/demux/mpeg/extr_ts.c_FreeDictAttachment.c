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
typedef  int /*<<< orphan*/  input_attachment_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FreeDictAttachment( void *p_value, void *p_obj )
{
    VLC_UNUSED(p_obj);
    vlc_input_attachment_Delete( (input_attachment_t *) p_value );
}