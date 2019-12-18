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
 int /*<<< orphan*/  cdio_lba_to_lsn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdio_msf_to_lba (int /*<<< orphan*/  const*) ; 

lba_t
cdio_msf_to_lsn (const msf_t *msf)
{
  return cdio_lba_to_lsn(cdio_msf_to_lba (msf));
}