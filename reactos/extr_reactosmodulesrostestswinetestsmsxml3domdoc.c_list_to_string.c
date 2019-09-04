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
typedef  int LONG ;
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IXMLDOMNodeList_get_length (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_nextNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  node_to_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ole_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static char *list_to_string(IXMLDOMNodeList *list)
{
    static char buf[4096];
    char *pos = buf;
    LONG len = 0;
    HRESULT hr;
    int i;

    if (list == NULL)
    {
        strcpy(buf, "(null)");
        return buf;
    }
    hr = IXMLDOMNodeList_get_length(list, &len);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    for (i = 0; i < len; i++)
    {
        IXMLDOMNode *node;
        if (i > 0)
            *(pos++) = ' ';
        ole_check(IXMLDOMNodeList_nextNode(list, &node));
        node_to_string(node, pos);
        pos += strlen(pos);
        IXMLDOMNode_Release(node);
    }
    *pos = 0;
    return buf;
}