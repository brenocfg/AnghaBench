#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  USB_INTERFACE_DESCRIPTOR ;
typedef  int /*<<< orphan*/  USB_ENDPOINT_DESCRIPTOR ;
typedef  int /*<<< orphan*/  USB_CONFIGURATION_DESCRIPTOR ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_7__ {TYPE_1__* bInterval; TYPE_1__* wMaxPacketSize; TYPE_1__* bmAttributes; TYPE_1__* bEndpointAddress; TYPE_1__* bDescriptorType; TYPE_1__* bLength; } ;
struct TYPE_6__ {scalar_t__ bNumInterfaces; scalar_t__ bNumEndpoints; struct TYPE_6__* iInterface; struct TYPE_6__* bInterfaceProtocol; struct TYPE_6__* bInterfaceSubClass; struct TYPE_6__* bInterfaceClass; struct TYPE_6__* bAlternateSetting; struct TYPE_6__* bInterfaceNumber; struct TYPE_6__* bDescriptorType; struct TYPE_6__* bLength; struct TYPE_6__* MaxPower; struct TYPE_6__* bmAttributes; struct TYPE_6__* iConfiguration; struct TYPE_6__* bConfigurationValue; struct TYPE_6__* wTotalLength; } ;
typedef  TYPE_1__* PUSB_INTERFACE_DESCRIPTOR ;
typedef  TYPE_2__* PUSB_ENDPOINT_DESCRIPTOR ;
typedef  TYPE_1__* PUSB_CONFIGURATION_DESCRIPTOR ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_1__*) ; 

VOID
DumpFullConfigurationDescriptor(PUSB_CONFIGURATION_DESCRIPTOR ConfigurationDescriptor)
{
    PUSB_INTERFACE_DESCRIPTOR InterfaceDescriptor;
    PUSB_ENDPOINT_DESCRIPTOR EndpointDescriptor;
    LONG i, j;

    DPRINT1("Dumping ConfigurationDescriptor %x\n", ConfigurationDescriptor);
    DPRINT1("bLength %x\n", ConfigurationDescriptor->bLength);
    DPRINT1("bDescriptorType %x\n", ConfigurationDescriptor->bDescriptorType);
    DPRINT1("wTotalLength %x\n", ConfigurationDescriptor->wTotalLength);
    DPRINT1("bNumInterfaces %x\n", ConfigurationDescriptor->bNumInterfaces);
    DPRINT1("bConfigurationValue %x\n", ConfigurationDescriptor->bConfigurationValue);
    DPRINT1("iConfiguration %x\n", ConfigurationDescriptor->iConfiguration);
    DPRINT1("bmAttributes %x\n", ConfigurationDescriptor->bmAttributes);
    DPRINT1("MaxPower %x\n", ConfigurationDescriptor->MaxPower);

    InterfaceDescriptor = (PUSB_INTERFACE_DESCRIPTOR) ((ULONG_PTR)ConfigurationDescriptor + sizeof(USB_CONFIGURATION_DESCRIPTOR));

    for (i=0; i < ConfigurationDescriptor->bNumInterfaces; i++)
    {
        DPRINT1("- Dumping InterfaceDescriptor %x\n", InterfaceDescriptor);
        DPRINT1("  bLength %x\n", InterfaceDescriptor->bLength);
        DPRINT1("  bDescriptorType %x\n", InterfaceDescriptor->bDescriptorType);
        DPRINT1("  bInterfaceNumber %x\n", InterfaceDescriptor->bInterfaceNumber);
        DPRINT1("  bAlternateSetting %x\n", InterfaceDescriptor->bAlternateSetting);
        DPRINT1("  bNumEndpoints %x\n", InterfaceDescriptor->bNumEndpoints);
        DPRINT1("  bInterfaceClass %x\n", InterfaceDescriptor->bInterfaceClass);
        DPRINT1("  bInterfaceSubClass %x\n", InterfaceDescriptor->bInterfaceSubClass);
        DPRINT1("  bInterfaceProtocol %x\n", InterfaceDescriptor->bInterfaceProtocol);
        DPRINT1("  iInterface %x\n", InterfaceDescriptor->iInterface);

        EndpointDescriptor = (PUSB_ENDPOINT_DESCRIPTOR) ((ULONG_PTR)InterfaceDescriptor + sizeof(USB_INTERFACE_DESCRIPTOR));

        for (j=0; j < InterfaceDescriptor->bNumEndpoints; j++)
        {
            DPRINT1("   bLength %x\n", EndpointDescriptor->bLength);
            DPRINT1("   bDescriptorType %x\n", EndpointDescriptor->bDescriptorType);
            DPRINT1("   bEndpointAddress %x\n", EndpointDescriptor->bEndpointAddress);
            DPRINT1("   bmAttributes %x\n", EndpointDescriptor->bmAttributes);
            DPRINT1("   wMaxPacketSize %x\n", EndpointDescriptor->wMaxPacketSize);
            DPRINT1("   bInterval %x\n", EndpointDescriptor->bInterval);
            EndpointDescriptor = (PUSB_ENDPOINT_DESCRIPTOR) ((ULONG_PTR)EndpointDescriptor + sizeof(USB_ENDPOINT_DESCRIPTOR));
        }
        InterfaceDescriptor = (PUSB_INTERFACE_DESCRIPTOR)(ULONG_PTR)EndpointDescriptor;
    }
}