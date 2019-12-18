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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_medialibrary_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_media_library; } ;
typedef  TYPE_1__ libvlc_priv_t ;

/* Variables and functions */
 TYPE_1__* libvlc_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

vlc_medialibrary_t* vlc_ml_instance_get( vlc_object_t* p_obj )
{
    libvlc_priv_t* p_priv = libvlc_priv( vlc_object_instance(p_obj) );
    return p_priv->p_media_library;
}