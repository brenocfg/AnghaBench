#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_26__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_25__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_24__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_23__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_22__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_21__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int ref; TYPE_11__ IMXWriter_iface; int /*<<< orphan*/  dispex; void* version; void* encoding; int /*<<< orphan*/  buffer; int /*<<< orphan*/  xml_enc; int /*<<< orphan*/ * dest; void* newline; void* text; scalar_t__ indent; void* cdata; int /*<<< orphan*/ * element; void* prop_changed; void** props; int /*<<< orphan*/  class_version; TYPE_10__ IVBSAXErrorHandler_iface; TYPE_9__ IVBSAXDTDHandler_iface; TYPE_8__ IVBSAXContentHandler_iface; TYPE_7__ IVBSAXLexicalHandler_iface; TYPE_6__ IVBSAXDeclHandler_iface; TYPE_5__ ISAXErrorHandler_iface; TYPE_4__ ISAXDTDHandler_iface; TYPE_3__ ISAXDeclHandler_iface; TYPE_2__ ISAXLexicalHandler_iface; TYPE_1__ ISAXContentHandler_iface; } ;
typedef  TYPE_12__ mxwriter ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  MSXML_VERSION ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 void* FALSE ; 
 int /*<<< orphan*/  MXWriterVtbl ; 
 size_t MXWriter_BOM ; 
 size_t MXWriter_DisableEscaping ; 
 size_t MXWriter_Indent ; 
 size_t MXWriter_OmitXmlDecl ; 
 size_t MXWriter_Standalone ; 
 int /*<<< orphan*/  SAXContentHandlerVtbl ; 
 int /*<<< orphan*/  SAXDTDHandlerVtbl ; 
 int /*<<< orphan*/  SAXDeclHandlerVtbl ; 
 int /*<<< orphan*/  SAXErrorHandlerVtbl ; 
 int /*<<< orphan*/  SAXLexicalHandlerVtbl ; 
 scalar_t__ S_OK ; 
 void* SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (void*) ; 
 int /*<<< orphan*/  TRACE (char*,void*) ; 
 void* VARIANT_FALSE ; 
 void* VARIANT_TRUE ; 
 int /*<<< orphan*/  VBSAXContentHandlerVtbl ; 
 int /*<<< orphan*/  VBSAXDTDHandlerVtbl ; 
 int /*<<< orphan*/  VBSAXDeclHandlerVtbl ; 
 int /*<<< orphan*/  VBSAXErrorHandlerVtbl ; 
 int /*<<< orphan*/  VBSAXLexicalHandlerVtbl ; 
 int /*<<< orphan*/  XmlEncoding_UTF16 ; 
 TYPE_12__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_12__*) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ init_output_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxwriter_dispex ; 
 char const* utf16W ; 

HRESULT MXWriter_create(MSXML_VERSION version, void **ppObj)
{
    static const WCHAR version10W[] = {'1','.','0',0};
    mxwriter *This;
    HRESULT hr;

    TRACE("(%p)\n", ppObj);

    This = heap_alloc( sizeof (*This) );
    if(!This)
        return E_OUTOFMEMORY;

    This->IMXWriter_iface.lpVtbl = &MXWriterVtbl;
    This->ISAXContentHandler_iface.lpVtbl = &SAXContentHandlerVtbl;
    This->ISAXLexicalHandler_iface.lpVtbl = &SAXLexicalHandlerVtbl;
    This->ISAXDeclHandler_iface.lpVtbl = &SAXDeclHandlerVtbl;
    This->ISAXDTDHandler_iface.lpVtbl = &SAXDTDHandlerVtbl;
    This->ISAXErrorHandler_iface.lpVtbl = &SAXErrorHandlerVtbl;
    This->IVBSAXDeclHandler_iface.lpVtbl = &VBSAXDeclHandlerVtbl;
    This->IVBSAXLexicalHandler_iface.lpVtbl = &VBSAXLexicalHandlerVtbl;
    This->IVBSAXContentHandler_iface.lpVtbl = &VBSAXContentHandlerVtbl;
    This->IVBSAXDTDHandler_iface.lpVtbl = &VBSAXDTDHandlerVtbl;
    This->IVBSAXErrorHandler_iface.lpVtbl = &VBSAXErrorHandlerVtbl;
    This->ref = 1;
    This->class_version = version;

    This->props[MXWriter_BOM] = VARIANT_TRUE;
    This->props[MXWriter_DisableEscaping] = VARIANT_FALSE;
    This->props[MXWriter_Indent] = VARIANT_FALSE;
    This->props[MXWriter_OmitXmlDecl] = VARIANT_FALSE;
    This->props[MXWriter_Standalone] = VARIANT_FALSE;
    This->prop_changed = FALSE;
    This->encoding = SysAllocString(utf16W);
    This->version  = SysAllocString(version10W);
    This->xml_enc  = XmlEncoding_UTF16;

    This->element = NULL;
    This->cdata = FALSE;
    This->indent = 0;
    This->text = FALSE;
    This->newline = FALSE;

    This->dest = NULL;

    hr = init_output_buffer(This->xml_enc, &This->buffer);
    if (hr != S_OK) {
        SysFreeString(This->encoding);
        SysFreeString(This->version);
        heap_free(This);
        return hr;
    }

    init_dispex(&This->dispex, (IUnknown*)&This->IMXWriter_iface, &mxwriter_dispex);

    *ppObj = &This->IMXWriter_iface;

    TRACE("returning iface %p\n", *ppObj);

    return S_OK;
}