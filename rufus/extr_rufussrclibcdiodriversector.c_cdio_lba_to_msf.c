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
typedef  int /*<<< orphan*/  msf_t ;
typedef  int /*<<< orphan*/  lba_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_assert (int) ; 
 int /*<<< orphan*/  cdio_lba_to_lsn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdio_lsn_to_msf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
cdio_lba_to_msf (lba_t lba, msf_t *msf)
{
  cdio_assert (msf != 0);
  cdio_lsn_to_msf(cdio_lba_to_lsn(lba), msf);
}