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
typedef  int uint32_t ;
struct ahci_port {int sense_key; int asc; } ;

/* Variables and functions */
 int ATA_I_CMD ; 
 int ATA_I_IN ; 
 int ATA_SENSE_ILLEGAL_REQUEST ; 
 int ATA_S_DSC ; 
 int ATA_S_ERROR ; 
 int ATA_S_READY ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
#define  GET_EVENT_STATUS_NOTIFICATION 139 
#define  INQUIRY 138 
#define  MODE_SENSE_10 137 
#define  PREVENT_ALLOW 136 
#define  READ_10 135 
#define  READ_12 134 
#define  READ_CAPACITY 133 
#define  READ_TOC 132 
#define  REPORT_LUNS 131 
#define  REQUEST_SENSE 130 
#define  START_STOP_UNIT 129 
#define  TEST_UNIT_READY 128 
 int /*<<< orphan*/  ahci_write_fis_d2h (struct ahci_port*,int,int*,int) ; 
 int /*<<< orphan*/  atapi_get_event_status_notification (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  atapi_inquiry (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  atapi_mode_sense (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  atapi_read (struct ahci_port*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atapi_read_capacity (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  atapi_read_toc (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  atapi_report_luns (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  atapi_request_sense (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  atapi_start_stop_unit (struct ahci_port*,int,int*) ; 

__attribute__((used)) static void
handle_packet_cmd(struct ahci_port *p, int slot, uint8_t *cfis)
{
	uint8_t *acmd;

	acmd = cfis + 0x40;

#ifdef AHCI_DEBUG
	{
		int i;
		DPRINTF("ACMD:");
		for (i = 0; i < 16; i++)
			DPRINTF("%02x ", acmd[i]);
		DPRINTF("\n");
	}
#endif

	switch (acmd[0]) {
	case TEST_UNIT_READY:
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		ahci_write_fis_d2h(p, slot, cfis, ATA_S_READY | ATA_S_DSC);
		break;
	case INQUIRY:
		atapi_inquiry(p, slot, cfis);
		break;
	case READ_CAPACITY:
		atapi_read_capacity(p, slot, cfis);
		break;
	case PREVENT_ALLOW:
		/* TODO */
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		ahci_write_fis_d2h(p, slot, cfis, ATA_S_READY | ATA_S_DSC);
		break;
	case READ_TOC:
		atapi_read_toc(p, slot, cfis);
		break;
	case REPORT_LUNS:
		atapi_report_luns(p, slot, cfis);
		break;
	case READ_10:
	case READ_12:
		atapi_read(p, slot, cfis, 0);
		break;
	case REQUEST_SENSE:
		atapi_request_sense(p, slot, cfis);
		break;
	case START_STOP_UNIT:
		atapi_start_stop_unit(p, slot, cfis);
		break;
	case MODE_SENSE_10:
		atapi_mode_sense(p, slot, cfis);
		break;
	case GET_EVENT_STATUS_NOTIFICATION:
		atapi_get_event_status_notification(p, slot, cfis);
		break;
	default:
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		p->sense_key = ATA_SENSE_ILLEGAL_REQUEST;
		p->asc = 0x20;
		ahci_write_fis_d2h(p, slot, cfis, ((uint32_t) (p->sense_key << 12)) |
			((uint32_t) (ATA_S_READY | ATA_S_ERROR)));
		break;
	}
}