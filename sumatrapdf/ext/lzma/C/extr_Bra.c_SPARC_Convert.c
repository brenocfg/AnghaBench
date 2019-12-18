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
typedef  int UInt32 ;
typedef  int SizeT ;
typedef  int Byte ;

/* Variables and functions */

SizeT SPARC_Convert(Byte *data, SizeT size, UInt32 ip, int encoding)
{
  UInt32 i;
  if (size < 4)
    return 0;
  size -= 4;
  for (i = 0; i <= size; i += 4)
  {
    if ((data[i] == 0x40 && (data[i + 1] & 0xC0) == 0x00) ||
        (data[i] == 0x7F && (data[i + 1] & 0xC0) == 0xC0))
    {
      UInt32 src =
        ((UInt32)data[i + 0] << 24) |
        ((UInt32)data[i + 1] << 16) |
        ((UInt32)data[i + 2] << 8) |
        ((UInt32)data[i + 3]);
      UInt32 dest;
      
      src <<= 2;
      if (encoding)
        dest = ip + i + src;
      else
        dest = src - (ip + i);
      dest >>= 2;
      
      dest = (((0 - ((dest >> 22) & 1)) << 22) & 0x3FFFFFFF) | (dest & 0x3FFFFF) | 0x40000000;

      data[i + 0] = (Byte)(dest >> 24);
      data[i + 1] = (Byte)(dest >> 16);
      data[i + 2] = (Byte)(dest >> 8);
      data[i + 3] = (Byte)dest;
    }
  }
  return i;
}