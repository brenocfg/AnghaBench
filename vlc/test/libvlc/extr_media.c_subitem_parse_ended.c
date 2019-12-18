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
typedef  int /*<<< orphan*/  vlc_sem_t ;
typedef  int /*<<< orphan*/  libvlc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void subitem_parse_ended(const libvlc_event_t *event, void *user_data)
{
    (void)event;
    vlc_sem_t *sem = user_data;
    vlc_sem_post (sem);
}