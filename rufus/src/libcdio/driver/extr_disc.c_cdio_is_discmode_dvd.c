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
typedef  int discmode_t ;

/* Variables and functions */
#define  CDIO_DISC_MODE_DVD_OTHER 134 
#define  CDIO_DISC_MODE_DVD_PR 133 
#define  CDIO_DISC_MODE_DVD_PRW 132 
#define  CDIO_DISC_MODE_DVD_R 131 
#define  CDIO_DISC_MODE_DVD_RAM 130 
#define  CDIO_DISC_MODE_DVD_ROM 129 
#define  CDIO_DISC_MODE_DVD_RW 128 

bool
cdio_is_discmode_dvd(discmode_t discmode) 
{
  switch (discmode) {
    case CDIO_DISC_MODE_DVD_ROM:
    case CDIO_DISC_MODE_DVD_RAM:
    case CDIO_DISC_MODE_DVD_R:
    case CDIO_DISC_MODE_DVD_RW:
    case CDIO_DISC_MODE_DVD_PR:
    case CDIO_DISC_MODE_DVD_PRW:
    case CDIO_DISC_MODE_DVD_OTHER:
      return true;
    default:
      return false;
  }
}