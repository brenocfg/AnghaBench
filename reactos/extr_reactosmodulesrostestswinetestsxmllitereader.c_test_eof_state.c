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
typedef  scalar_t__ LONG_PTR ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ IXmlReader_GetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int IXmlReader_IsEOF (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ XmlReadState_EndOfFile ; 
 int /*<<< orphan*/  XmlReaderProperty_ReadState ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_eof_state(IXmlReader *reader, BOOL eof)
{
    LONG_PTR state;
    HRESULT hr;

    ok(IXmlReader_IsEOF(reader) == eof, "Unexpected IsEOF() result\n");
    hr = IXmlReader_GetProperty(reader, XmlReaderProperty_ReadState, &state);
    ok(hr == S_OK, "GetProperty() failed, %#x\n", hr);
    ok((state == XmlReadState_EndOfFile) == eof, "Unexpected EndOfFile state %ld\n", state);
}