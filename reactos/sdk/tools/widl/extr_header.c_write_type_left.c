#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {char* name; int /*<<< orphan*/  attrs; void* written; int /*<<< orphan*/  defined; int /*<<< orphan*/  namespace; } ;
typedef  TYPE_1__ type_t ;
typedef  enum name_type { ____Placeholder_name_type } name_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CONST ; 
 void* TRUE ; 
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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  indent (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  indentation ; 
 scalar_t__ is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_global_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ptr (TYPE_1__*) ; 
 TYPE_1__* type_array_get_element (TYPE_1__*) ; 
 int /*<<< orphan*/  type_array_is_decl_as_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  type_basic_get_sign (TYPE_1__*) ; 
 int type_basic_get_type (TYPE_1__*) ; 
 TYPE_1__* type_bitfield_get_field (TYPE_1__*) ; 
 int /*<<< orphan*/  type_encapsulated_union_get_fields (TYPE_1__*) ; 
 int /*<<< orphan*/  type_enum_get_values (TYPE_1__*) ; 
 char* type_get_name (TYPE_1__*,int) ; 
 int const type_get_type (TYPE_1__*) ; 
 int type_get_type_detect_alias (TYPE_1__*) ; 
 scalar_t__ type_is_alias (TYPE_1__*) ; 
 TYPE_1__* type_pointer_get_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  type_struct_get_fields (TYPE_1__*) ; 
 int /*<<< orphan*/  type_union_get_cases (TYPE_1__*) ; 
 int /*<<< orphan*/  write_enums (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_fields (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pointer_left (int /*<<< orphan*/ *,TYPE_1__*) ; 

void write_type_left(FILE *h, type_t *t, enum name_type name_type, int declonly)
{
  const char *name;

  if (!h) return;

  name = type_get_name(t, name_type);

  if (is_attr(t->attrs, ATTR_CONST) &&
      (type_is_alias(t) || !is_ptr(t)))
    fprintf(h, "const ");

  if (type_is_alias(t)) fprintf(h, "%s", t->name);
  else {
    switch (type_get_type_detect_alias(t)) {
      case TYPE_ENUM:
        if (!declonly && t->defined && !t->written) {
          if (name) fprintf(h, "enum %s {\n", name);
          else fprintf(h, "enum {\n");
          t->written = TRUE;
          indentation++;
          write_enums(h, type_enum_get_values(t), is_global_namespace(t->namespace) ? NULL : t->name);
          indent(h, -1);
          fprintf(h, "}");
        }
        else fprintf(h, "enum %s", name ? name : "");
        break;
      case TYPE_STRUCT:
      case TYPE_ENCAPSULATED_UNION:
        if (!declonly && t->defined && !t->written) {
          if (name) fprintf(h, "struct %s {\n", name);
          else fprintf(h, "struct {\n");
          t->written = TRUE;
          indentation++;
          if (type_get_type(t) != TYPE_STRUCT)
            write_fields(h, type_encapsulated_union_get_fields(t));
          else
            write_fields(h, type_struct_get_fields(t));
          indent(h, -1);
          fprintf(h, "}");
        }
        else fprintf(h, "struct %s", name ? name : "");
        break;
      case TYPE_UNION:
        if (!declonly && t->defined && !t->written) {
          if (t->name) fprintf(h, "union %s {\n", t->name);
          else fprintf(h, "union {\n");
          t->written = TRUE;
          indentation++;
          write_fields(h, type_union_get_cases(t));
          indent(h, -1);
          fprintf(h, "}");
        }
        else fprintf(h, "union %s", t->name ? t->name : "");
        break;
      case TYPE_POINTER:
      {
        write_type_left(h, type_pointer_get_ref(t), name_type, declonly);
        write_pointer_left(h, type_pointer_get_ref(t));
        if (is_attr(t->attrs, ATTR_CONST)) fprintf(h, "const ");
        break;
      }
      case TYPE_ARRAY:
        if (t->name && type_array_is_decl_as_ptr(t))
          fprintf(h, "%s", t->name);
        else
        {
          write_type_left(h, type_array_get_element(t), name_type, declonly);
          if (type_array_is_decl_as_ptr(t))
            write_pointer_left(h, type_array_get_element(t));
        }
        break;
      case TYPE_BASIC:
        if (type_basic_get_type(t) != TYPE_BASIC_INT32 &&
            type_basic_get_type(t) != TYPE_BASIC_INT64 &&
            type_basic_get_type(t) != TYPE_BASIC_LONG &&
            type_basic_get_type(t) != TYPE_BASIC_HYPER)
        {
          if (type_basic_get_sign(t) < 0) fprintf(h, "signed ");
          else if (type_basic_get_sign(t) > 0) fprintf(h, "unsigned ");
        }
        switch (type_basic_get_type(t))
        {
        case TYPE_BASIC_INT8: fprintf(h, "small"); break;
        case TYPE_BASIC_INT16: fprintf(h, "short"); break;
        case TYPE_BASIC_INT: fprintf(h, "int"); break;
        case TYPE_BASIC_INT3264: fprintf(h, "__int3264"); break;
        case TYPE_BASIC_BYTE: fprintf(h, "byte"); break;
        case TYPE_BASIC_CHAR: fprintf(h, "char"); break;
        case TYPE_BASIC_WCHAR: fprintf(h, "wchar_t"); break;
        case TYPE_BASIC_FLOAT: fprintf(h, "float"); break;
        case TYPE_BASIC_DOUBLE: fprintf(h, "double"); break;
        case TYPE_BASIC_ERROR_STATUS_T: fprintf(h, "error_status_t"); break;
        case TYPE_BASIC_HANDLE: fprintf(h, "handle_t"); break;
        case TYPE_BASIC_INT32:
          if (type_basic_get_sign(t) > 0)
            fprintf(h, "UINT32");
          else
            fprintf(h, "INT32");
          break;
        case TYPE_BASIC_LONG:
          if (type_basic_get_sign(t) > 0)
            fprintf(h, "ULONG");
          else
            fprintf(h, "LONG");
          break;
        case TYPE_BASIC_INT64:
          if (type_basic_get_sign(t) > 0)
            fprintf(h, "UINT64");
          else
            fprintf(h, "INT64");
          break;
        case TYPE_BASIC_HYPER:
          if (type_basic_get_sign(t) > 0)
            fprintf(h, "MIDL_uhyper");
          else
            fprintf(h, "hyper");
          break;
        }
        break;
      case TYPE_INTERFACE:
      case TYPE_MODULE:
      case TYPE_COCLASS:
        fprintf(h, "%s", t->name);
        break;
      case TYPE_VOID:
        fprintf(h, "void");
        break;
      case TYPE_BITFIELD:
        write_type_left(h, type_bitfield_get_field(t), name_type, declonly);
        break;
      case TYPE_ALIAS:
      case TYPE_FUNCTION:
        /* handled elsewhere */
        assert(0);
        break;
    }
  }
}