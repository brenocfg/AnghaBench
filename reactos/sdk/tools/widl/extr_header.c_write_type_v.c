#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  var_list_t ;
struct TYPE_13__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CALLCONV ; 
 int /*<<< orphan*/  ATTR_INLINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NAME_DEFAULT ; 
 scalar_t__ TYPE_FUNCTION ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 char* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_interface ; 
 scalar_t__ is_ptr (TYPE_1__*) ; 
 scalar_t__ needs_space_after (TYPE_1__*) ; 
 int /*<<< orphan*/ * type_function_get_args (TYPE_1__*) ; 
 TYPE_1__* type_function_get_rettype (TYPE_1__*) ; 
 scalar_t__ type_get_type_detect_alias (TYPE_1__*) ; 
 TYPE_1__* type_pointer_get_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  write_args (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_type_left (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_type_right (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static void write_type_v(FILE *h, type_t *t, int is_field, int declonly, const char *name)
{
  type_t *pt = NULL;
  int ptr_level = 0;

  if (!h) return;

  if (t) {
    for (pt = t; is_ptr(pt); pt = type_pointer_get_ref(pt), ptr_level++)
      ;

    if (type_get_type_detect_alias(pt) == TYPE_FUNCTION) {
      int i;
      const char *callconv = get_attrp(pt->attrs, ATTR_CALLCONV);
      if (!callconv && is_object_interface) callconv = "STDMETHODCALLTYPE";
      if (is_attr(pt->attrs, ATTR_INLINE)) fprintf(h, "inline ");
      write_type_left(h, type_function_get_rettype(pt), NAME_DEFAULT, declonly);
      fputc(' ', h);
      if (ptr_level) fputc('(', h);
      if (callconv) fprintf(h, "%s ", callconv);
      for (i = 0; i < ptr_level; i++)
        fputc('*', h);
    } else
      write_type_left(h, t, NAME_DEFAULT, declonly);
  }

  if (name) fprintf(h, "%s%s", !t || needs_space_after(t) ? " " : "", name );

  if (t) {
    if (type_get_type_detect_alias(pt) == TYPE_FUNCTION) {
      const var_list_t *args = type_function_get_args(pt);

      if (ptr_level) fputc(')', h);
      fputc('(', h);
      if (args)
          write_args(h, args, NULL, 0, FALSE);
      else
          fprintf(h, "void");
      fputc(')', h);
    } else
      write_type_right(h, t, is_field);
  }
}