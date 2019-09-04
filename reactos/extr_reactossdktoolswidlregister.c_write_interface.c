#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  UUID ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_UUID ; 
 int /*<<< orphan*/  count_methods (TYPE_1__ const*) ; 
 int /*<<< orphan*/  format_uuid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indent ; 
 scalar_t__ is_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object (TYPE_1__ const*) ; 
 int /*<<< orphan*/  put_str (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  type_iface_get_inherit (TYPE_1__ const*) ; 

__attribute__((used)) static void write_interface( const type_t *iface, const type_t *ps_factory )
{
    const UUID *uuid = get_attrp( iface->attrs, ATTR_UUID );
    const UUID *ps_uuid = get_attrp( ps_factory->attrs, ATTR_UUID );

    if (!uuid) return;
    if (!is_object( iface )) return;
    if (!type_iface_get_inherit(iface)) /* special case for IUnknown */
    {
        put_str( indent, "'%s' = s '%s'\n", format_uuid( uuid ), iface->name );
        return;
    }
    if (is_local( iface->attrs )) return;
    put_str( indent, "'%s' = s '%s'\n", format_uuid( uuid ), iface->name );
    put_str( indent, "{\n" );
    indent++;
    put_str( indent, "NumMethods = s %u\n", count_methods( iface ));
    put_str( indent, "ProxyStubClsid32 = s '%s'\n", format_uuid( ps_uuid ));
    indent--;
    put_str( indent, "}\n" );
}