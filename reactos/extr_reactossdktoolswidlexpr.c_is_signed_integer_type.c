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
 int FALSE ; 
 int TRUE ; 
#define  TYPE_BASIC 144 
#define  TYPE_BASIC_BYTE 143 
#define  TYPE_BASIC_CHAR 142 
#define  TYPE_BASIC_DOUBLE 141 
#define  TYPE_BASIC_ERROR_STATUS_T 140 
#define  TYPE_BASIC_FLOAT 139 
#define  TYPE_BASIC_HANDLE 138 
#define  TYPE_BASIC_HYPER 137 
#define  TYPE_BASIC_INT 136 
#define  TYPE_BASIC_INT16 135 
#define  TYPE_BASIC_INT32 134 
#define  TYPE_BASIC_INT3264 133 
#define  TYPE_BASIC_INT64 132 
#define  TYPE_BASIC_INT8 131 
#define  TYPE_BASIC_LONG 130 
#define  TYPE_BASIC_WCHAR 129 
#define  TYPE_ENUM 128 
 int /*<<< orphan*/  type_basic_get_sign (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  type_basic_get_type (int /*<<< orphan*/  const*) ; 
 int type_get_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int is_signed_integer_type(const type_t *type)
{
    switch (type_get_type(type))
    {
    case TYPE_ENUM:
        return FALSE;
    case TYPE_BASIC:
        switch (type_basic_get_type(type))
        {
        case TYPE_BASIC_INT8:
        case TYPE_BASIC_INT16:
        case TYPE_BASIC_INT32:
        case TYPE_BASIC_INT64:
        case TYPE_BASIC_INT:
        case TYPE_BASIC_INT3264:
        case TYPE_BASIC_LONG:
            return type_basic_get_sign(type) < 0;
        case TYPE_BASIC_CHAR:
            return TRUE;
        case TYPE_BASIC_HYPER:
        case TYPE_BASIC_BYTE:
        case TYPE_BASIC_WCHAR:
        case TYPE_BASIC_ERROR_STATUS_T:
        case TYPE_BASIC_FLOAT:
        case TYPE_BASIC_DOUBLE:
        case TYPE_BASIC_HANDLE:
            return FALSE;
        }
        /* FALLTHROUGH */
    default:
        return FALSE;
    }
}