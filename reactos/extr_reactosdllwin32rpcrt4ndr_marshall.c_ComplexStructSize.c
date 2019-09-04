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
typedef  int /*<<< orphan*/  SHORT ;
typedef  int /*<<< orphan*/  PMIDL_STUB_MESSAGE ;
typedef  int* PFORMAT_STRING ;
typedef  int /*<<< orphan*/  INT_PTR ;

/* Variables and functions */
 int EmbeddedComplexSize (int /*<<< orphan*/ ,int*) ; 
#define  FC_ALIGNM2 160 
#define  FC_ALIGNM4 159 
#define  FC_ALIGNM8 158 
#define  FC_BYTE 157 
#define  FC_CHAR 156 
#define  FC_DOUBLE 155 
#define  FC_EMBEDDED_COMPLEX 154 
 int FC_END ; 
#define  FC_ENUM16 153 
#define  FC_ENUM32 152 
#define  FC_FLOAT 151 
#define  FC_FP 150 
#define  FC_HYPER 149 
#define  FC_INT3264 148 
#define  FC_LONG 147 
#define  FC_OP 146 
#define  FC_PAD 145 
#define  FC_POINTER 144 
#define  FC_RP 143 
#define  FC_SHORT 142 
#define  FC_SMALL 141 
#define  FC_STRUCTPAD1 140 
#define  FC_STRUCTPAD2 139 
#define  FC_STRUCTPAD3 138 
#define  FC_STRUCTPAD4 137 
#define  FC_STRUCTPAD5 136 
#define  FC_STRUCTPAD6 135 
#define  FC_STRUCTPAD7 134 
#define  FC_UINT3264 133 
#define  FC_ULONG 132 
#define  FC_UP 131 
#define  FC_USHORT 130 
#define  FC_USMALL 129 
#define  FC_WCHAR 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  align_length (int*,int) ; 

ULONG ComplexStructSize(PMIDL_STUB_MESSAGE pStubMsg, PFORMAT_STRING pFormat)
{
  PFORMAT_STRING desc;
  ULONG size = 0;

  while (*pFormat != FC_END) {
    switch (*pFormat) {
    case FC_BYTE:
    case FC_CHAR:
    case FC_SMALL:
    case FC_USMALL:
      size += 1;
      break;
    case FC_WCHAR:
    case FC_SHORT:
    case FC_USHORT:
      size += 2;
      break;
    case FC_LONG:
    case FC_ULONG:
    case FC_ENUM16:
    case FC_ENUM32:
    case FC_FLOAT:
      size += 4;
      break;
    case FC_INT3264:
    case FC_UINT3264:
      size += sizeof(INT_PTR);
      break;
    case FC_HYPER:
    case FC_DOUBLE:
      size += 8;
      break;
    case FC_RP:
    case FC_UP:
    case FC_OP:
    case FC_FP:
    case FC_POINTER:
      size += sizeof(void *);
      if (*pFormat != FC_POINTER)
        pFormat += 4;
      break;
    case FC_ALIGNM2:
      align_length(&size, 2);
      break;
    case FC_ALIGNM4:
      align_length(&size, 4);
      break;
    case FC_ALIGNM8:
      align_length(&size, 8);
      break;
    case FC_STRUCTPAD1:
    case FC_STRUCTPAD2:
    case FC_STRUCTPAD3:
    case FC_STRUCTPAD4:
    case FC_STRUCTPAD5:
    case FC_STRUCTPAD6:
    case FC_STRUCTPAD7:
      size += *pFormat - FC_STRUCTPAD1 + 1;
      break;
    case FC_EMBEDDED_COMPLEX:
      size += pFormat[1];
      pFormat += 2;
      desc = pFormat + *(const SHORT*)pFormat;
      size += EmbeddedComplexSize(pStubMsg, desc);
      pFormat += 2;
      continue;
    case FC_PAD:
      break;
    default:
      FIXME("unhandled format 0x%02x\n", *pFormat);
    }
    pFormat++;
  }

  return size;
}