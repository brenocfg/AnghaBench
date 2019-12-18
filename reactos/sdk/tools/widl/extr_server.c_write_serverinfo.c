#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  indent ; 
 int /*<<< orphan*/  print_server (char*,...) ; 

__attribute__((used)) static void write_serverinfo(type_t *iface)
{
    print_server( "static const MIDL_SERVER_INFO %s_ServerInfo =\n", iface->name );
    print_server( "{\n" );
    indent++;
    print_server( "&%s_StubDesc,\n", iface->name );
    print_server( "%s_ServerRoutineTable,\n", iface->name );
    print_server( "__MIDL_ProcFormatString.Format,\n" );
    print_server( "%s_FormatStringOffsetTable,\n", iface->name );
    print_server( "0,\n" );
    print_server( "0,\n" );
    print_server( "0,\n" );
    print_server( "0\n" );
    indent--;
    print_server( "};\n\n" );
}