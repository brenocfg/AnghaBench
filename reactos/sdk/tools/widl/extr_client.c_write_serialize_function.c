#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int typestring_offset; char* name; } ;
typedef  TYPE_1__ type_t ;
typedef  enum stub_mode { ____Placeholder_stub_mode } stub_mode ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MODE_Os ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int get_stub_mode () ; 
 int /*<<< orphan*/  warning (char*,char*) ; 

__attribute__((used)) static void write_serialize_function(FILE *file, const type_t *type, const type_t *iface,
                                     const char *func_name, const char *ret_type)
{
    enum stub_mode mode = get_stub_mode();
    static int emited_pickling_info;

    if (iface && !type->typestring_offset)
    {
        /* FIXME: Those are mostly basic types. They should be implemented
         * using NdrMesSimpleType* functions */
        if (ret_type) warning("Serialization of type %s is not supported\n", type->name);
        return;
    }

    if (!emited_pickling_info && iface && mode != MODE_Os)
    {
        fprintf(file, "static const MIDL_TYPE_PICKLING_INFO __MIDL_TypePicklingInfo =\n");
        fprintf(file, "{\n");
        fprintf(file, "    0x33205054,\n");
        fprintf(file, "    0x3,\n");
        fprintf(file, "    0,\n");
        fprintf(file, "    0,\n");
        fprintf(file, "    0\n");
        fprintf(file, "};\n");
        fprintf(file, "\n");
        emited_pickling_info = 1;
    }

    /* FIXME: Assuming explicit handle */

    fprintf(file, "%s __cdecl %s_%s(handle_t IDL_handle, %s *IDL_type)%s\n",
            ret_type ? ret_type : "void", type->name, func_name, type->name, iface ? "" : ";");
    if (!iface) return; /* declaration only */

    fprintf(file, "{\n");
    fprintf(file, "    %sNdrMesType%s%s(\n", ret_type ? "return " : "", func_name,
            mode != MODE_Os ? "2" : "");
    fprintf(file, "        IDL_handle,\n");
    if (mode != MODE_Os)
        fprintf(file, "        (MIDL_TYPE_PICKLING_INFO*)&__MIDL_TypePicklingInfo,\n");
    fprintf(file, "        &%s_StubDesc,\n", iface->name);
    fprintf(file, "        (PFORMAT_STRING)&__MIDL_TypeFormatString.Format[%u],\n",
            type->typestring_offset);
    fprintf(file, "        IDL_type);\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");
}