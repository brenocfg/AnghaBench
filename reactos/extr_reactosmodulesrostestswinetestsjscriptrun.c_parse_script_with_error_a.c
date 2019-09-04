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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  SCODE ;
typedef  char const* LPCSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  SCRIPTITEM_GLOBALMEMBERS ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 
 int /*<<< orphan*/  parse_script_with_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_script_with_error_a(const char *src, SCODE errorcode, ULONG line, LONG pos, LPCSTR source, LPCSTR desc, LPCSTR linetext)
{
    BSTR tmp, script_source, description, line_text;

    tmp = a2bstr(src);
    script_source = a2bstr(source);
    description = a2bstr(desc);
    line_text = a2bstr(linetext);

    parse_script_with_error(SCRIPTITEM_GLOBALMEMBERS, tmp, errorcode, line, pos, script_source, description, line_text);

    SysFreeString(line_text);
    SysFreeString(description);
    SysFreeString(script_source);
    SysFreeString(tmp);
}