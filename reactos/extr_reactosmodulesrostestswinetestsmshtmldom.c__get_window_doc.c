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
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLWindow2_get_document (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static IHTMLDocument2 *_get_window_doc(unsigned line, IHTMLWindow2 *window)
{
    IHTMLDocument2 *doc;
    HRESULT hres;

    doc = NULL;
    hres = IHTMLWindow2_get_document(window, &doc);
    ok(hres == S_OK, "get_document failed: %08x\n", hres);
    ok(doc != NULL, "disp == NULL\n");

    return doc;
}