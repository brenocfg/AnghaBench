#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct file {int /*<<< orphan*/  entry; int /*<<< orphan*/  name; } ;
struct assembly {int /*<<< orphan*/  files; } ;
typedef  float WCHAR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMNamedNodeMap ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SXS_MANIFEST_FORMAT_ERROR ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct file* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 
 scalar_t__ IXMLDOMDocument_getElementsByTagName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNamedNodeMap_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNodeList_nextNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocString (float const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  get_attribute_value (int /*<<< orphan*/ *,float const*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT parse_files( IXMLDOMDocument *doc, struct assembly *assembly )
{
    static const WCHAR fileW[] = {'f','i','l','e',0};
    static const WCHAR nameW[] = {'n','a','m','e',0};
    IXMLDOMNamedNodeMap *attrs;
    IXMLDOMNodeList *list;
    IXMLDOMNode *node;
    struct file *f;
    BSTR str;
    HRESULT hr;
    LONG len;

    str = SysAllocString( fileW );
    hr = IXMLDOMDocument_getElementsByTagName( doc, str, &list );
    SysFreeString( str );
    if (hr != S_OK) return hr;

    hr = IXMLDOMNodeList_get_length( list, &len );
    if (hr != S_OK) goto done;
    TRACE("found %d files\n", len);
    if (!len)
    {
        hr = ERROR_SXS_MANIFEST_FORMAT_ERROR;
        goto done;
    }

    for (;;)
    {
        hr = IXMLDOMNodeList_nextNode( list, &node );
        if (hr != S_OK || !node)
        {
            hr = S_OK;
            break;
        }

        /* FIXME: validate node type */

        hr = IXMLDOMNode_get_attributes( node, &attrs );
        IXMLDOMNode_Release( node );
        if (hr != S_OK)
            goto done;

        if (!(f = HeapAlloc( GetProcessHeap(), 0, sizeof(struct file) )))
        {
            IXMLDOMNamedNodeMap_Release( attrs );
            hr = E_OUTOFMEMORY;
            goto done;
        }

        f->name = get_attribute_value( attrs, nameW );
        IXMLDOMNamedNodeMap_Release( attrs );
        if (!f->name)
        {
            HeapFree( GetProcessHeap(), 0, f );
            hr = ERROR_SXS_MANIFEST_FORMAT_ERROR;
            goto done;
        }
        list_add_tail( &assembly->files, &f->entry );
    }

    if (list_empty( &assembly->files ))
    {
        WARN("no files found\n");
        hr = ERROR_SXS_MANIFEST_FORMAT_ERROR;
    }

done:
    IXMLDOMNodeList_Release( list );
    return hr;
}