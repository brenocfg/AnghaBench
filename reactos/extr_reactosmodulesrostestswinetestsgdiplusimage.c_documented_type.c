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
 int PropertyTagTypeByte ; 
#define  PropertyTagTypeDouble 131 
#define  PropertyTagTypeFloat 130 
#define  PropertyTagTypeSByte 129 
#define  PropertyTagTypeSShort 128 
 int PropertyTagTypeShort ; 
 int PropertyTagTypeUndefined ; 

__attribute__((used)) static UINT documented_type(UINT type)
{
    switch (type)
    {
    case PropertyTagTypeSByte: return PropertyTagTypeByte;
    case PropertyTagTypeSShort: return PropertyTagTypeShort;
    case PropertyTagTypeFloat: return PropertyTagTypeUndefined;
    case PropertyTagTypeDouble: return PropertyTagTypeUndefined;
    default: return type;
    }
}