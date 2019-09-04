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
typedef  int /*<<< orphan*/  xmlreader ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WC_E_EQUAL ; 
 scalar_t__ reader_cmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  reader_skipn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reader_skipspaces (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT reader_parse_eq(xmlreader *reader)
{
    static const WCHAR eqW[] = {'=',0};
    reader_skipspaces(reader);
    if (reader_cmp(reader, eqW)) return WC_E_EQUAL;
    /* skip '=' */
    reader_skipn(reader, 1);
    reader_skipspaces(reader);
    return S_OK;
}