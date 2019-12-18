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
typedef  int /*<<< orphan*/  XmlWriterProperty ;
typedef  int /*<<< orphan*/  IXmlWriter ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IXmlWriter_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void writer_set_property(IXmlWriter *writer, XmlWriterProperty property)
{
    HRESULT hr;

    hr = IXmlWriter_SetProperty(writer, property, TRUE);
    ok(hr == S_OK, "Failed to set writer property, hr %#x.\n", hr);
}