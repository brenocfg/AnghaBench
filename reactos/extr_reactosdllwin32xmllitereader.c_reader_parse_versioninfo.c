#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct reader_position {int dummy; } ;
struct TYPE_10__ {struct reader_position position; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_E_QUOTE ; 
 int /*<<< orphan*/  WC_E_WHITESPACE ; 
 int /*<<< orphan*/  WC_E_XMLDECL ; 
 char const* dblquoteW ; 
 char const* quoteW ; 
 int /*<<< orphan*/  reader_add_attr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct reader_position*,int /*<<< orphan*/ ) ; 
 scalar_t__ reader_cmp (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  reader_get_cur (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_init_strvalue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_parse_eq (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_parse_versionnum (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reader_skipspaces (TYPE_1__*) ; 

__attribute__((used)) static HRESULT reader_parse_versioninfo(xmlreader *reader)
{
    static const WCHAR versionW[] = {'v','e','r','s','i','o','n',0};
    struct reader_position position;
    strval val, name;
    HRESULT hr;

    if (!reader_skipspaces(reader)) return WC_E_WHITESPACE;

    position = reader->position;
    if (reader_cmp(reader, versionW)) return WC_E_XMLDECL;
    reader_init_strvalue(reader_get_cur(reader), 7, &name);
    /* skip 'version' */
    reader_skipn(reader, 7);

    hr = reader_parse_eq(reader);
    if (FAILED(hr)) return hr;

    if (reader_cmp(reader, quoteW) && reader_cmp(reader, dblquoteW))
        return WC_E_QUOTE;
    /* skip "'"|'"' */
    reader_skipn(reader, 1);

    hr = reader_parse_versionnum(reader, &val);
    if (FAILED(hr)) return hr;

    if (reader_cmp(reader, quoteW) && reader_cmp(reader, dblquoteW))
        return WC_E_QUOTE;

    /* skip "'"|'"' */
    reader_skipn(reader, 1);

    return reader_add_attr(reader, NULL, &name, NULL, &val, &position, 0);
}