#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct e82545_softc {size_t* eeprom_data; TYPE_1__* vms; } ;
struct TYPE_2__ {int* mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,size_t) ; 
 size_t E82545_DEV_ID_82545EM_COPPER ; 
 size_t E82545_SUBDEV_ID ; 
 void* E82545_VENDOR_ID_INTEL ; 
 size_t NVM_CHECKSUM_REG ; 
 size_t NVM_DEV_ID ; 
 size_t NVM_MAC_ADDR ; 
 size_t NVM_SUB_DEV_ID ; 
 size_t NVM_SUB_VEN_ID ; 
 size_t NVM_SUM ; 
 size_t NVM_VEN_ID ; 

__attribute__((used)) static void
e82545_init_eeprom(struct e82545_softc *sc)
{
	uint16_t checksum, i;

        /* mac addr */
	sc->eeprom_data[NVM_MAC_ADDR] = (uint16_t)((sc->vms->mac[0]) |
		(sc->vms->mac[1]) << 8);
	sc->eeprom_data[NVM_MAC_ADDR+1] = (uint16_t)((sc->vms->mac[2]) |
		(sc->vms->mac[3] << 8));
	sc->eeprom_data[NVM_MAC_ADDR+2] = (uint16_t)((sc->vms->mac[4]) |
		(sc->vms->mac[5] << 8));

	/* pci ids */
	sc->eeprom_data[NVM_SUB_DEV_ID] = E82545_SUBDEV_ID;
	sc->eeprom_data[NVM_SUB_VEN_ID] = E82545_VENDOR_ID_INTEL;
	sc->eeprom_data[NVM_DEV_ID] = E82545_DEV_ID_82545EM_COPPER;
	sc->eeprom_data[NVM_VEN_ID] = E82545_VENDOR_ID_INTEL;

	/* fill in the checksum */
        checksum = 0;
	for (i = 0; i < NVM_CHECKSUM_REG; i++) {
		checksum += sc->eeprom_data[i];
	}
	checksum = NVM_SUM - checksum;
	sc->eeprom_data[NVM_CHECKSUM_REG] = checksum;
	DPRINTF("eeprom checksum: 0x%x\r\n", checksum);
}