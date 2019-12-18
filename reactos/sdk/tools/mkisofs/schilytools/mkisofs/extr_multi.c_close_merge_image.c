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

/* Variables and functions */
 int fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_image ; 
 int scsidev_close () ; 

int
close_merge_image()
{
#ifdef	USE_SCG
	return (scsidev_close());
#else
	return (fclose(in_image));
#endif
}