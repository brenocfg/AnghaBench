#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {struct TYPE_4__* bNumConfigurations; struct TYPE_4__* iSerialNumber; struct TYPE_4__* iProduct; struct TYPE_4__* iManufacturer; struct TYPE_4__* bcdDevice; struct TYPE_4__* idProduct; struct TYPE_4__* idVendor; struct TYPE_4__* bMaxPacketSize0; struct TYPE_4__* bDeviceProtocol; struct TYPE_4__* bDeviceSubClass; struct TYPE_4__* bDeviceClass; struct TYPE_4__* bcdUSB; struct TYPE_4__* bDescriptorType; struct TYPE_4__* bLength; } ;
typedef  TYPE_1__* PUSB_DEVICE_DESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_1__*) ; 

VOID
DumpDeviceDescriptor(PUSB_DEVICE_DESCRIPTOR DeviceDescriptor)
{
    DPRINT1("Dumping Device Descriptor %x\n", DeviceDescriptor);
    DPRINT1("bLength %x\n", DeviceDescriptor->bLength);
    DPRINT1("bDescriptorType %x\n", DeviceDescriptor->bDescriptorType);
    DPRINT1("bcdUSB %x\n", DeviceDescriptor->bcdUSB);
    DPRINT1("bDeviceClass %x\n", DeviceDescriptor->bDeviceClass);
    DPRINT1("bDeviceSubClass %x\n", DeviceDescriptor->bDeviceSubClass);
    DPRINT1("bDeviceProtocol %x\n", DeviceDescriptor->bDeviceProtocol);
    DPRINT1("bMaxPacketSize0 %x\n", DeviceDescriptor->bMaxPacketSize0);
    DPRINT1("idVendor %x\n", DeviceDescriptor->idVendor);
    DPRINT1("idProduct %x\n", DeviceDescriptor->idProduct);
    DPRINT1("bcdDevice %x\n", DeviceDescriptor->bcdDevice);
    DPRINT1("iManufacturer %x\n", DeviceDescriptor->iManufacturer);
    DPRINT1("iProduct %x\n", DeviceDescriptor->iProduct);
    DPRINT1("iSerialNumber %x\n", DeviceDescriptor->iSerialNumber);
    DPRINT1("bNumConfigurations %x\n", DeviceDescriptor->bNumConfigurations);
}