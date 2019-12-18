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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  bridge_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * var_GetAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bridge_t *GetBridge( vlc_object_t *p_object )
{
    return var_GetAddress(VLC_OBJECT(vlc_object_instance(p_object)),
                          "mosaic-struct");
}