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
struct TYPE_6__ {TYPE_1__ progids; void* progid; void* miscstatusdocprint; void* miscstatusicon; void* miscstatusthumbnail; void* miscstatuscontent; void* miscstatus; int /*<<< orphan*/  model; void* tlbid; void* clsid; } ;
struct TYPE_7__ {TYPE_2__ comclass; } ;
struct entity {TYPE_3__ u; } ;
struct dll_redirect {int /*<<< orphan*/  entities; } ;
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
 int /*<<< orphan*/  clsidW ; 
 int /*<<< orphan*/  comClassW ; 
 int /*<<< orphan*/  descriptionW ; 
 int /*<<< orphan*/  miscstatusW ; 
 int /*<<< orphan*/  miscstatuscontentW ; 
 int /*<<< orphan*/  miscstatusdocprintW ; 
 int /*<<< orphan*/  miscstatusiconW ; 
 int /*<<< orphan*/  miscstatusthumbnailW ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ next_xml_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* parse_com_class_misc (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_com_class_progid (int /*<<< orphan*/ *,struct entity*) ; 
 int /*<<< orphan*/  parse_com_class_threadingmodel (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_end_element (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_unknown_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  progidW ; 
 int /*<<< orphan*/  threadingmodelW ; 
 int /*<<< orphan*/  tlbidW ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlstr_cmp_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xmlstrdupW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL parse_com_class_elem(xmlbuf_t* xmlbuf, struct dll_redirect* dll, struct actctx_loader *acl)
{
    xmlstr_t elem, attr_name, attr_value;
    BOOL ret = TRUE, end = FALSE, error;
    struct entity*      entity;
    UNICODE_STRING  attr_valueU, attr_nameU;

    if (!(entity = add_entity(&dll->entities, ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION)))
        return FALSE;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        if (xmlstr_cmp(&attr_name, clsidW))
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
        else if (xmlstr_cmp(&attr_name, miscstatusW))
        {
            entity->u.comclass.miscstatus = parse_com_class_misc(&attr_value);
        }
        else if (xmlstr_cmp(&attr_name, miscstatuscontentW))
        {
            entity->u.comclass.miscstatuscontent = parse_com_class_misc(&attr_value);
        }
        else if (xmlstr_cmp(&attr_name, miscstatusthumbnailW))
        {
            entity->u.comclass.miscstatusthumbnail = parse_com_class_misc(&attr_value);
        }
        else if (xmlstr_cmp(&attr_name, miscstatusiconW))
        {
            entity->u.comclass.miscstatusicon = parse_com_class_misc(&attr_value);
        }
        else if (xmlstr_cmp(&attr_name, miscstatusdocprintW))
        {
            entity->u.comclass.miscstatusdocprint = parse_com_class_misc(&attr_value);
        }
        else if (xmlstr_cmp(&attr_name, descriptionW))
        {
            /* not stored */
        }
        else
        {
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
        if (xmlstr_cmp_end(&elem, comClassW))
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
            attr_nameU = xmlstr2unicode(&elem);
            DPRINT1("unknown elem %wZ\n", &attr_nameU);
            ret = parse_unknown_elem(xmlbuf, &elem);
        }
    }

    if (entity->u.comclass.progids.num)
        acl->actctx->sections |= PROGIDREDIRECT_SECTION;

    return ret;
}