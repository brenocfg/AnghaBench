#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlstr_t ;
struct TYPE_8__ {scalar_t__ ptr; scalar_t__ end; } ;
typedef  TYPE_2__ xmlbuf_t ;
struct assembly_identity {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  info; } ;
struct assembly {TYPE_1__ manifest; } ;
struct actctx_loader {int dummy; } ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_SXS_CANT_GEN_ACTCTX ; 
 int /*<<< orphan*/  asmv1W ; 
 int /*<<< orphan*/  assemblyW ; 
 int /*<<< orphan*/  g_xmlW ; 
 scalar_t__ next_xml_elem (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_assembly_elem (TYPE_2__*,struct actctx_loader*,struct assembly*,struct assembly_identity*) ; 
 int /*<<< orphan*/  parse_xml_header (TYPE_2__*) ; 
 int /*<<< orphan*/  xml_elem_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS parse_manifest_buffer( struct actctx_loader* acl, struct assembly *assembly,
                                       struct assembly_identity* ai, xmlbuf_t *xmlbuf )
{
    xmlstr_t elem;
    UNICODE_STRING elemU;

    if (!next_xml_elem(xmlbuf, &elem)) return STATUS_SXS_CANT_GEN_ACTCTX;

    if (xmlstr_cmp(&elem, g_xmlW) &&
        (!parse_xml_header(xmlbuf) || !next_xml_elem(xmlbuf, &elem)))
        return STATUS_SXS_CANT_GEN_ACTCTX;

    if (!xml_elem_cmp(&elem, assemblyW, asmv1W))
    {
        elemU = xmlstr2unicode(&elem);
        DPRINT1("root element is %wZ, not <assembly>\n", &elemU);
        return STATUS_SXS_CANT_GEN_ACTCTX;
    }

    if (!parse_assembly_elem(xmlbuf, acl, assembly, ai))
    {
        DPRINT1("failed to parse manifest %S\n", assembly->manifest.info );
        return STATUS_SXS_CANT_GEN_ACTCTX;
    }

    if (next_xml_elem(xmlbuf, &elem))
    {
        elemU = xmlstr2unicode(&elem);
        DPRINT1("unexpected element %wZ\n", &elemU);
        return STATUS_SXS_CANT_GEN_ACTCTX;
    }

    if (xmlbuf->ptr != xmlbuf->end)
    {
        DPRINT1("parse error\n");
        return STATUS_SXS_CANT_GEN_ACTCTX;
    }
    return STATUS_SUCCESS;
}