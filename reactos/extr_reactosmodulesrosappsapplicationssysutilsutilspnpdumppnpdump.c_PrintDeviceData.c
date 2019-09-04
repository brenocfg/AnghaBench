#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Node; int Size; int /*<<< orphan*/  ProductId; } ;
typedef  TYPE_1__* PCM_PNP_BIOS_DEVICE_NODE ;
typedef  int /*<<< orphan*/  CM_PNP_BIOS_DEVICE_NODE ;

/* Variables and functions */
 char* GetDeviceName (char*) ; 
 char* Hex ; 
 int /*<<< orphan*/  PnpDecodeDma (unsigned char*) ; 
 int /*<<< orphan*/  PnpDecodeFixedIoPort (unsigned char*) ; 
 int /*<<< orphan*/  PnpDecodeFixedMemory (unsigned char*) ; 
 int /*<<< orphan*/  PnpDecodeIoPort (unsigned char*) ; 
 int /*<<< orphan*/  PnpDecodeIrq (unsigned char*) ; 
 int /*<<< orphan*/  PnpDecodeMemory16 (unsigned char*) ; 
 int /*<<< orphan*/  PnpDecodeMemory32 (unsigned char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void PrintDeviceData (PCM_PNP_BIOS_DEVICE_NODE DeviceNode)
{
  char PnpId[8];
  unsigned char *Ptr;
  unsigned int TagSize;
  unsigned int TagType;

  unsigned char Id[4];

  printf ("Node: %x  Size %hu (0x%hx)\n",
	  DeviceNode->Node,
	  DeviceNode->Size,
	  DeviceNode->Size);

  memcpy(Id, &DeviceNode->ProductId, 4);

  PnpId[0] = ((Id[0] >> 2) & 0x1F) + 0x40;
  PnpId[1] = ((Id[0] << 3) & 0x18) +
	     ((Id[1] >> 5) & 0x07) + 0x40;
  PnpId[2] = (Id[1] & 0x1F) + 0x40;

  PnpId[3] = Hex[(Id[2] >> 4) & 0xF];
  PnpId[4] = Hex[Id[2] & 0x0F];

  PnpId[5] = Hex[(Id[3] >> 4) & 0x0F];
  PnpId[6] = Hex[Id[3] & 0x0F];
  PnpId[7] = 0;

  printf("  '%s' (%s)\n",
	 PnpId, GetDeviceName(PnpId));

  if (DeviceNode->Size > sizeof(CM_PNP_BIOS_DEVICE_NODE))
    {
      Ptr = (unsigned char *)(DeviceNode + 1);
      while (TRUE)
	{
	  if (*Ptr & 0x80)
	    {
	      TagType = *Ptr & 0x7F;
	      Ptr++;
	      TagSize = *Ptr;
	      Ptr++;
	      TagSize += (*Ptr << 16);
	      Ptr++;


	      switch (TagType)
		{
		  case 1:
		    PnpDecodeMemory16(Ptr);
		    break;

		  case 5:
		    PnpDecodeMemory32(Ptr);
		    break;

		  case 6:
		    PnpDecodeFixedMemory(Ptr);
		    break;

		  default:
		    printf("      Large tag: type %u  size %u\n",
			   TagType,
			   TagSize);
		    break;
		}
	    }
	  else
	    {
	      TagType = (*Ptr >> 3) & 0x0F;
	      TagSize = *Ptr & 0x07;
	      Ptr++;

	      switch (TagType)
		{
		  case 2:
		    printf("      Logical device ID\n");
		    break;

		  case 3:
		    printf("      Compatible device ID\n");
		    break;

		  case 4:
		    PnpDecodeIrq(Ptr);
		    break;

		  case 5:
		    PnpDecodeDma(Ptr);
		    break;

		  case 8:
		    PnpDecodeIoPort(Ptr);
		    break;

		  case 9:
		    PnpDecodeFixedIoPort(Ptr);
		    break;

		  case 0x0F: /* end tag */
		    break;

		  default:
		    printf("      Small tag: type %u  size %u\n",
			   TagType,
			   TagSize);
		    break;
		}

	      /* end tag */
	      if (TagType == 0x0F)
		break;
	    }

	  Ptr = Ptr + TagSize;
	}
    }
}