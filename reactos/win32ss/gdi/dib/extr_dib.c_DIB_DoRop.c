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
typedef  int ULONG ;

/* Variables and functions */
#define  R3_OPINDEX_BLACKNESS 143 
#define  R3_OPINDEX_DSTINVERT 142 
#define  R3_OPINDEX_MERGECOPY 141 
#define  R3_OPINDEX_MERGEPAINT 140 
#define  R3_OPINDEX_NOOP 139 
#define  R3_OPINDEX_NOTSRCCOPY 138 
#define  R3_OPINDEX_NOTSRCERASE 137 
#define  R3_OPINDEX_PATCOPY 136 
#define  R3_OPINDEX_PATINVERT 135 
#define  R3_OPINDEX_PATPAINT 134 
#define  R3_OPINDEX_SRCAND 133 
#define  R3_OPINDEX_SRCCOPY 132 
#define  R3_OPINDEX_SRCERASE 131 
#define  R3_OPINDEX_SRCINVERT 130 
#define  R3_OPINDEX_SRCPAINT 129 
#define  R3_OPINDEX_WHITENESS 128 

ULONG
DIB_DoRop(ULONG Rop, ULONG Dest, ULONG Source, ULONG Pattern)
{
  ULONG ResultNibble;
  ULONG Result = 0;
  ULONG i;
static const ULONG ExpandDest[16] =
    {
      0x55555555 /* 0000 */,
      0x555555AA /* 0001 */,
      0x5555AA55 /* 0010 */,
      0x5555AAAA /* 0011 */,
      0x55AA5555 /* 0100 */,
      0x55AA55AA /* 0101 */,
      0x55AAAA55 /* 0110 */,
      0x55AAAAAA /* 0111 */,
      0xAA555555 /* 1000 */,
      0xAA5555AA /* 1001 */,
      0xAA55AA55 /* 1010 */,
      0xAA55AAAA /* 1011 */,
      0xAAAA5555 /* 1100 */,
      0xAAAA55AA /* 1101 */,
      0xAAAAAA55 /* 1110 */,
      0xAAAAAAAA /* 1111 */,
    };
  static const ULONG ExpandSource[16] =
    {
      0x33333333 /* 0000 */,
      0x333333CC /* 0001 */,
      0x3333CC33 /* 0010 */,
      0x3333CCCC /* 0011 */,
      0x33CC3333 /* 0100 */,
      0x33CC33CC /* 0101 */,
      0x33CCCC33 /* 0110 */,
      0x33CCCCCC /* 0111 */,
      0xCC333333 /* 1000 */,
      0xCC3333CC /* 1001 */,
      0xCC33CC33 /* 1010 */,
      0xCC33CCCC /* 1011 */,
      0xCCCC3333 /* 1100 */,
      0xCCCC33CC /* 1101 */,
      0xCCCCCC33 /* 1110 */,
      0xCCCCCCCC /* 1111 */,
    };
  static const ULONG ExpandPattern[16] =
    {
      0x0F0F0F0F /* 0000 */,
      0x0F0F0FF0 /* 0001 */,
      0x0F0FF00F /* 0010 */,
      0x0F0FF0F0 /* 0011 */,
      0x0FF00F0F /* 0100 */,
      0x0FF00FF0 /* 0101 */,
      0x0FF0F00F /* 0110 */,
      0x0FF0F0F0 /* 0111 */,
      0xF00F0F0F /* 1000 */,
      0xF00F0FF0 /* 1001 */,
      0xF00FF00F /* 1010 */,
      0xF00FF0F0 /* 1011 */,
      0xF0F00F0F /* 1100 */,
      0xF0F00FF0 /* 1101 */,
      0xF0F0F00F /* 1110 */,
      0xF0F0F0F0 /* 1111 */,
    };

    Rop &=0xFF;
    switch(Rop)
    {

        /* Optimized code for the various named rop codes. */
        case R3_OPINDEX_NOOP:        return(Dest);
        case R3_OPINDEX_BLACKNESS:   return(0);
        case R3_OPINDEX_NOTSRCERASE: return(~(Dest | Source));
        case R3_OPINDEX_NOTSRCCOPY:  return(~Source);
        case R3_OPINDEX_SRCERASE:    return((~Dest) & Source);
        case R3_OPINDEX_DSTINVERT:   return(~Dest);
        case R3_OPINDEX_PATINVERT:   return(Dest ^ Pattern);
        case R3_OPINDEX_SRCINVERT:   return(Dest ^ Source);
        case R3_OPINDEX_SRCAND:      return(Dest & Source);
        case R3_OPINDEX_MERGEPAINT:  return(Dest | (~Source));
        case R3_OPINDEX_SRCPAINT:    return(Dest | Source);
        case R3_OPINDEX_MERGECOPY:   return(Source & Pattern);
        case R3_OPINDEX_SRCCOPY:     return(Source);
        case R3_OPINDEX_PATCOPY:     return(Pattern);
        case R3_OPINDEX_PATPAINT:    return(Dest | (~Source) | Pattern);
        case R3_OPINDEX_WHITENESS:   return(0xFFFFFFFF);
    }

  /* Expand the ROP operation to all four bytes */
  Rop |= (Rop << 24) | (Rop << 16) | (Rop << 8);
  /* Do the operation on four bits simultaneously. */
  Result = 0;
  for (i = 0; i < 8; i++)
  {
    ResultNibble = Rop & ExpandDest[Dest & 0xF] & ExpandSource[Source & 0xF] & ExpandPattern[Pattern & 0xF];
    Result |= (((ResultNibble & 0xFF000000) ? 0x8 : 0x0) | ((ResultNibble & 0x00FF0000) ? 0x4 : 0x0) |
    ((ResultNibble & 0x0000FF00) ? 0x2 : 0x0) | ((ResultNibble & 0x000000FF) ? 0x1 : 0x0)) << (i * 4);
    Dest >>= 4;
    Source >>= 4;
    Pattern >>= 4;
  }
  return(Result);
}