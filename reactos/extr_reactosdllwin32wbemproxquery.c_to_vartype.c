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
typedef  int /*<<< orphan*/  VARTYPE ;
typedef  int CIMTYPE ;

/* Variables and functions */
#define  CIM_BOOLEAN 138 
#define  CIM_DATETIME 137 
#define  CIM_SINT16 136 
#define  CIM_SINT32 135 
#define  CIM_SINT64 134 
#define  CIM_SINT8 133 
#define  CIM_STRING 132 
#define  CIM_UINT16 131 
#define  CIM_UINT32 130 
#define  CIM_UINT64 129 
#define  CIM_UINT8 128 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  VT_BOOL ; 
 int /*<<< orphan*/  VT_BSTR ; 
 int /*<<< orphan*/  VT_I1 ; 
 int /*<<< orphan*/  VT_I2 ; 
 int /*<<< orphan*/  VT_I4 ; 
 int /*<<< orphan*/  VT_I8 ; 
 int /*<<< orphan*/  VT_UI1 ; 
 int /*<<< orphan*/  VT_UI2 ; 
 int /*<<< orphan*/  VT_UI4 ; 
 int /*<<< orphan*/  VT_UI8 ; 

VARTYPE to_vartype( CIMTYPE type )
{
    switch (type)
    {
    case CIM_BOOLEAN:  return VT_BOOL;
    case CIM_STRING:
    case CIM_DATETIME: return VT_BSTR;
    case CIM_SINT8:    return VT_I1;
    case CIM_UINT8:    return VT_UI1;
    case CIM_SINT16:   return VT_I2;
    case CIM_UINT16:   return VT_UI2;
    case CIM_SINT32:   return VT_I4;
    case CIM_UINT32:   return VT_UI4;
    case CIM_SINT64:   return VT_I8;
    case CIM_UINT64:   return VT_UI8;
    default:
        ERR("unhandled type %u\n", type);
        break;
    }
    return 0;
}