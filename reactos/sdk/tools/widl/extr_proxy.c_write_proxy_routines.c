#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* iface; } ;
struct TYPE_9__ {char* name; TYPE_2__ details; } ;
typedef  TYPE_3__ type_t ;
typedef  int /*<<< orphan*/  statement_list_t ;
struct TYPE_7__ {TYPE_3__* async_iface; } ;

/* Variables and functions */
 scalar_t__ MODE_Oif ; 
 scalar_t__ does_any_iface (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_delegation_indirect (TYPE_3__*,TYPE_3__ const**) ; 
 scalar_t__ get_stub_mode () ; 
 int /*<<< orphan*/  header_name ; 
 int /*<<< orphan*/  indent ; 
 int /*<<< orphan*/  need_proxy ; 
 int /*<<< orphan*/  need_proxy_and_inline_stubs ; 
 int pointer_size ; 
 int /*<<< orphan*/  print_proxy (char*,...) ; 
 int /*<<< orphan*/  proxy ; 
 char* proxy_token ; 
 TYPE_3__** sort_interfaces (int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  write_exceptions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_expr_eval_routine_list (int /*<<< orphan*/ ,char*) ; 
 int write_expr_eval_routines (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_formatstringsdecl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_procformatstring (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_proxy_stmts (int /*<<< orphan*/  const*,unsigned int*) ; 
 int /*<<< orphan*/  write_stubdesc (int) ; 
 int /*<<< orphan*/  write_stubdescproto () ; 
 int /*<<< orphan*/  write_typeformatstring (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_user_quad_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_proxy_routines(const statement_list_t *stmts)
{
  int expr_eval_routines;
  unsigned int proc_offset = 0;
  char *file_id = proxy_token;
  int i, count, have_baseiid = 0;
  unsigned int table_version;
  type_t **interfaces;
  const type_t * delegate_to;

  print_proxy( "#ifndef __REDQ_RPCPROXY_H_VERSION__\n");
  print_proxy( "#define __REQUIRED_RPCPROXY_H_VERSION__ %u\n", get_stub_mode() == MODE_Oif ? 475 : 440);
  print_proxy( "#endif\n");
  print_proxy( "\n");
  if (get_stub_mode() == MODE_Oif) print_proxy( "#define USE_STUBLESS_PROXY\n");
  print_proxy( "#include \"rpcproxy.h\"\n");
  print_proxy( "#ifndef __RPCPROXY_H_VERSION__\n");
  print_proxy( "#error This code needs a newer version of rpcproxy.h\n");
  print_proxy( "#endif /* __RPCPROXY_H_VERSION__ */\n");
  print_proxy( "\n");
  print_proxy( "#include \"%s\"\n", header_name);
  print_proxy( "\n");

  if (does_any_iface(stmts, need_proxy_and_inline_stubs))
  {
      write_exceptions( proxy );
      print_proxy( "\n");
      print_proxy( "struct __proxy_frame\n");
      print_proxy( "{\n");
      print_proxy( "    __DECL_EXCEPTION_FRAME\n");
      print_proxy( "    MIDL_STUB_MESSAGE _StubMsg;\n");
      print_proxy( "    void             *This;\n");
      print_proxy( "};\n");
      print_proxy( "\n");
      print_proxy("static int __proxy_filter( struct __proxy_frame *__frame )\n");
      print_proxy( "{\n");
      print_proxy( "    return (__frame->_StubMsg.dwStubPhase != PROXY_SENDRECEIVE);\n");
      print_proxy( "}\n");
      print_proxy( "\n");
  }

  write_formatstringsdecl(proxy, indent, stmts, need_proxy);
  write_stubdescproto();
  write_proxy_stmts(stmts, &proc_offset);

  expr_eval_routines = write_expr_eval_routines(proxy, proxy_token);
  if (expr_eval_routines)
      write_expr_eval_routine_list(proxy, proxy_token);
  write_user_quad_list(proxy);
  write_stubdesc(expr_eval_routines);

  print_proxy( "#if !defined(__RPC_WIN%u__)\n", pointer_size == 8 ? 64 : 32);
  print_proxy( "#error Invalid build platform for this proxy.\n");
  print_proxy( "#endif\n");
  print_proxy( "\n");
  write_procformatstring(proxy, stmts, need_proxy);
  write_typeformatstring(proxy, stmts, need_proxy);

  interfaces = sort_interfaces(stmts, &count);
  fprintf(proxy, "static const CInterfaceProxyVtbl* const _%s_ProxyVtblList[] =\n", file_id);
  fprintf(proxy, "{\n");
  for (i = 0; i < count; i++)
      fprintf(proxy, "    (const CInterfaceProxyVtbl*)&_%sProxyVtbl,\n", interfaces[i]->name);
  fprintf(proxy, "    0\n");
  fprintf(proxy, "};\n");
  fprintf(proxy, "\n");

  fprintf(proxy, "static const CInterfaceStubVtbl* const _%s_StubVtblList[] =\n", file_id);
  fprintf(proxy, "{\n");
  for (i = 0; i < count; i++)
      fprintf(proxy, "    &_%sStubVtbl,\n", interfaces[i]->name);
  fprintf(proxy, "    0\n");
  fprintf(proxy, "};\n");
  fprintf(proxy, "\n");

  fprintf(proxy, "static PCInterfaceName const _%s_InterfaceNamesList[] =\n", file_id);
  fprintf(proxy, "{\n");
  for (i = 0; i < count; i++)
      fprintf(proxy, "    \"%s\",\n", interfaces[i]->name);
  fprintf(proxy, "    0\n");
  fprintf(proxy, "};\n");
  fprintf(proxy, "\n");

  for (i = 0; i < count; i++)
      if ((have_baseiid = get_delegation_indirect( interfaces[i], NULL ))) break;

  if (have_baseiid)
  {
      fprintf(proxy, "static const IID * _%s_BaseIIDList[] =\n", file_id);
      fprintf(proxy, "{\n");
      for (i = 0; i < count; i++)
      {
          if (get_delegation_indirect(interfaces[i], &delegate_to))
              fprintf( proxy, "    &IID_%s,  /* %s */\n", delegate_to->name, interfaces[i]->name );
          else
              fprintf( proxy, "    0,\n" );
      }
      fprintf(proxy, "    0\n");
      fprintf(proxy, "};\n");
      fprintf(proxy, "\n");
  }

  fprintf(proxy, "static int __stdcall _%s_IID_Lookup(const IID* pIID, int* pIndex)\n", file_id);
  fprintf(proxy, "{\n");
  fprintf(proxy, "    int low = 0, high = %d;\n", count - 1);
  fprintf(proxy, "\n");
  fprintf(proxy, "    while (low <= high)\n");
  fprintf(proxy, "    {\n");
  fprintf(proxy, "        int pos = (low + high) / 2;\n");
  fprintf(proxy, "        int res = IID_GENERIC_CHECK_IID(_%s, pIID, pos);\n", file_id);
  fprintf(proxy, "        if (!res) { *pIndex = pos; return 1; }\n");
  fprintf(proxy, "        if (res > 0) low = pos + 1;\n");
  fprintf(proxy, "        else high = pos - 1;\n");
  fprintf(proxy, "    }\n");
  fprintf(proxy, "    return 0;\n");
  fprintf(proxy, "}\n");
  fprintf(proxy, "\n");

  table_version = get_stub_mode() == MODE_Oif ? 2 : 1;
  for (i = 0; i < count; i++)
  {
      if (interfaces[i]->details.iface->async_iface != interfaces[i]) continue;
      if (table_version != 6)
      {
          fprintf(proxy, "static const IID *_AsyncInterfaceTable[] =\n");
          fprintf(proxy, "{\n");
          table_version = 6;
      }
      fprintf(proxy, "    &IID_%s,\n", interfaces[i]->name);
      fprintf(proxy, "    (IID*)(LONG_PTR)-1,\n");
  }
  if (table_version == 6)
  {
      fprintf(proxy, "    0\n");
      fprintf(proxy, "};\n");
      fprintf(proxy, "\n");
  }

  fprintf(proxy, "const ExtendedProxyFileInfo %s_ProxyFileInfo DECLSPEC_HIDDEN =\n", file_id);
  fprintf(proxy, "{\n");
  fprintf(proxy, "    (const PCInterfaceProxyVtblList*)_%s_ProxyVtblList,\n", file_id);
  fprintf(proxy, "    (const PCInterfaceStubVtblList*)_%s_StubVtblList,\n", file_id);
  fprintf(proxy, "    _%s_InterfaceNamesList,\n", file_id);
  if (have_baseiid) fprintf(proxy, "    _%s_BaseIIDList,\n", file_id);
  else fprintf(proxy, "    0,\n");
  fprintf(proxy, "    _%s_IID_Lookup,\n", file_id);
  fprintf(proxy, "    %d,\n", count);
  fprintf(proxy, "    %u,\n", table_version);
  fprintf(proxy, "    %s,\n", table_version == 6 ? "_AsyncInterfaceTable" : "0");
  fprintf(proxy, "    0,\n");
  fprintf(proxy, "    0,\n");
  fprintf(proxy, "    0\n");
  fprintf(proxy, "};\n");
}