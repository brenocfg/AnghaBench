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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * get_elem_by_id (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_elem_set_innerhtml (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_img_set_src (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_img_src (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void test_blocked(IHTMLDocument2 *doc, IHTMLElement *outer_elem)
{
    IHTMLElement *elem;

    test_elem_set_innerhtml((IUnknown*)outer_elem,
            "<img id=\"imgid\" src=\"BLOCKED::http://www.winehq.org/img.png\" />");
    elem = get_elem_by_id(doc, "imgid", TRUE);
    if(elem) {
        test_img_src((IUnknown*)elem, "BLOCKED::", "blocked::http://www.winehq.org/img.png");
        IHTMLElement_Release(elem);
    }

    test_elem_set_innerhtml((IUnknown*)outer_elem,
            "<img id=\"imgid\" src=\"BLOCKE::http://www.winehq.org/img.png\" />");
    elem = get_elem_by_id(doc, "imgid", TRUE);
    if(elem) {
        test_img_src((IUnknown*)elem, "blocke::http://www.winehq.org/img.png", NULL);
        test_img_set_src((IUnknown*)elem, "BLOCKED:http://www.winehq.org/img.png");
        test_img_src((IUnknown*)elem, "blocked:http://www.winehq.org/img.png", NULL);
        test_img_set_src((IUnknown*)elem, "blocked::http://www.winehq.org/img.png");
        test_img_src((IUnknown*)elem, "BLOCKED::", "blocked::http://www.winehq.org/img.png");
        IHTMLElement_Release(elem);
    }
}