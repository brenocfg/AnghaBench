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
typedef  int /*<<< orphan*/  vlc_dialog_id ;
typedef  int /*<<< orphan*/  libvlc_dialog_id ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int vlc_dialog_id_dismiss (int /*<<< orphan*/ *) ; 

int
libvlc_dialog_dismiss(libvlc_dialog_id *p_id)
{
    int i_ret = vlc_dialog_id_dismiss((vlc_dialog_id *)p_id);
    return i_ret == VLC_SUCCESS ? 0 : -1;
}