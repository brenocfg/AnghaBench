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
#define  CDIO_DISC_MODE_CD_DA 132 
#define  CDIO_DISC_MODE_CD_DATA 131 
#define  CDIO_DISC_MODE_CD_MIXED 130 
#define  CDIO_DISC_MODE_CD_XA 129 
#define  CDIO_DISC_MODE_NO_INFO 128 

bool
cdio_is_discmode_cdrom(discmode_t discmode) 
{
  switch (discmode) {
  case CDIO_DISC_MODE_CD_DA:
  case CDIO_DISC_MODE_CD_DATA:
  case CDIO_DISC_MODE_CD_XA:
  case CDIO_DISC_MODE_CD_MIXED:
  case CDIO_DISC_MODE_NO_INFO:
    return true;
  default:
    return false;
  }
}