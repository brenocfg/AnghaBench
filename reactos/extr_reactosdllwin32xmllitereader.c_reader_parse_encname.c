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
typedef  int /*<<< orphan*/  xmlreader ;
typedef  scalar_t__ xml_encoding ;
struct TYPE_3__ {char* str; int len; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ strval ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_E_ENCNAME ; 
 scalar_t__ XmlEncoding_Unknown ; 
 int /*<<< orphan*/  debugstr_wn (char*,int) ; 
 scalar_t__ is_wchar_encname (char) ; 
 scalar_t__ parse_encoding_name (char*,int) ; 
 int /*<<< orphan*/  reader_get_cur (int /*<<< orphan*/ *) ; 
 char* reader_get_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT reader_parse_encname(xmlreader *reader, strval *val)
{
    WCHAR *start = reader_get_ptr(reader), *ptr;
    xml_encoding enc;
    int len;

    if ((*start < 'A' || *start > 'Z') && (*start < 'a' || *start > 'z'))
        return WC_E_ENCNAME;

    val->start = reader_get_cur(reader);

    ptr = start;
    while (is_wchar_encname(*++ptr))
        ;

    len = ptr - start;
    enc = parse_encoding_name(start, len);
    TRACE("encoding name %s\n", debugstr_wn(start, len));
    val->str = start;
    val->len = len;

    if (enc == XmlEncoding_Unknown)
        return WC_E_ENCNAME;

    /* skip encoding name */
    reader_skipn(reader, len);
    return S_OK;
}