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
typedef  int /*<<< orphan*/  const elem_type_t ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;

/* Variables and functions */
#define  ET_BR 129 
#define  ET_DIV 128 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_adjacent_elem (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_create_elem (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_elem_all (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void test_insert_adjacent_elems(IHTMLDocument2 *doc, IHTMLElement *parent)
{
    IHTMLElement *elem, *elem2;

    static const elem_type_t br_br[] = {ET_BR, ET_BR};
    static const elem_type_t br_div_br[] = {ET_BR, ET_DIV, ET_BR};

    elem = test_create_elem(doc, "BR");
    insert_adjacent_elem(parent, "BeforeEnd", elem);
    IHTMLElement_Release(elem);

    test_elem_all((IUnknown*)parent, br_br, 1);

    elem = test_create_elem(doc, "BR");
    insert_adjacent_elem(parent, "beforeend", elem);

    test_elem_all((IUnknown*)parent, br_br, 2);

    elem2 = test_create_elem(doc, "DIV");
    insert_adjacent_elem(elem, "beforebegin", elem2);
    IHTMLElement_Release(elem2);
    IHTMLElement_Release(elem);

    test_elem_all((IUnknown*)parent, br_div_br, 3);
}