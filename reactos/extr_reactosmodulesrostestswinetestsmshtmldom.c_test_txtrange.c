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
typedef  int /*<<< orphan*/  IHTMLTxtRange ;
typedef  int /*<<< orphan*/  IHTMLSelectionObject ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ET_BODY ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_get_selection (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLSelectionObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLSelectionObject_createRange (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLTxtRange_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLTxtRange_moveToElementText (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLSelectionObject ; 
 int /*<<< orphan*/  IID_IHTMLTxtRange ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  characterW ; 
 int /*<<< orphan*/ * doc_get_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * range_duplicate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selection_iids ; 
 int /*<<< orphan*/ * test_create_body_range (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_disp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_ifaces (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_range_collapse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_range_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_range_inrange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_range_isequal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_range_move (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_range_moveend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_range_movestart (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_range_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_range_paste_html (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_range_put_text (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_range_set_end_point (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  test_range_text (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  texteditW ; 
 int /*<<< orphan*/  wordW ; 

__attribute__((used)) static void test_txtrange(IHTMLDocument2 *doc)
{
    IHTMLTxtRange *body_range, *range, *range2;
    IHTMLSelectionObject *selection;
    IDispatch *disp_range;
    IHTMLElement *body;
    HRESULT hres;

    body_range = test_create_body_range(doc);

    test_disp((IUnknown*)body_range, &IID_IHTMLTxtRange, "[object]");

    test_range_text(body_range, "test abc 123\r\nit's text");

    range = range_duplicate(body_range);
    range2 = range_duplicate(body_range);

    test_range_isequal(range, range2, VARIANT_TRUE);

    test_range_text(range, "test abc 123\r\nit's text");
    test_range_text(body_range, "test abc 123\r\nit's text");

    test_range_collapse(range, TRUE);
    test_range_isequal(range, range2, VARIANT_FALSE);
    test_range_inrange(range, range2, VARIANT_FALSE);
    test_range_inrange(range2, range, VARIANT_TRUE);
    IHTMLTxtRange_Release(range2);

    test_range_expand(range, wordW, VARIANT_TRUE, "test ");
    test_range_expand(range, wordW, VARIANT_FALSE, "test ");
    test_range_move(range, characterW, 2, 2);
    test_range_expand(range, wordW, VARIANT_TRUE, "test ");

    test_range_collapse(range, FALSE);
    test_range_expand(range, wordW, VARIANT_TRUE, "abc ");

    test_range_collapse(range, FALSE);
    test_range_expand(range, wordW, VARIANT_TRUE, "123");
    test_range_expand(range, wordW, VARIANT_FALSE, "123");
    test_range_move(range, characterW, 2, 2);
    test_range_expand(range, wordW, VARIANT_TRUE, "123");
    test_range_moveend(range, characterW, -5, -5);
    test_range_text(range, NULL);
    test_range_moveend(range, characterW, 3, 3);
    test_range_text(range, "c 1");
    test_range_expand(range, texteditW, VARIANT_TRUE, "test abc 123\r\nit's text");
    test_range_collapse(range, TRUE);
    test_range_move(range, characterW, 4, 4);
    test_range_moveend(range, characterW, 1, 1);
    test_range_text(range, " ");
    test_range_move(range, wordW, 1, 1);
    test_range_moveend(range, characterW, 2, 2);
    test_range_text(range, "ab");

    IHTMLTxtRange_Release(range);

    range = range_duplicate(body_range);

    test_range_text(range, "test abc 123\r\nit's text");
    test_range_move(range, characterW, 3, 3);
    test_range_moveend(range, characterW, 1, 1);
    test_range_text(range, "t");
    test_range_moveend(range, characterW, 3, 3);
    test_range_text(range, "t ab");
    test_range_moveend(range, characterW, -2, -2);
    test_range_text(range, "t ");
    test_range_move(range, characterW, 6, 6);
    test_range_moveend(range, characterW, 3, 3);
    test_range_text(range, "123");
    test_range_moveend(range, characterW, 2, 2);
    test_range_text(range, "123\r\ni");

    IHTMLTxtRange_Release(range);

    range = range_duplicate(body_range);

    test_range_move(range, wordW, 1, 1);
    test_range_moveend(range, characterW, 2, 2);
    test_range_text(range, "ab");

    test_range_move(range, characterW, -2, -2);
    test_range_moveend(range, characterW, 2, 2);
    test_range_text(range, "t ");

    test_range_move(range, wordW, 3, 3);
    test_range_move(range, wordW, -2, -2);
    test_range_moveend(range, characterW, 2, 2);
    test_range_text(range, "ab");

    test_range_move(range, characterW, -6, -5);
    test_range_moveend(range, characterW, -1, 0);
    test_range_moveend(range, characterW, -6, 0);
    test_range_move(range, characterW, 2, 2);
    test_range_moveend(range, characterW, 2, 2);
    test_range_text(range, "st");
    test_range_moveend(range, characterW, -6, -4);
    test_range_moveend(range, characterW, 2, 2);

    IHTMLTxtRange_Release(range);

    range = range_duplicate(body_range);

    test_range_move(range, wordW, 2, 2);
    test_range_moveend(range, characterW, 2, 2);
    test_range_text(range, "12");

    test_range_move(range, characterW, 15, 14);
    test_range_move(range, characterW, -2, -2);
    test_range_moveend(range, characterW, 3, 2);
    test_range_text(range, "t");
    test_range_moveend(range, characterW, -1, -1);
    test_range_text(range, "t");
    test_range_expand(range, wordW, VARIANT_TRUE, "text");
    test_range_move(range, characterW, -2, -2);
    test_range_moveend(range, characterW, 2, 2);
    test_range_text(range, "s ");
    test_range_move(range, characterW, 100, 7);
    test_range_move(range, wordW, 1, 0);
    test_range_move(range, characterW, -2, -2);
    test_range_moveend(range, characterW, 3, 2);
    test_range_text(range, "t");

    IHTMLTxtRange_Release(range);

    range = range_duplicate(body_range);

    test_range_collapse(range, TRUE);
    test_range_expand(range, wordW, VARIANT_TRUE, "test ");
    test_range_put_text(range, "word");
    test_range_text(body_range, "wordabc 123\r\nit's text");
    test_range_text(range, NULL);
    test_range_moveend(range, characterW, 3, 3);
    test_range_text(range, "abc");
    test_range_movestart(range, characterW, -2, -2);
    test_range_text(range, "rdabc");
    test_range_movestart(range, characterW, 3, 3);
    test_range_text(range, "bc");
    test_range_movestart(range, characterW, 4, 4);
    test_range_text(range, NULL);
    test_range_movestart(range, characterW, -3, -3);
    test_range_text(range, "c 1");
    test_range_movestart(range, characterW, -7, -6);
    test_range_text(range, "wordabc 1");
    test_range_movestart(range, characterW, 100, 22);
    test_range_text(range, NULL);

    IHTMLTxtRange_Release(range);

    hres = IHTMLDocument2_get_selection(doc, &selection);
    ok(hres == S_OK, "IHTMLDocument2_get_selection failed: %08x\n", hres);

    test_disp((IUnknown*)selection, &IID_IHTMLSelectionObject, "[object]");
    test_ifaces((IUnknown*)selection, selection_iids);

    hres = IHTMLSelectionObject_createRange(selection, &disp_range);
    ok(hres == S_OK, "IHTMLSelectionObject_createRange failed: %08x\n", hres);
    IHTMLSelectionObject_Release(selection);

    hres = IDispatch_QueryInterface(disp_range, &IID_IHTMLTxtRange, (void **)&range);
    ok(hres == S_OK, "Could not get IID_IHTMLTxtRange interface: 0x%08x\n", hres);
    IDispatch_Release(disp_range);

    test_range_text(range, NULL);
    test_range_moveend(range, characterW, 3, 3);
    test_range_text(range, "wor");
    test_range_parent(range, ET_BODY);
    test_range_expand(range, texteditW, VARIANT_TRUE, "wordabc 123\r\nit's text");
    test_range_expand(range, texteditW, VARIANT_TRUE, "wordabc 123\r\nit's text");
    test_range_move(range, characterW, 3, 3);
    test_range_expand(range, wordW, VARIANT_TRUE, "wordabc ");
    test_range_moveend(range, characterW, -4, -4);
    test_range_put_text(range, "abc def ");
    test_range_expand(range, texteditW, VARIANT_TRUE, "abc def abc 123\r\nit's text");
    test_range_move(range, wordW, 1, 1);
    test_range_movestart(range, characterW, -1, -1);
    test_range_text(range, " ");
    test_range_move(range, wordW, 1, 1);
    test_range_moveend(range, characterW, 3, 3);
    test_range_text(range, "def");
    test_range_put_text(range, "xyz");
    test_range_moveend(range, characterW, 1, 1);
    test_range_move(range, wordW, 1, 1);
    test_range_moveend(range, characterW, 2, 2);
    test_range_text(range, "ab");

    body = doc_get_body(doc);

    hres = IHTMLTxtRange_moveToElementText(range, body);
    ok(hres == S_OK, "moveToElementText failed: %08x\n", hres);

    test_range_text(range, "abc xyz abc 123\r\nit's text");
    test_range_parent(range, ET_BODY);

    test_range_move(range, wordW, 1, 1);
    test_range_moveend(range, characterW, 12, 12);
    test_range_text(range, "xyz abc 123");

    test_range_collapse(range, VARIANT_TRUE);
    test_range_paste_html(range, "<br>paste<br>");
    test_range_text(range, NULL);

    test_range_moveend(range, characterW, 3, 3);
    test_range_text(range, "xyz");

    hres = IHTMLTxtRange_moveToElementText(range, body);
    ok(hres == S_OK, "moveToElementText failed: %08x\n", hres);

    test_range_text(range, "abc \r\npaste\r\nxyz abc 123\r\nit's text");

    test_range_move(range, wordW, 2, 2);
    test_range_collapse(range, VARIANT_TRUE);
    test_range_moveend(range, characterW, 5, 5);
    test_range_text(range, "paste");

    range2 = range_duplicate(range);

    test_range_set_end_point(range, "starttostart", body_range, S_OK);
    test_range_text(range, "abc \r\npaste");

    test_range_set_end_point(range, "endtoend", body_range, S_OK);
    test_range_text(range, "abc \r\npaste\r\nxyz abc 123\r\nit's text");

    test_range_set_end_point(range, "starttoend", range2, S_OK);
    test_range_text(range, "\r\nxyz abc 123\r\nit's text");

    test_range_set_end_point(range, "starttostart", body_range, S_OK);
    test_range_set_end_point(range, "endtostart", range2, S_OK);
    test_range_text(range, "abc ");

    test_range_set_end_point(range, "starttoend", body_range, S_OK);
    test_range_text(range, "paste\r\nxyz abc 123\r\nit's text");

    test_range_set_end_point(range, "EndToStart", body_range, S_OK);
    test_range_text(range, "abc ");

    test_range_set_end_point(range, "xxx", body_range, E_INVALIDARG);

    IHTMLTxtRange_Release(range);
    IHTMLTxtRange_Release(range2);
    IHTMLTxtRange_Release(body_range);
    IHTMLElement_Release(body);

}