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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int SUBPICTURE_ALIGN_RIGHT ; 
 int SUBPICTURE_ALIGN_TOP ; 
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_OSDText (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,char*) ; 

void vout_OSDMessageVa(vout_thread_t *vout, int channel,
                       const char *format, va_list args)
{
    char *string;
    if (vasprintf(&string, format, args) != -1) {
        vout_OSDText(vout, channel,
                     SUBPICTURE_ALIGN_TOP|SUBPICTURE_ALIGN_RIGHT, VLC_TICK_FROM_SEC(1),
                     string);
        free(string);
    }
}