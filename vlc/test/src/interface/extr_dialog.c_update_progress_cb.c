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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,float,char const*) ; 

__attribute__((used)) static void update_progress_cb(void *p_data, vlc_dialog_id *p_id, float f_position,
                               const char *psz_text)
{
    (void) p_id;
    (void) p_data;
    printf("update_progress: %f, text: %s\n", f_position, psz_text);
}