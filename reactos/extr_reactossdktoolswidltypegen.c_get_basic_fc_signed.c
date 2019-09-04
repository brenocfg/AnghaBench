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
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 unsigned char FC_BIND_PRIMITIVE ; 
 unsigned char FC_BYTE ; 
 unsigned char FC_CHAR ; 
 unsigned char FC_DOUBLE ; 
 unsigned char FC_ERROR_STATUS_T ; 
 unsigned char FC_FLOAT ; 
 unsigned char FC_HYPER ; 
 unsigned char FC_INT3264 ; 
 unsigned char FC_LONG ; 
 unsigned char FC_SHORT ; 
 unsigned char FC_SMALL ; 
 unsigned char FC_WCHAR ; 
#define  TYPE_BASIC_BYTE 142 
#define  TYPE_BASIC_CHAR 141 
#define  TYPE_BASIC_DOUBLE 140 
#define  TYPE_BASIC_ERROR_STATUS_T 139 
#define  TYPE_BASIC_FLOAT 138 
#define  TYPE_BASIC_HANDLE 137 
#define  TYPE_BASIC_HYPER 136 
#define  TYPE_BASIC_INT 135 
#define  TYPE_BASIC_INT16 134 
#define  TYPE_BASIC_INT32 133 
#define  TYPE_BASIC_INT3264 132 
#define  TYPE_BASIC_INT64 131 
#define  TYPE_BASIC_INT8 130 
#define  TYPE_BASIC_LONG 129 
#define  TYPE_BASIC_WCHAR 128 
 int type_basic_get_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static unsigned char get_basic_fc_signed(const type_t *type)
{
    switch (type_basic_get_type(type))
    {
    case TYPE_BASIC_INT8: return FC_SMALL;
    case TYPE_BASIC_INT16: return FC_SHORT;
    case TYPE_BASIC_INT32: return FC_LONG;
    case TYPE_BASIC_INT64: return FC_HYPER;
    case TYPE_BASIC_INT: return FC_LONG;
    case TYPE_BASIC_INT3264: return FC_INT3264;
    case TYPE_BASIC_LONG: return FC_LONG;
    case TYPE_BASIC_BYTE: return FC_BYTE;
    case TYPE_BASIC_CHAR: return FC_CHAR;
    case TYPE_BASIC_WCHAR: return FC_WCHAR;
    case TYPE_BASIC_HYPER: return FC_HYPER;
    case TYPE_BASIC_FLOAT: return FC_FLOAT;
    case TYPE_BASIC_DOUBLE: return FC_DOUBLE;
    case TYPE_BASIC_ERROR_STATUS_T: return FC_ERROR_STATUS_T;
    case TYPE_BASIC_HANDLE: return FC_BIND_PRIMITIVE;
    }
    return 0;
}