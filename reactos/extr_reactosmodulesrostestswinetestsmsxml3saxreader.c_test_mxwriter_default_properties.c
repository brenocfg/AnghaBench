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
struct mxwriter_props_t {int bom; int disable_escape; int indent; int omitdecl; int standalone; int encoding; scalar_t__ clsid; } ;
typedef  int VARIANT_BOOL ;
typedef  int /*<<< orphan*/  IMXWriter ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoCreateInstance (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IMXWriter ; 
 int /*<<< orphan*/  IMXWriter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMXWriter_get_byteOrderMark (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IMXWriter_get_disableOutputEscaping (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IMXWriter_get_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMXWriter_get_indent (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IMXWriter_get_omitXMLDeclaration (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IMXWriter_get_standalone (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bstr_ (int) ; 
 int /*<<< orphan*/  is_clsid_supported (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxwriter_support_data ; 
 int /*<<< orphan*/  ok (int,char*,int,int,int) ; 
 int wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_mxwriter_default_properties(const struct mxwriter_props_t *table)
{
    int i = 0;

    while (table->clsid)
    {
        IMXWriter *writer;
        VARIANT_BOOL b;
        BSTR encoding;
        HRESULT hr;

        if (!is_clsid_supported(table->clsid, mxwriter_support_data))
        {
            table++;
            i++;
            continue;
        }

        hr = CoCreateInstance(table->clsid, NULL, CLSCTX_INPROC_SERVER,
            &IID_IMXWriter, (void**)&writer);
        EXPECT_HR(hr, S_OK);

        b = !table->bom;
        hr = IMXWriter_get_byteOrderMark(writer, &b);
        EXPECT_HR(hr, S_OK);
        ok(table->bom == b, "test %d: got BOM %d, expected %d\n", i, b, table->bom);

        b = !table->disable_escape;
        hr = IMXWriter_get_disableOutputEscaping(writer, &b);
        EXPECT_HR(hr, S_OK);
        ok(table->disable_escape == b, "test %d: got disable escape %d, expected %d\n", i, b,
           table->disable_escape);

        b = !table->indent;
        hr = IMXWriter_get_indent(writer, &b);
        EXPECT_HR(hr, S_OK);
        ok(table->indent == b, "test %d: got indent %d, expected %d\n", i, b, table->indent);

        b = !table->omitdecl;
        hr = IMXWriter_get_omitXMLDeclaration(writer, &b);
        EXPECT_HR(hr, S_OK);
        ok(table->omitdecl == b, "test %d: got omitdecl %d, expected %d\n", i, b, table->omitdecl);

        b = !table->standalone;
        hr = IMXWriter_get_standalone(writer, &b);
        EXPECT_HR(hr, S_OK);
        ok(table->standalone == b, "test %d: got standalone %d, expected %d\n", i, b, table->standalone);

        hr = IMXWriter_get_encoding(writer, &encoding);
        EXPECT_HR(hr, S_OK);
        ok(!lstrcmpW(encoding, _bstr_(table->encoding)), "test %d: got encoding %s, expected %s\n",
            i, wine_dbgstr_w(encoding), table->encoding);
        SysFreeString(encoding);

        IMXWriter_Release(writer);

        table++;
        i++;
    }
}