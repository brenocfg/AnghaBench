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
struct TYPE_3__ {char* name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  UUID ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_HELPSTRING ; 
 int /*<<< orphan*/  ATTR_PROGID ; 
 int /*<<< orphan*/  ATTR_UUID ; 
 int /*<<< orphan*/  ATTR_VIPROGID ; 
 int /*<<< orphan*/  format_uuid (int /*<<< orphan*/  const*) ; 
 void* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indent ; 
 int /*<<< orphan*/  put_str (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int write_progid( const type_t *class )
{
    const UUID *uuid = get_attrp( class->attrs, ATTR_UUID );
    const char *descr = get_attrp( class->attrs, ATTR_HELPSTRING );
    const char *progid = get_attrp( class->attrs, ATTR_PROGID );
    const char *vi_progid = get_attrp( class->attrs, ATTR_VIPROGID );

    if (!uuid) return 0;
    if (!descr) descr = class->name;

    if (progid)
    {
        put_str( indent, "'%s' = s '%s'\n", progid, descr );
        put_str( indent++, "{\n" );
        put_str( indent, "CLSID = s '%s'\n", format_uuid( uuid ) );
        put_str( --indent, "}\n" );
    }
    if (vi_progid)
    {
        put_str( indent, "'%s' = s '%s'\n", vi_progid, descr );
        put_str( indent++, "{\n" );
        put_str( indent, "CLSID = s '%s'\n", format_uuid( uuid ) );
        if (progid && strcmp( progid, vi_progid )) put_str( indent, "CurVer = s '%s'\n", progid );
        put_str( --indent, "}\n" );
    }
    return 1;
}