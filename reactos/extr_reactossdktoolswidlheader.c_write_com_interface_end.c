#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char* c_name; char* name; int /*<<< orphan*/  namespace; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  UUID ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_DISPINTERFACE ; 
 int /*<<< orphan*/  ATTR_UUID ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_global_namespace (int /*<<< orphan*/ ) ; 
 TYPE_1__* type_iface_get_inherit (TYPE_1__*) ; 
 char* uuid_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  winrt_mode ; 
 int /*<<< orphan*/  write_c_disp_method_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  write_c_method_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  write_cpp_method_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  write_guid (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  write_inline_wrappers (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  write_line (int /*<<< orphan*/ *,int,char*,...) ; 
 int /*<<< orphan*/  write_locals (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_method_macro (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  write_method_proto (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  write_namespace_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_namespace_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uuid_decl (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void write_com_interface_end(FILE *header, type_t *iface)
{
  int dispinterface = is_attr(iface->attrs, ATTR_DISPINTERFACE);
  const UUID *uuid = get_attrp(iface->attrs, ATTR_UUID);
  type_t *type;

  if (uuid)
      write_guid(header, dispinterface ? "DIID" : "IID", iface->c_name, uuid);

  /* C++ interface */
  fprintf(header, "#if defined(__cplusplus) && !defined(CINTERFACE)\n");
  if (!is_global_namespace(iface->namespace)) {
      write_line(header, 0, "} /* extern \"C\" */");
      write_namespace_start(header, iface->namespace);
  }
  if (uuid) {
      write_line(header, 0, "MIDL_INTERFACE(\"%s\")", uuid_string(uuid));
      indent(header, 0);
  }else {
      indent(header, 0);
      fprintf(header, "interface ");
  }
  if (type_iface_get_inherit(iface))
  {
    fprintf(header, "%s : public %s\n", iface->name,
            type_iface_get_inherit(iface)->name);
    write_line(header, 1, "{");
  }
  else
  {
    fprintf(header, "%s\n", iface->name);
    write_line(header, 1, "{\n");
    write_line(header, 0, "BEGIN_INTERFACE\n");
  }
  /* dispinterfaces don't have real functions, so don't write C++ functions for
   * them */
  if (!dispinterface)
    write_cpp_method_def(header, iface);
  if (!type_iface_get_inherit(iface))
    write_line(header, 0, "END_INTERFACE\n");
  write_line(header, -1, "};");
  if (!is_global_namespace(iface->namespace)) {
      write_namespace_end(header, iface->namespace);
      write_line(header, 0, "extern \"C\" {");
  }
  if (uuid)
      write_uuid_decl(header, iface, uuid);
  fprintf(header, "#else\n");
  /* C interface */
  write_line(header, 1, "typedef struct %sVtbl {", iface->c_name);
  write_line(header, 0, "BEGIN_INTERFACE\n");
  if (dispinterface)
    write_c_disp_method_def(header, iface);
  else
    write_c_method_def(header, iface);
  write_line(header, 0, "END_INTERFACE");
  write_line(header, -1, "} %sVtbl;\n", iface->c_name);
  fprintf(header, "interface %s {\n", iface->c_name);
  fprintf(header, "    CONST_VTBL %sVtbl* lpVtbl;\n", iface->c_name);
  fprintf(header, "};\n\n");
  fprintf(header, "#ifdef COBJMACROS\n");
  /* dispinterfaces don't have real functions, so don't write macros for them,
   * only for the interface this interface inherits from, i.e. IDispatch */
  fprintf(header, "#ifndef WIDL_C_INLINE_WRAPPERS\n");
  type = dispinterface ? type_iface_get_inherit(iface) : iface;
  write_method_macro(header, type, type, iface->c_name);
  fprintf(header, "#else\n");
  write_inline_wrappers(header, type, type, iface->c_name);
  fprintf(header, "#endif\n");
  fprintf(header, "#endif\n");
  fprintf(header, "\n");
  fprintf(header, "#endif\n");
  fprintf(header, "\n");
  /* dispinterfaces don't have real functions, so don't write prototypes for
   * them */
  if (!dispinterface && !winrt_mode)
  {
    write_method_proto(header, iface);
    write_locals(header, iface, FALSE);
    fprintf(header, "\n");
  }
  fprintf(header,"#endif  /* __%s_%sINTERFACE_DEFINED__ */\n\n", iface->c_name, dispinterface ? "DISP" : "");
}