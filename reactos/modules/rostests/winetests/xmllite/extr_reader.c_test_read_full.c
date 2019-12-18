#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nodes_test {TYPE_1__* nodes; int /*<<< orphan*/  xml; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ XmlNodeType_None ; 
 struct nodes_test misc_test ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  read_node (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  reader_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_input_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_read_full(void)
{
    struct nodes_test *test = &misc_test;
    IXmlReader *reader;
    HRESULT hr;
    int i;

    hr = CreateXmlReader(&IID_IXmlReader, (void**)&reader, NULL);
    ok(hr == S_OK, "S_OK, got %08x\n", hr);

    set_input_string(reader, test->xml);

    i = 0;
    do
    {
        read_node(reader, test->nodes[i].type);
        reader_value(reader, test->nodes[i].value);
    } while(test->nodes[i++].type != XmlNodeType_None);

    IXmlReader_Release(reader);
}