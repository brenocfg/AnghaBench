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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_JScript ; 
 int /*<<< orphan*/  CLSID_VBScript ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static BOOL get_guid_from_type(LPCWSTR type, GUID *guid)
{
    const WCHAR text_javascriptW[] =
        {'t','e','x','t','/','j','a','v','a','s','c','r','i','p','t',0};
    const WCHAR text_jscriptW[] =
        {'t','e','x','t','/','j','s','c','r','i','p','t',0};
    const WCHAR text_vbscriptW[] =
        {'t','e','x','t','/','v','b','s','c','r','i','p','t',0};

    /* FIXME: Handle more types */
    if(!strcmpiW(type, text_javascriptW) || !strcmpiW(type, text_jscriptW)) {
        *guid = CLSID_JScript;
    }else if(!strcmpiW(type, text_vbscriptW)) {
        *guid = CLSID_VBScript;
    }else {
        FIXME("Unknown type %s\n", debugstr_w(type));
        return FALSE;
    }

    return TRUE;
}