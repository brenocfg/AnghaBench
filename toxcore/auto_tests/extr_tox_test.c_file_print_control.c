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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Tox ;
typedef  scalar_t__ TOX_FILE_CONTROL ;

/* Variables and functions */
 scalar_t__ TOX_FILE_CONTROL_RESUME ; 
 int sendf_ok ; 

void file_print_control(Tox *tox, uint32_t friend_number, uint32_t file_number, TOX_FILE_CONTROL control,
                        void *userdata)
{
    if (*((uint32_t *)userdata) != 974536)
        return;

    /* First send file num is 0.*/
    if (file_number == 0 && control == TOX_FILE_CONTROL_RESUME)
        sendf_ok = 1;
}