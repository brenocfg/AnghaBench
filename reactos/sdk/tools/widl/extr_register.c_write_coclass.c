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
struct TYPE_7__ {char* name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_2__ type_t ;
typedef  int /*<<< orphan*/  UUID ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_HELPSTRING ; 
 int /*<<< orphan*/  ATTR_PROGID ; 
 int /*<<< orphan*/  ATTR_UUID ; 
 int /*<<< orphan*/  ATTR_VERSION ; 
 int /*<<< orphan*/  ATTR_VIPROGID ; 
 int /*<<< orphan*/  MAJORVERSION (unsigned int) ; 
 int /*<<< orphan*/  MINORVERSION (unsigned int) ; 
 int /*<<< orphan*/  format_uuid (int /*<<< orphan*/  const*) ; 
 void* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int get_attrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* get_coclass_threading (TYPE_2__ const*) ; 
 int /*<<< orphan*/  indent ; 
 int /*<<< orphan*/  put_str (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int write_coclass( const type_t *class, const typelib_t *typelib )
{
    const UUID *uuid = get_attrp( class->attrs, ATTR_UUID );
    const char *descr = get_attrp( class->attrs, ATTR_HELPSTRING );
    const char *progid = get_attrp( class->attrs, ATTR_PROGID );
    const char *vi_progid = get_attrp( class->attrs, ATTR_VIPROGID );
    const char *threading = get_coclass_threading( class );
    unsigned int version = get_attrv( class->attrs, ATTR_VERSION );

    if (!uuid) return 0;
    if (typelib && !threading && !progid) return 0;
    if (!descr) descr = class->name;

    put_str( indent, "'%s' = s '%s'\n", format_uuid( uuid ), descr );
    put_str( indent++, "{\n" );
    if (threading) put_str( indent, "InprocServer32 = s '%%MODULE%%' { val ThreadingModel = s '%s' }\n",
                            threading );
    if (progid) put_str( indent, "ProgId = s '%s'\n", progid );
    if (typelib)
    {
        const UUID *typelib_uuid = get_attrp( typelib->attrs, ATTR_UUID );
        put_str( indent, "TypeLib = s '%s'\n", format_uuid( typelib_uuid ));
        if (!version) version = get_attrv( typelib->attrs, ATTR_VERSION );
    }
    if (version) put_str( indent, "Version = s '%u.%u'\n", MAJORVERSION(version), MINORVERSION(version) );
    if (vi_progid) put_str( indent, "VersionIndependentProgId = s '%s'\n", vi_progid );
    put_str( --indent, "}\n" );
    return 1;
}