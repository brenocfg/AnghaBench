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
typedef  int /*<<< orphan*/  elem_type_t ;
typedef  int /*<<< orphan*/  all_types ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLElementCollection ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
#define  ET_BODY 132 
#define  ET_BR 131 
#define  ET_HEAD 130 
#define  ET_HTML 129 
#define  ET_TITLE 128 
 scalar_t__ IHTMLDocument2_get_all (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLElementCollection_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_elem_collection (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void test_cond_comment(IHTMLDocument2 *doc)
{
    IHTMLElementCollection *col;
    HRESULT hres;

    static const elem_type_t all_types[] = {
        ET_HTML,
        ET_HEAD,
        ET_TITLE,
        ET_BODY,
        ET_BR
    };

    hres = IHTMLDocument2_get_all(doc, &col);
    ok(hres == S_OK, "get_all failed: %08x\n", hres);
    test_elem_collection((IUnknown*)col, all_types, sizeof(all_types)/sizeof(all_types[0]));
    IHTMLElementCollection_Release(col);
}