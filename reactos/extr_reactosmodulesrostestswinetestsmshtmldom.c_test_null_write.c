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
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IHTMLDocument2_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_writeln (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  doc_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_null_write(IHTMLDocument2 *doc)
{
    HRESULT hres;

    doc_write(doc, FALSE, NULL);
    doc_write(doc, TRUE, NULL);

    hres = IHTMLDocument2_write(doc, NULL);
    ok(hres == S_OK,
       "Expected IHTMLDocument2::write to return S_OK, got 0x%08x\n", hres);

    hres = IHTMLDocument2_writeln(doc, NULL);
    ok(hres == S_OK,
       "Expected IHTMLDocument2::writeln to return S_OK, got 0x%08x\n", hres);
}