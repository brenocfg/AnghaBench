#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ typelib_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_2__ type_t ;
typedef  int /*<<< orphan*/  UUID ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_DISPINTERFACE ; 
 int /*<<< orphan*/  ATTR_OLEAUTOMATION ; 
 int /*<<< orphan*/  ATTR_UUID ; 
 int /*<<< orphan*/  ATTR_VERSION ; 
 int /*<<< orphan*/  MAJORVERSION (unsigned int) ; 
 int /*<<< orphan*/  MINORVERSION (unsigned int) ; 
 int /*<<< orphan*/  format_uuid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int get_attrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indent ; 
 int /*<<< orphan*/  is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object (TYPE_2__ const*) ; 
 int /*<<< orphan*/  put_str (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void write_typelib_interface( const type_t *iface, const typelib_t *typelib )
{
    const UUID *typelib_uuid = get_attrp( typelib->attrs, ATTR_UUID );
    const UUID *uuid = get_attrp( iface->attrs, ATTR_UUID );
    unsigned int version = get_attrv( typelib->attrs, ATTR_VERSION );

    if (!uuid) return;
    if (!is_object( iface )) return;
    if (!is_attr( iface->attrs, ATTR_OLEAUTOMATION ) && !is_attr( iface->attrs, ATTR_DISPINTERFACE ))
        return;
    put_str( indent, "'%s' = s '%s'\n", format_uuid( uuid ), iface->name );
    put_str( indent, "{\n" );
    indent++;
    put_str( indent, "ProxyStubClsid = s '{00020424-0000-0000-C000-000000000046}'\n" );
    put_str( indent, "ProxyStubClsid32 = s '{00020424-0000-0000-C000-000000000046}'\n" );
    if (version)
        put_str( indent, "TypeLib = s '%s' { val Version = s '%u.%u' }\n",
                 format_uuid( typelib_uuid ), MAJORVERSION(version), MINORVERSION(version) );
    else
        put_str( indent, "TypeLib = s '%s'", format_uuid( typelib_uuid ));
    indent--;
    put_str( indent, "}\n" );
}