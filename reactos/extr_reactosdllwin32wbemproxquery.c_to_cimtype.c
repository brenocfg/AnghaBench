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
typedef  int VARTYPE ;
typedef  int /*<<< orphan*/  CIMTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CIM_BOOLEAN ; 
 int /*<<< orphan*/  CIM_SINT16 ; 
 int /*<<< orphan*/  CIM_SINT32 ; 
 int /*<<< orphan*/  CIM_SINT64 ; 
 int /*<<< orphan*/  CIM_SINT8 ; 
 int /*<<< orphan*/  CIM_STRING ; 
 int /*<<< orphan*/  CIM_UINT16 ; 
 int /*<<< orphan*/  CIM_UINT32 ; 
 int /*<<< orphan*/  CIM_UINT64 ; 
 int /*<<< orphan*/  CIM_UINT8 ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  VT_BOOL 137 
#define  VT_BSTR 136 
#define  VT_I1 135 
#define  VT_I2 134 
#define  VT_I4 133 
#define  VT_I8 132 
#define  VT_UI1 131 
#define  VT_UI2 130 
#define  VT_UI4 129 
#define  VT_UI8 128 

__attribute__((used)) static CIMTYPE to_cimtype( VARTYPE type )
{
    switch (type)
    {
    case VT_BOOL:  return CIM_BOOLEAN;
    case VT_BSTR:  return CIM_STRING;
    case VT_I1:    return CIM_SINT8;
    case VT_UI1:   return CIM_UINT8;
    case VT_I2:    return CIM_SINT16;
    case VT_UI2:   return CIM_UINT16;
    case VT_I4:    return CIM_SINT32;
    case VT_UI4:   return CIM_UINT32;
    case VT_I8:    return CIM_SINT64;
    case VT_UI8:   return CIM_UINT64;
    default:
        ERR("unhandled type %u\n", type);
        break;
    }
    return 0;
}