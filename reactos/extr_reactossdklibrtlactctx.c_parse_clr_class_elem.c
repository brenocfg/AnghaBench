#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
struct TYPE_5__ {scalar_t__ num; } ;
struct TYPE_6__ {TYPE_1__ progids; void* progid; void* version; int /*<<< orphan*/  model; void* tlbid; void* clsid; void* name; } ;
struct TYPE_7__ {TYPE_2__ comclass; } ;
struct entity {TYPE_3__ u; } ;
struct assembly {int /*<<< orphan*/  entities; } ;
struct actctx_loader {TYPE_4__* actctx; } ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_8__ {int /*<<< orphan*/  sections; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,...) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PROGIDREDIRECT_SECTION ; 
 int /*<<< orphan*/  SERVERREDIRECT_SECTION ; 
 scalar_t__ TRUE ; 
 struct entity* add_entity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clrClassW ; 
 int /*<<< orphan*/  clsidW ; 
 int /*<<< orphan*/  g_nameW ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ next_xml_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_com_class_progid (int /*<<< orphan*/ *,struct entity*) ; 
 int /*<<< orphan*/  parse_com_class_threadingmodel (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_end_element (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_unknown_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  progidW ; 
 int /*<<< orphan*/  runtimeVersionW ; 
 int /*<<< orphan*/  threadingmodelW ; 
 int /*<<< orphan*/  tlbidW ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlstr_cmp_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xmlstrdupW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL parse_clr_class_elem(xmlbuf_t* xmlbuf, struct assembly* assembly, struct actctx_loader *acl)
{
    xmlstr_t    attr_name, attr_value, elem;
    BOOL        end = FALSE, error, ret = TRUE;
    struct entity*      entity;

    entity = add_entity(&assembly->entities, ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION);
    if (!entity) return FALSE;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        if (xmlstr_cmp(&attr_name, g_nameW))
        {
            if (!(entity->u.comclass.name = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, clsidW))
        {
            if (!(entity->u.comclass.clsid = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, progidW))
        {
            if (!(entity->u.comclass.progid = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, tlbidW))
        {
            if (!(entity->u.comclass.tlbid = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, threadingmodelW))
        {
            entity->u.comclass.model = parse_com_class_threadingmodel(&attr_value);
        }
        else if (xmlstr_cmp(&attr_name, runtimeVersionW))
        {
            if (!(entity->u.comclass.version = xmlstrdupW(&attr_value))) return FALSE;
        }
        else
        {
            UNICODE_STRING attr_nameU, attr_valueU;
            attr_nameU = xmlstr2unicode(&attr_name);
            attr_valueU = xmlstr2unicode(&attr_value);
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
        }
    }

    if (error) return FALSE;
    acl->actctx->sections |= SERVERREDIRECT_SECTION;
    if (entity->u.comclass.progid)
        acl->actctx->sections |= PROGIDREDIRECT_SECTION;
    if (end) return TRUE;

    while (ret && (ret = next_xml_elem(xmlbuf, &elem)))
    {
        if (xmlstr_cmp_end(&elem, clrClassW))
        {
            ret = parse_end_element(xmlbuf);
            break;
        }
        else if (xmlstr_cmp(&elem, progidW))
        {
            ret = parse_com_class_progid(xmlbuf, entity);
        }
        else
        {
            UNICODE_STRING elemU = xmlstr2unicode(&elem);
            DPRINT1("unknown elem %wZ\n", &elemU);
            ret = parse_unknown_elem(xmlbuf, &elem);
        }
    }

    if (entity->u.comclass.progids.num)
        acl->actctx->sections |= PROGIDREDIRECT_SECTION;

    return ret;
}