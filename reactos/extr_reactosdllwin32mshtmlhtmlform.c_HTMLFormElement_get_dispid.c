#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsIDOMHTMLCollection ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  nsform; } ;
typedef  char PRUnichar ;
typedef  TYPE_1__ HTMLFormElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ DISPID ;
typedef  char* BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLElement ; 
 scalar_t__ MSHTML_CUSTOM_DISPID_CNT ; 
 scalar_t__ MSHTML_DISPID_CUSTOM_MIN ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  get_elem_attr_value (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const**) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLCollection_GetLength (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsIDOMHTMLCollection_Item (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMHTMLCollection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_GetId (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLFormElement_GetElements (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpiW (char const*,char*) ; 
 scalar_t__ strtoulW (char*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static HRESULT HTMLFormElement_get_dispid(HTMLDOMNode *iface,
        BSTR name, DWORD grfdex, DISPID *pid)
{
    HTMLFormElement *This = impl_from_HTMLDOMNode(iface);
    nsIDOMHTMLCollection *elements;
    nsAString nsstr, name_str;
    UINT32 len, i;
    nsresult nsres;
    HRESULT hres = DISP_E_UNKNOWNNAME;

    static const PRUnichar nameW[] = {'n','a','m','e',0};

    TRACE("(%p)->(%s %x %p)\n", This, wine_dbgstr_w(name), grfdex, pid);

    nsres = nsIDOMHTMLFormElement_GetElements(This->nsform, &elements);
    if(NS_FAILED(nsres)) {
        FIXME("GetElements failed: 0x%08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIDOMHTMLCollection_GetLength(elements, &len);
    if(NS_FAILED(nsres)) {
        FIXME("GetLength failed: 0x%08x\n", nsres);
        nsIDOMHTMLCollection_Release(elements);
        return E_FAIL;
    }

    if(len > MSHTML_CUSTOM_DISPID_CNT)
        len = MSHTML_CUSTOM_DISPID_CNT;

    /* FIXME: Implement in more generic way */
    if('0' <= *name && *name <= '9') {
        WCHAR *end_ptr;

        i = strtoulW(name, &end_ptr, 10);
        if(!*end_ptr && i < len) {
            *pid = MSHTML_DISPID_CUSTOM_MIN + i;
            return S_OK;
        }
    }

    nsAString_Init(&nsstr, NULL);
    for(i = 0; i < len; ++i) {
        nsIDOMNode *nsitem;
        nsIDOMHTMLElement *nshtml_elem;
        const PRUnichar *str;

        nsres = nsIDOMHTMLCollection_Item(elements, i, &nsitem);
        if(NS_FAILED(nsres)) {
            FIXME("Item failed: 0x%08x\n", nsres);
            hres = E_FAIL;
            break;
        }

        nsres = nsIDOMNode_QueryInterface(nsitem, &IID_nsIDOMHTMLElement, (void**)&nshtml_elem);
        nsIDOMNode_Release(nsitem);
        if(NS_FAILED(nsres)) {
            FIXME("Failed to get nsIDOMHTMLNode interface: 0x%08x\n", nsres);
            hres = E_FAIL;
            break;
        }

        /* compare by id attr */
        nsres = nsIDOMHTMLElement_GetId(nshtml_elem, &nsstr);
        if(NS_FAILED(nsres)) {
            FIXME("GetId failed: 0x%08x\n", nsres);
            nsIDOMHTMLElement_Release(nshtml_elem);
            hres = E_FAIL;
            break;
        }
        nsAString_GetData(&nsstr, &str);
        if(!strcmpiW(str, name)) {
            nsIDOMHTMLElement_Release(nshtml_elem);
            /* FIXME: using index for dispid */
            *pid = MSHTML_DISPID_CUSTOM_MIN + i;
            hres = S_OK;
            break;
        }

        /* compare by name attr */
        nsres = get_elem_attr_value(nshtml_elem, nameW, &name_str, &str);
        nsIDOMHTMLElement_Release(nshtml_elem);
        if(NS_SUCCEEDED(nsres)) {
            if(!strcmpiW(str, name)) {
                nsAString_Finish(&name_str);
                /* FIXME: using index for dispid */
                *pid = MSHTML_DISPID_CUSTOM_MIN + i;
                hres = S_OK;
                break;
            }
            nsAString_Finish(&name_str);
        }
    }

    nsAString_Finish(&nsstr);
    nsIDOMHTMLCollection_Release(elements);
    return hres;
}