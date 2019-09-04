#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
struct TYPE_4__ {void* helpdir; void* tlbid; } ;
struct TYPE_5__ {TYPE_1__ typelib; } ;
struct entity {TYPE_2__ u; } ;
struct dll_redirect {int /*<<< orphan*/  entities; } ;
struct actctx_loader {TYPE_3__* actctx; } ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_6__ {int /*<<< orphan*/  sections; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TLIBREDIRECT_SECTION ; 
 scalar_t__ TRUE ; 
 struct entity* add_entity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asmv1W ; 
 int /*<<< orphan*/  flagsW ; 
 int /*<<< orphan*/  helpdirW ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ parse_expect_end_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_typelib_flags (int /*<<< orphan*/ *,struct entity*) ; 
 int /*<<< orphan*/  parse_typelib_version (int /*<<< orphan*/ *,struct entity*) ; 
 int /*<<< orphan*/  tlbidW ; 
 int /*<<< orphan*/  typelibW ; 
 int /*<<< orphan*/  versionW ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xmlstrdupW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL parse_typelib_elem(xmlbuf_t* xmlbuf, struct dll_redirect* dll, struct actctx_loader* acl)
{
    xmlstr_t    attr_name, attr_value;
    BOOL        end = FALSE, error;
    struct entity*      entity;
    UNICODE_STRING  attr_valueU, attr_nameU;

    if (!(entity = add_entity(&dll->entities, ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION)))
        return FALSE;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        if (xmlstr_cmp(&attr_name, tlbidW))
        {
            if (!(entity->u.typelib.tlbid = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, versionW))
        {
            if (!parse_typelib_version(&attr_value, entity)) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, helpdirW))
        {
            if (!(entity->u.typelib.helpdir = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, flagsW))
        {
            if (!parse_typelib_flags(&attr_value, entity)) return FALSE;
        }
        else
        {
            attr_nameU = xmlstr2unicode(&attr_name);
            attr_valueU = xmlstr2unicode(&attr_value);
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
        }
    }

    if (error) return FALSE;

    acl->actctx->sections |= TLIBREDIRECT_SECTION;

    if (end) return TRUE;

    return parse_expect_end_elem(xmlbuf, typelibW, asmv1W);
}