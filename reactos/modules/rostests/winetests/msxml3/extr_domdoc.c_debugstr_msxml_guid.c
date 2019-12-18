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
typedef  int /*<<< orphan*/  REFIID ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IMXNamespaceManager ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument2 ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument3 ; 
 int /*<<< orphan*/  IID_IXMLDOMSchemaCollection ; 
 int /*<<< orphan*/  IID_IXSLTemplate ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* wine_dbgstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *debugstr_msxml_guid(REFIID riid)
{
    if(!riid)
        return "(null)";

    if (IsEqualIID(&IID_IXMLDOMDocument, riid))
        return "IXMLDOMDocument";
    else if (IsEqualIID(&IID_IXMLDOMDocument2, riid))
        return "IXMLDOMDocument2";
    else if (IsEqualIID(&IID_IXMLDOMDocument3, riid))
        return "IXMLDOMDocument3";
    else if (IsEqualIID(&IID_IXMLDOMSchemaCollection, riid))
        return "IXMLDOMSchemaCollection";
    else if (IsEqualIID(&IID_IXSLTemplate, riid))
        return "IXSLTemplate";
    else if (IsEqualIID(&IID_IMXNamespaceManager, riid))
        return "IMXNamespaceManager";
    else
        return wine_dbgstr_guid(riid);
}