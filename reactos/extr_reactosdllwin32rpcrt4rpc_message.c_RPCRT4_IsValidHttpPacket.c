#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_4__ {unsigned short num_data_items; } ;
struct TYPE_5__ {TYPE_1__ http; } ;
typedef  TYPE_2__ RpcPktHdr ;
typedef  int /*<<< orphan*/  GUID ;
typedef  unsigned char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL RPCRT4_IsValidHttpPacket(RpcPktHdr *hdr, unsigned char *data,
                              unsigned short data_len)
{
  unsigned short i;
  BYTE *p = data;

  for (i = 0; i < hdr->http.num_data_items; i++)
  {
    ULONG type;

    if (data_len < sizeof(ULONG))
      return FALSE;

    type = *(ULONG *)p;
    p += sizeof(ULONG);
    data_len -= sizeof(ULONG);

    switch (type)
    {
      case 0x3:
      case 0xc:
        if (data_len < sizeof(GUID))
          return FALSE;
        p += sizeof(GUID);
        data_len -= sizeof(GUID);
        break;
      case 0x0:
      case 0x2:
      case 0x4:
      case 0x5:
      case 0x6:
      case 0xd:
        if (data_len < sizeof(ULONG))
          return FALSE;
        p += sizeof(ULONG);
        data_len -= sizeof(ULONG);
        break;
      case 0x1:
        if (data_len < 24)
          return FALSE;
        p += 24;
        data_len -= 24;
        break;
      default:
        FIXME("unimplemented type 0x%x\n", type);
        break;
    }
  }
  return TRUE;
}