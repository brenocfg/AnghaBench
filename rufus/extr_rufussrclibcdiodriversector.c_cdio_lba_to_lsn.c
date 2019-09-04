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
typedef  scalar_t__ lba_t ;

/* Variables and functions */
 scalar_t__ CDIO_INVALID_LBA ; 
 scalar_t__ CDIO_INVALID_LSN ; 
 scalar_t__ CDIO_PREGAP_SECTORS ; 

lba_t
cdio_lba_to_lsn (lba_t lba)
{
  if (CDIO_INVALID_LBA     == lba) return CDIO_INVALID_LSN;
  return lba - CDIO_PREGAP_SECTORS;
}