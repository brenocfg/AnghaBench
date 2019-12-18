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
typedef  unsigned int lba_t ;

/* Variables and functions */
 unsigned int CDIO_CD_FRAMES_PER_SEC ; 
 unsigned int CDIO_CD_SECS_PER_MIN ; 

lba_t
cdio_msf3_to_lba (unsigned int minutes, unsigned int seconds,
                  unsigned int frames)
{
  return ((minutes * CDIO_CD_SECS_PER_MIN + seconds) * CDIO_CD_FRAMES_PER_SEC
	  + frames);
}