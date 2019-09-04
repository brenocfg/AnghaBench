#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ charset; int /*<<< orphan*/  nsdoc; } ;
typedef  scalar_t__ PRUnichar ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ CP_UTF8 ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysAllocString (scalar_t__ const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_from_charset_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,scalar_t__ const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_GetCharacterSet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

UINT get_document_charset(HTMLDocumentNode *doc)
{
    nsAString charset_str;
    UINT ret = 0;
    nsresult nsres;

    if(doc->charset)
        return doc->charset;

    nsAString_Init(&charset_str, NULL);
    nsres = nsIDOMHTMLDocument_GetCharacterSet(doc->nsdoc, &charset_str);
    if(NS_SUCCEEDED(nsres)) {
        const PRUnichar *charset;

        nsAString_GetData(&charset_str, &charset);

        if(*charset) {
            BSTR str = SysAllocString(charset);
            ret = cp_from_charset_string(str);
            SysFreeString(str);
        }
    }else {
        ERR("GetCharset failed: %08x\n", nsres);
    }
    nsAString_Finish(&charset_str);

    if(!ret)
        return CP_UTF8;

    return doc->charset = ret;
}