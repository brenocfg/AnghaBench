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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  spu_t ;

/* Variables and functions */
 int /*<<< orphan*/  spu_RegisterChannelInternal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ssize_t spu_RegisterChannel(spu_t *spu)
{
    /* Public call, order is always primary (used for OSD or dvd/bluray spus) */
    return spu_RegisterChannelInternal(spu, NULL, NULL);
}