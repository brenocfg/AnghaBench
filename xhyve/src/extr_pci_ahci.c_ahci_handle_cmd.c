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
struct ahci_port {int tfd; int xfermode; int mult_sectors; int /*<<< orphan*/  atapi; } ;

/* Variables and functions */
#define  ATA_ATAPI_IDENTIFY 169 
#define  ATA_ATA_IDENTIFY 168 
#define  ATA_DATA_SET_MANAGEMENT 167 
 int ATA_DSM_TRIM ; 
 int ATA_ERROR_ABORT ; 
 int ATA_E_ABORT ; 
#define  ATA_FLUSHCACHE 166 
#define  ATA_FLUSHCACHE48 165 
#define  ATA_IDLE_CMD 164 
#define  ATA_IDLE_IMMEDIATE 163 
#define  ATA_NOP 162 
#define  ATA_PACKET_CMD 161 
#define  ATA_PIO 160 
#define  ATA_PIO0 159 
#define  ATA_READ 158 
#define  ATA_READ48 157 
#define  ATA_READ_DMA 156 
#define  ATA_READ_DMA48 155 
#define  ATA_READ_FPDMA_QUEUED 154 
#define  ATA_READ_LOG_DMA_EXT 153 
#define  ATA_READ_LOG_EXT 152 
#define  ATA_READ_MUL 151 
#define  ATA_READ_MUL48 150 
#define  ATA_SATA_SF_AN 149 
#define  ATA_SEND_FPDMA_QUEUED 148 
#define  ATA_SETFEATURES 147 
#define  ATA_SET_MULTI 146 
 int ATA_SFPDMA_DSM ; 
#define  ATA_SF_DIS_RCACHE 145 
#define  ATA_SF_DIS_WCACHE 144 
#define  ATA_SF_ENAB_RCACHE 143 
#define  ATA_SF_ENAB_SATA_SF 142 
#define  ATA_SF_ENAB_WCACHE 141 
#define  ATA_SF_SETXFER 140 
#define  ATA_SLEEP 139 
#define  ATA_STANDBY_CMD 138 
#define  ATA_STANDBY_IMMEDIATE 137 
 int ATA_S_BUSY ; 
 int ATA_S_DSC ; 
 int ATA_S_ERROR ; 
 int ATA_S_READY ; 
#define  ATA_UDMA0 136 
#define  ATA_WDMA0 135 
#define  ATA_WRITE 134 
#define  ATA_WRITE48 133 
#define  ATA_WRITE_DMA 132 
#define  ATA_WRITE_DMA48 131 
#define  ATA_WRITE_FPDMA_QUEUED 130 
#define  ATA_WRITE_MUL 129 
#define  ATA_WRITE_MUL48 128 
 int /*<<< orphan*/  WPRINTF (char*,int) ; 
 int /*<<< orphan*/  ahci_handle_dsm_trim (struct ahci_port*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_handle_flush (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  ahci_handle_read_log (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  ahci_handle_rw (struct ahci_port*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_write_fis_d2h (struct ahci_port*,int,int*,int) ; 
 int /*<<< orphan*/  handle_atapi_identify (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  handle_identify (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  handle_packet_cmd (struct ahci_port*,int,int*) ; 

__attribute__((used)) static void
ahci_handle_cmd(struct ahci_port *p, int slot, uint8_t *cfis)
{

	p->tfd |= ATA_S_BUSY;
	switch (cfis[2]) {
	case ATA_ATA_IDENTIFY:
		handle_identify(p, slot, cfis);
		break;
	case ATA_SETFEATURES:
	{
		switch (cfis[3]) {
		case ATA_SF_ENAB_SATA_SF:
			switch (cfis[12]) {
			case ATA_SATA_SF_AN:
				p->tfd = ATA_S_DSC | ATA_S_READY;
				break;
			default:
				p->tfd = ATA_S_ERROR | ATA_S_READY;
				p->tfd |= (ATA_ERROR_ABORT << 8);
				break;
			}
			break;
		case ATA_SF_ENAB_WCACHE:
		case ATA_SF_DIS_WCACHE:
		case ATA_SF_ENAB_RCACHE:
		case ATA_SF_DIS_RCACHE:
			p->tfd = ATA_S_DSC | ATA_S_READY;
			break;
		case ATA_SF_SETXFER:
		{
			switch (cfis[12] & 0xf8) {
			case ATA_PIO:
			case ATA_PIO0:
				break;
			case ATA_WDMA0:
			case ATA_UDMA0:
				p->xfermode = (cfis[12] & 0x7);
				break;
			}
			p->tfd = ATA_S_DSC | ATA_S_READY;
			break;
		}
		default:
			p->tfd = ATA_S_ERROR | ATA_S_READY;
			p->tfd |= (ATA_ERROR_ABORT << 8);
			break;
		}
		ahci_write_fis_d2h(p, slot, cfis, p->tfd);
		break;
	}
	case ATA_SET_MULTI:
		if (cfis[12] != 0 &&
			(cfis[12] > 128 || (cfis[12] & (cfis[12] - 1)))) {
			p->tfd = ATA_S_ERROR | ATA_S_READY;
			p->tfd |= (ATA_ERROR_ABORT << 8);
		} else {
			p->mult_sectors = cfis[12];
			p->tfd = ATA_S_DSC | ATA_S_READY;
		}
		ahci_write_fis_d2h(p, slot, cfis, p->tfd);
		break;
	case ATA_READ:
	case ATA_WRITE:
	case ATA_READ48:
	case ATA_WRITE48:
	case ATA_READ_MUL:
	case ATA_WRITE_MUL:
	case ATA_READ_MUL48:
	case ATA_WRITE_MUL48:
	case ATA_READ_DMA:
	case ATA_WRITE_DMA:
	case ATA_READ_DMA48:
	case ATA_WRITE_DMA48:
	case ATA_READ_FPDMA_QUEUED:
	case ATA_WRITE_FPDMA_QUEUED:
		ahci_handle_rw(p, slot, cfis, 0);
		break;
	case ATA_FLUSHCACHE:
	case ATA_FLUSHCACHE48:
		ahci_handle_flush(p, slot, cfis);
		break;
	case ATA_DATA_SET_MANAGEMENT:
		if (cfis[11] == 0 && cfis[3] == ATA_DSM_TRIM &&
		    cfis[13] == 0 && cfis[12] == 1) {
			ahci_handle_dsm_trim(p, slot, cfis, 0);
			break;
		}
		ahci_write_fis_d2h(p, slot, cfis,
		    (ATA_E_ABORT << 8) | ATA_S_READY | ATA_S_ERROR);
		break;
	case ATA_SEND_FPDMA_QUEUED:
		if ((cfis[13] & 0x1f) == ATA_SFPDMA_DSM &&
		    cfis[17] == 0 && cfis[16] == ATA_DSM_TRIM &&
		    cfis[11] == 0 && cfis[13] == 1) {
			ahci_handle_dsm_trim(p, slot, cfis, 0);
			break;
		}
		ahci_write_fis_d2h(p, slot, cfis,
		    (ATA_E_ABORT << 8) | ATA_S_READY | ATA_S_ERROR);
		break;
	case ATA_READ_LOG_EXT:
	case ATA_READ_LOG_DMA_EXT:
		ahci_handle_read_log(p, slot, cfis);
		break;
	case ATA_NOP:
		ahci_write_fis_d2h(p, slot, cfis,
		    (ATA_E_ABORT << 8) | ATA_S_READY | ATA_S_ERROR);
		break;
	case ATA_STANDBY_CMD:
	case ATA_STANDBY_IMMEDIATE:
	case ATA_IDLE_CMD:
	case ATA_IDLE_IMMEDIATE:
	case ATA_SLEEP:
		ahci_write_fis_d2h(p, slot, cfis, ATA_S_READY | ATA_S_DSC);
		break;
	case ATA_ATAPI_IDENTIFY:
		handle_atapi_identify(p, slot, cfis);
		break;
	case ATA_PACKET_CMD:
		if (!p->atapi) {
			ahci_write_fis_d2h(p, slot, cfis,
			    (ATA_E_ABORT << 8) | ATA_S_READY | ATA_S_ERROR);
		} else
			handle_packet_cmd(p, slot, cfis);
		break;
	default:
		WPRINTF("Unsupported cmd:%02x\n", cfis[2]);
		ahci_write_fis_d2h(p, slot, cfis,
		    (ATA_E_ABORT << 8) | ATA_S_READY | ATA_S_ERROR);
		break;
	}
}