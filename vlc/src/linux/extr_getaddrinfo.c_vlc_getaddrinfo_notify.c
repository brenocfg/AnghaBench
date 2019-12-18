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
union sigval {int /*<<< orphan*/  sival_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_getaddrinfo_notify(union sigval val)
{
    vlc_sem_post(val.sival_ptr);
}