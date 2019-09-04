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
typedef  int UINT ;

/* Variables and functions */
#define  CIM_BOOLEAN 137 
 int CIM_ILLEGAL ; 
#define  CIM_SINT16 136 
#define  CIM_SINT32 135 
#define  CIM_SINT64 134 
#define  CIM_SINT8 133 
#define  CIM_STRING 132 
#define  CIM_UINT16 131 
#define  CIM_UINT32 130 
#define  CIM_UINT64 129 
#define  CIM_UINT8 128 

__attribute__((used)) static UINT resolve_type( UINT left, UINT right )
{
    switch (left)
    {
    case CIM_SINT8:
    case CIM_SINT16:
    case CIM_SINT32:
    case CIM_SINT64:
    case CIM_UINT8:
    case CIM_UINT16:
    case CIM_UINT32:
    case CIM_UINT64:
        switch (right)
        {
            case CIM_SINT8:
            case CIM_SINT16:
            case CIM_SINT32:
            case CIM_SINT64:
            case CIM_UINT8:
            case CIM_UINT16:
            case CIM_UINT32:
            case CIM_UINT64:
                return CIM_UINT64;
            default: break;
        }
        break;

    case CIM_STRING:
        if (right == CIM_STRING) return CIM_STRING;
        break;

    case CIM_BOOLEAN:
        if (right == CIM_BOOLEAN) return CIM_BOOLEAN;
        break;

    default:
        break;
    }
    return CIM_ILLEGAL;
}