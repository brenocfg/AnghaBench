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
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DOMNodeType ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IXMLDOMNode_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_get_nodeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_get_nodeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_parentNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLDOMNode_selectSingleNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  NODE_ATTRIBUTE ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int get_node_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_str_for_type (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ole_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  wsprintfA (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void node_to_string(IXMLDOMNode *node, char *buf)
{
    HRESULT r = S_OK;
    DOMNodeType type;

    if (node == NULL)
    {
        lstrcpyA(buf, "(null)");
        return;
    }

    IXMLDOMNode_AddRef(node);
    while (r == S_OK)
    {
        IXMLDOMNode *new_node;

        ole_check(IXMLDOMNode_get_nodeType(node, &type));
        get_str_for_type(type, buf);
        buf+=strlen(buf);

        if (type == NODE_ATTRIBUTE)
        {
            BSTR bstr;
            ole_check(IXMLDOMNode_get_nodeName(node, &bstr));
            *(buf++) = '\'';
            wsprintfA(buf, "%ws", bstr);
            buf += strlen(buf);
            *(buf++) = '\'';
            SysFreeString(bstr);

            r = IXMLDOMNode_selectSingleNode(node, _bstr_(".."), &new_node);
        }
        else
        {
            r = IXMLDOMNode_get_parentNode(node, &new_node);
            sprintf(buf, "%d", get_node_position(node));
            buf += strlen(buf);
        }

        ok(SUCCEEDED(r), "get_parentNode failed (%08x)\n", r);
        IXMLDOMNode_Release(node);
        node = new_node;
        if (r == S_OK)
            *(buf++) = '.';
    }

    *buf = 0;
}