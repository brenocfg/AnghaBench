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
typedef  int uint8_t ;
struct ahci_port {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ATA_I_CMD ; 
 int ATA_I_IN ; 
 int ATA_S_DSC ; 
 int ATA_S_READY ; 
 int /*<<< orphan*/  ahci_write_fis_d2h (struct ahci_port*,int,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_prdt (struct ahci_port*,int,int*,int*,int) ; 

__attribute__((used)) static void
atapi_report_luns(struct ahci_port *p, int slot, uint8_t *cfis)
{
	uint8_t buf[16];

	memset(buf, 0, sizeof(buf));
	buf[3] = 8;

	cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
	write_prdt(p, slot, cfis, buf, sizeof(buf));
	ahci_write_fis_d2h(p, slot, cfis, ATA_S_READY | ATA_S_DSC);
}