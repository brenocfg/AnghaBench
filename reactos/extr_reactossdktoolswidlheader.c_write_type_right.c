#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type_t ;
struct TYPE_2__ {int cval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FALSE ; 
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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  is_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_conformant_array (int /*<<< orphan*/ *) ; 
 int type_array_get_dim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_array_get_element (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_array_is_decl_as_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__* type_bitfield_get_bits (int /*<<< orphan*/ *) ; 
 int type_get_type (int /*<<< orphan*/ *) ; 
 scalar_t__ type_is_alias (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_pointer_get_ref (int /*<<< orphan*/ *) ; 

void write_type_right(FILE *h, type_t *t, int is_field)
{
  if (!h) return;
  if (type_is_alias(t)) return;

  switch (type_get_type(t))
  {
  case TYPE_ARRAY:
  {
    type_t *elem = type_array_get_element(t);
    if (type_array_is_decl_as_ptr(t))
    {
      if (!type_is_alias(elem) && is_array(elem) && !type_array_is_decl_as_ptr(elem))
        fprintf(h, ")");
    }
    else
    {
      if (is_conformant_array(t))
        fprintf(h, "[%s]", is_field ? "1" : "");
      else
        fprintf(h, "[%u]", type_array_get_dim(t));
    }
    write_type_right(h, elem, FALSE);
    break;
  }
  case TYPE_POINTER:
  {
    type_t *ref = type_pointer_get_ref(t);
    if (!type_is_alias(ref) && is_array(ref) && !type_array_is_decl_as_ptr(ref))
      fprintf(h, ")");
    write_type_right(h, ref, FALSE);
    break;
  }
  case TYPE_BITFIELD:
    fprintf(h, " : %u", type_bitfield_get_bits(t)->cval);
    break;
  case TYPE_VOID:
  case TYPE_BASIC:
  case TYPE_ENUM:
  case TYPE_STRUCT:
  case TYPE_ENCAPSULATED_UNION:
  case TYPE_UNION:
  case TYPE_ALIAS:
  case TYPE_MODULE:
  case TYPE_COCLASS:
  case TYPE_FUNCTION:
  case TYPE_INTERFACE:
    break;
  }
}