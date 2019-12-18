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
 int vlc_lock_marked (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_marks ; 

bool vlc_mutex_marked(const vlc_mutex_t *mutex)
{
    return vlc_lock_marked(mutex, &vlc_mutex_marks);
}