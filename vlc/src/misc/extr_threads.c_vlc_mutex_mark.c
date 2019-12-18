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
typedef  int /*<<< orphan*/  vlc_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_lock_mark (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_marks ; 

void vlc_mutex_mark(const vlc_mutex_t *mutex)
{
    vlc_lock_mark(mutex, &vlc_mutex_marks);
}