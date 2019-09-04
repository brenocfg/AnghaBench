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
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMHTMLScriptElement ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  char PRUnichar ;
typedef  int /*<<< orphan*/  HTMLInnerWindow ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLElement ; 
 scalar_t__ NS_OK ; 
 scalar_t__ NS_SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_default_script_guid (int /*<<< orphan*/ *) ; 
 scalar_t__ get_elem_attr_value (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  get_guid_from_language (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_guid_from_type (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMHTMLScriptElement_GetType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMHTMLScriptElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static BOOL get_script_guid(HTMLInnerWindow *window, nsIDOMHTMLScriptElement *nsscript, GUID *guid)
{
    nsIDOMHTMLElement *nselem;
    const PRUnichar *language;
    nsAString val_str;
    BOOL ret = FALSE;
    nsresult nsres;

    static const PRUnichar languageW[] = {'l','a','n','g','u','a','g','e',0};

    nsAString_Init(&val_str, NULL);

    nsres = nsIDOMHTMLScriptElement_GetType(nsscript, &val_str);
    if(NS_SUCCEEDED(nsres)) {
        const PRUnichar *type;

        nsAString_GetData(&val_str, &type);
        if(*type) {
            ret = get_guid_from_type(type, guid);
            nsAString_Finish(&val_str);
            return ret;
        }
    }else {
        ERR("GetType failed: %08x\n", nsres);
    }

    nsres = nsIDOMHTMLScriptElement_QueryInterface(nsscript, &IID_nsIDOMHTMLElement, (void**)&nselem);
    assert(nsres == NS_OK);

    nsres = get_elem_attr_value(nselem, languageW, &val_str, &language);
    nsIDOMHTMLElement_Release(nselem);
    if(NS_SUCCEEDED(nsres)) {
        if(*language) {
            ret = get_guid_from_language(language, guid);
        }else {
            *guid = get_default_script_guid(window);
            ret = TRUE;
        }
        nsAString_Finish(&val_str);
    }

    return ret;
}