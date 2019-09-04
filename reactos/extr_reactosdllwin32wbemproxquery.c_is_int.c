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
typedef  int CIMTYPE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CIM_SINT16 135 
#define  CIM_SINT32 134 
#define  CIM_SINT64 133 
#define  CIM_SINT8 132 
#define  CIM_UINT16 131 
#define  CIM_UINT32 130 
#define  CIM_UINT64 129 
#define  CIM_UINT8 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL is_int( CIMTYPE type )
{
    switch (type)
    {
    case CIM_SINT8:
    case CIM_SINT16:
    case CIM_SINT32:
    case CIM_SINT64:
    case CIM_UINT8:
    case CIM_UINT16:
    case CIM_UINT32:
    case CIM_UINT64:
        return TRUE;
    default:
        return FALSE;
    }
}