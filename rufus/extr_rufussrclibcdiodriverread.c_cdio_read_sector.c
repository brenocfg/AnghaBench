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
typedef  int /*<<< orphan*/  lsn_t ;
typedef  int /*<<< orphan*/  driver_return_code_t ;
typedef  int /*<<< orphan*/  cdio_read_mode_t ;
typedef  int /*<<< orphan*/  CdIo_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_read_sectors (int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

driver_return_code_t
cdio_read_sector(const CdIo_t *p_cdio, void *p_buf, lsn_t i_lsn,
                 cdio_read_mode_t read_mode)
{
  return cdio_read_sectors(p_cdio, p_buf, i_lsn, read_mode, 1);
}