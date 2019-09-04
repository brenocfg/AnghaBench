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
typedef  int LONG_PTR ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  int HRESULT ;

/* Variables and functions */
 int CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 int IXmlReader_GetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 int IXmlReader_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int S_OK ; 
 int /*<<< orphan*/  XmlReaderProperty_MaxElementDepth ; 
 int /*<<< orphan*/  XmlReaderProperty_MultiLanguage ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_reader_properties(void)
{
    IXmlReader *reader;
    LONG_PTR value;
    HRESULT hr;

    hr = CreateXmlReader(&IID_IXmlReader, (void**)&reader, NULL);
    ok(hr == S_OK, "S_OK, got %08x\n", hr);

    value = 0;
    hr = IXmlReader_GetProperty(reader, XmlReaderProperty_MaxElementDepth, &value);
    ok(hr == S_OK, "GetProperty failed: %08x\n", hr);
    ok(value == 256, "Unexpected default max depth value %ld\n", value);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_MultiLanguage, 0);
    ok(hr == S_OK, "SetProperty failed: %08x\n", hr);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_MaxElementDepth, 0);
    ok(hr == S_OK, "SetProperty failed: %08x\n", hr);

    value = 256;
    hr = IXmlReader_GetProperty(reader, XmlReaderProperty_MaxElementDepth, &value);
    ok(hr == S_OK, "GetProperty failed: %08x\n", hr);
    ok(value == 0, "Unexpected max depth value %ld\n", value);

    IXmlReader_Release(reader);
}