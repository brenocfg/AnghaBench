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
struct TYPE_6__ {char const* name; int /*<<< orphan*/  stmts; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ typelib_t ;
struct TYPE_7__ {int cval; } ;
typedef  TYPE_2__ expr_t ;
typedef  int /*<<< orphan*/  UUID ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CONTROL ; 
 int /*<<< orphan*/  ATTR_HELPSTRING ; 
 int /*<<< orphan*/  ATTR_HIDDEN ; 
 int /*<<< orphan*/  ATTR_ID ; 
 int /*<<< orphan*/  ATTR_LIBLCID ; 
 int /*<<< orphan*/  ATTR_RESTRICTED ; 
 int /*<<< orphan*/  ATTR_UUID ; 
 int /*<<< orphan*/  ATTR_VERSION ; 
 int /*<<< orphan*/  MAJORVERSION (unsigned int) ; 
 int /*<<< orphan*/  MINORVERSION (unsigned int) ; 
 int /*<<< orphan*/  add_output_to_resources (char*,char*) ; 
 int /*<<< orphan*/  format_uuid (int /*<<< orphan*/  const*) ; 
 void* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int get_attrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indent ; 
 scalar_t__ is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pointer_size ; 
 int /*<<< orphan*/  put_str (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strlen (char*) ; 
 char* typelib_name ; 
 int /*<<< orphan*/  write_coclasses (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  write_progids (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_typelib_interfaces (TYPE_1__ const*) ; 
 char* xmalloc (scalar_t__) ; 

void output_typelib_regscript( const typelib_t *typelib )
{
    const UUID *typelib_uuid = get_attrp( typelib->attrs, ATTR_UUID );
    const char *descr = get_attrp( typelib->attrs, ATTR_HELPSTRING );
    const expr_t *lcid_expr = get_attrp( typelib->attrs, ATTR_LIBLCID );
    unsigned int version = get_attrv( typelib->attrs, ATTR_VERSION );
    unsigned int flags = 0;
    char id_part[12] = "";
#ifndef __REACTOS__
    char *resname = typelib_name;
#endif
    expr_t *expr;

    if (is_attr( typelib->attrs, ATTR_RESTRICTED )) flags |= 1; /* LIBFLAG_FRESTRICTED */
    if (is_attr( typelib->attrs, ATTR_CONTROL )) flags |= 2; /* LIBFLAG_FCONTROL */
    if (is_attr( typelib->attrs, ATTR_HIDDEN )) flags |= 4; /* LIBFLAG_FHIDDEN */

    put_str( indent, "HKCR\n" );
    put_str( indent++, "{\n" );

    put_str( indent, "NoRemove Typelib\n" );
    put_str( indent++, "{\n" );
    put_str( indent, "NoRemove '%s'\n", format_uuid( typelib_uuid ));
    put_str( indent++, "{\n" );
    put_str( indent, "'%u.%u' = s '%s'\n",
             MAJORVERSION(version), MINORVERSION(version), descr ? descr : typelib->name );
    put_str( indent++, "{\n" );
    expr = get_attrp( typelib->attrs, ATTR_ID );
#ifdef __REACTOS__
    if (expr)
        sprintf(id_part, "\\%d", expr->cval);
#else
    if (expr)
    {
        sprintf(id_part, "\\%d", expr->cval);
        resname = xmalloc( strlen(typelib_name) + 20 );
        sprintf(resname, "%s\\%d", typelib_name, expr->cval);
    }
#endif
    put_str( indent, "'%x' { %s = s '%%MODULE%%%s' }\n",
             lcid_expr ? lcid_expr->cval : 0, pointer_size == 8 ? "win64" : "win32", id_part );
    put_str( indent, "FLAGS = s '%u'\n", flags );
    put_str( --indent, "}\n" );
    put_str( --indent, "}\n" );
    put_str( --indent, "}\n" );

    put_str( indent, "NoRemove Interface\n" );
    put_str( indent++, "{\n" );
    write_typelib_interfaces( typelib );
    put_str( --indent, "}\n" );

    put_str( indent, "NoRemove CLSID\n" );
    put_str( indent++, "{\n" );
    write_coclasses( typelib->stmts, typelib );
    put_str( --indent, "}\n" );

    write_progids( typelib->stmts );
    put_str( --indent, "}\n" );
#ifdef __REACTOS__
    add_output_to_resources( "WINE_REGISTRY", typelib_name );
#else
    add_output_to_resources( "WINE_REGISTRY", resname );
#endif
}