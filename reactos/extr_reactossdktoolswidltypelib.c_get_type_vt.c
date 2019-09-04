#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;
struct TYPE_13__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_PUBLIC ; 
#define  TYPE_ALIAS 156 
#define  TYPE_ARRAY 155 
#define  TYPE_BASIC 154 
#define  TYPE_BASIC_BYTE 153 
#define  TYPE_BASIC_CHAR 152 
#define  TYPE_BASIC_DOUBLE 151 
#define  TYPE_BASIC_ERROR_STATUS_T 150 
#define  TYPE_BASIC_FLOAT 149 
#define  TYPE_BASIC_HANDLE 148 
#define  TYPE_BASIC_HYPER 147 
#define  TYPE_BASIC_INT 146 
#define  TYPE_BASIC_INT16 145 
#define  TYPE_BASIC_INT32 144 
#define  TYPE_BASIC_INT3264 143 
#define  TYPE_BASIC_INT64 142 
#define  TYPE_BASIC_INT8 141 
#define  TYPE_BASIC_LONG 140 
#define  TYPE_BASIC_WCHAR 139 
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
 unsigned short VT_CARRAY ; 
 unsigned short VT_DISPATCH ; 
 unsigned short VT_I1 ; 
 unsigned short VT_I2 ; 
 unsigned short VT_I4 ; 
 unsigned short VT_I8 ; 
 unsigned short VT_INT ; 
 unsigned short VT_PTR ; 
 unsigned short VT_R4 ; 
 unsigned short VT_R8 ; 
 unsigned short VT_SAFEARRAY ; 
 unsigned short VT_UI1 ; 
 unsigned short VT_UI2 ; 
 unsigned short VT_UI4 ; 
 unsigned short VT_UI8 ; 
 unsigned short VT_UINT ; 
 unsigned short VT_UNKNOWN ; 
 unsigned short VT_USERDEFINED ; 
 unsigned short VT_VOID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 unsigned short builtin_vt (TYPE_1__*) ; 
 int /*<<< orphan*/  chat (char*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match (scalar_t__,char*) ; 
 int pointer_size ; 
 TYPE_7__* type_array_get_element (TYPE_1__*) ; 
 int /*<<< orphan*/  type_array_is_decl_as_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  type_basic_get_sign (TYPE_1__*) ; 
 int /*<<< orphan*/  type_basic_get_type (TYPE_1__*) ; 
 int type_get_type (TYPE_1__*) ; 
 scalar_t__ type_is_alias (TYPE_1__*) ; 

unsigned short get_type_vt(type_t *t)
{
  unsigned short vt;

  chat("get_type_vt: %p type->name %s\n", t, t->name);
  if (t->name) {
    vt = builtin_vt(t);
    if (vt) return vt;
  }

  if (type_is_alias(t) && is_attr(t->attrs, ATTR_PUBLIC))
    return VT_USERDEFINED;

  switch (type_get_type(t)) {
  case TYPE_BASIC:
    switch (type_basic_get_type(t)) {
    case TYPE_BASIC_BYTE:
      return VT_UI1;
    case TYPE_BASIC_CHAR:
    case TYPE_BASIC_INT8:
      if (type_basic_get_sign(t) > 0)
        return VT_UI1;
      else
        return VT_I1;
    case TYPE_BASIC_WCHAR:
      return VT_I2; /* mktyplib seems to parse wchar_t as short */
    case TYPE_BASIC_INT16:
      if (type_basic_get_sign(t) > 0)
        return VT_UI2;
      else
        return VT_I2;
    case TYPE_BASIC_INT:
      if (type_basic_get_sign(t) > 0)
        return VT_UINT;
      else
        return VT_INT;
    case TYPE_BASIC_INT32:
    case TYPE_BASIC_LONG:
    case TYPE_BASIC_ERROR_STATUS_T:
      if (type_basic_get_sign(t) > 0)
        return VT_UI4;
      else
        return VT_I4;
    case TYPE_BASIC_INT64:
    case TYPE_BASIC_HYPER:
      if (type_basic_get_sign(t) > 0)
        return VT_UI8;
      else
        return VT_I8;
    case TYPE_BASIC_INT3264:
      if (pointer_size == 8)
      {
        if (type_basic_get_sign(t) > 0)
          return VT_UI8;
        else
          return VT_I8;
      }
      else
      {
        if (type_basic_get_sign(t) > 0)
          return VT_UI4;
        else
          return VT_I4;
      }
    case TYPE_BASIC_FLOAT:
      return VT_R4;
    case TYPE_BASIC_DOUBLE:
      return VT_R8;
    case TYPE_BASIC_HANDLE:
      error("handles can't be used in typelibs\n");
    }
    break;

  case TYPE_POINTER:
    return VT_PTR;

  case TYPE_ARRAY:
    if (type_array_is_decl_as_ptr(t))
    {
      if (match(type_array_get_element(t)->name, "SAFEARRAY"))
        return VT_SAFEARRAY;
      return VT_PTR;
    }
    else
      return VT_CARRAY;

  case TYPE_INTERFACE:
    if(match(t->name, "IUnknown"))
      return VT_UNKNOWN;
    if(match(t->name, "IDispatch"))
      return VT_DISPATCH;
    return VT_USERDEFINED;

  case TYPE_ENUM:
  case TYPE_STRUCT:
  case TYPE_COCLASS:
  case TYPE_MODULE:
  case TYPE_UNION:
  case TYPE_ENCAPSULATED_UNION:
    return VT_USERDEFINED;

  case TYPE_VOID:
    return VT_VOID;

  case TYPE_ALIAS:
    /* aliases should be filtered out by the type_get_type call above */
    assert(0);
    break;

  case TYPE_FUNCTION:
    error("get_type_vt: functions not supported\n");
    break;

  case TYPE_BITFIELD:
    error("get_type_vt: bitfields not supported\n");
    break;
  }
  return 0;
}