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
typedef  enum typegen_type { ____Placeholder_typegen_type } typegen_type ;
typedef  int /*<<< orphan*/  attr_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CONTEXTHANDLE ; 
 int /*<<< orphan*/  ATTR_IIDIS ; 
 int /*<<< orphan*/  ATTR_RANGE ; 
 unsigned int TDT_IGNORE_RANGES ; 
 unsigned int TDT_IGNORE_STRINGS ; 
 int TGT_ARRAY ; 
 int TGT_BASIC ; 
 int TGT_CTXT_HANDLE ; 
 int TGT_CTXT_HANDLE_POINTER ; 
 int TGT_ENUM ; 
 int TGT_IFACE_POINTER ; 
 int TGT_INVALID ; 
 int TGT_POINTER ; 
 int TGT_RANGE ; 
 int TGT_STRING ; 
 int TGT_STRUCT ; 
 int TGT_UNION ; 
 int TGT_USER_TYPE ; 
#define  TYPE_ALIAS 141 
#define  TYPE_ARRAY 140 
#define  TYPE_BASIC 139 
#define  TYPE_BITFIELD 138 
#define  TYPE_COCLASS 137 
#define  TYPE_ENCAPSULATED_UNION 136 
#define  TYPE_ENUM 135 
#define  TYPE_FUNCTION 134 
#define  TYPE_INTERFACE 133 
#define  TYPE_MODULE 132 
#define  TYPE_POINTER 131 
#define  TYPE_STRUCT 130 
#define  TYPE_UNION 129 
#define  TYPE_VOID 128 
 scalar_t__ is_aliaschain_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_string_type (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ is_user_type (int /*<<< orphan*/  const*) ; 
 int type_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* type_pointer_get_ref (int /*<<< orphan*/  const*) ; 

enum typegen_type typegen_detect_type(const type_t *type, const attr_list_t *attrs, unsigned int flags)
{
    if (is_user_type(type))
        return TGT_USER_TYPE;

    if (is_aliaschain_attr(type, ATTR_CONTEXTHANDLE))
        return TGT_CTXT_HANDLE;

    if (!(flags & TDT_IGNORE_STRINGS) && is_string_type(attrs, type))
        return TGT_STRING;

    switch (type_get_type(type))
    {
    case TYPE_BASIC:
        if (!(flags & TDT_IGNORE_RANGES) &&
            (is_attr(attrs, ATTR_RANGE) || is_aliaschain_attr(type, ATTR_RANGE)))
            return TGT_RANGE;
        return TGT_BASIC;
    case TYPE_ENUM:
        if (!(flags & TDT_IGNORE_RANGES) &&
            (is_attr(attrs, ATTR_RANGE) || is_aliaschain_attr(type, ATTR_RANGE)))
            return TGT_RANGE;
        return TGT_ENUM;
    case TYPE_POINTER:
        if (type_get_type(type_pointer_get_ref(type)) == TYPE_INTERFACE ||
            (type_get_type(type_pointer_get_ref(type)) == TYPE_VOID && is_attr(attrs, ATTR_IIDIS)))
            return TGT_IFACE_POINTER;
        else if (is_aliaschain_attr(type_pointer_get_ref(type), ATTR_CONTEXTHANDLE))
            return TGT_CTXT_HANDLE_POINTER;
        else
            return TGT_POINTER;
    case TYPE_STRUCT:
        return TGT_STRUCT;
    case TYPE_ENCAPSULATED_UNION:
    case TYPE_UNION:
        return TGT_UNION;
    case TYPE_ARRAY:
        return TGT_ARRAY;
    case TYPE_FUNCTION:
    case TYPE_COCLASS:
    case TYPE_INTERFACE:
    case TYPE_MODULE:
    case TYPE_VOID:
    case TYPE_ALIAS:
    case TYPE_BITFIELD:
        break;
    }
    return TGT_INVALID;
}