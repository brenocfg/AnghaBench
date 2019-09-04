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
typedef  int /*<<< orphan*/  IHTMLTxtRange ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLTxtRange_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  characterW ; 
 int /*<<< orphan*/ * test_create_body_range (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_range_collapse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_range_move (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_range_moveend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_range_text (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_txtrange2(IHTMLDocument2 *doc)
{
    IHTMLTxtRange *range;

    range = test_create_body_range(doc);

    test_range_text(range, "abc\r\n\r\n123\r\n\r\n\r\ndef");
    test_range_move(range, characterW, 5, 5);
    test_range_moveend(range, characterW, 1, 1);
    test_range_text(range, "2");
    test_range_move(range, characterW, -3, -3);
    test_range_moveend(range, characterW, 3, 3);
    test_range_text(range, "c\r\n\r\n1");
    test_range_collapse(range, VARIANT_FALSE);
    test_range_moveend(range, characterW, 4, 4);
    test_range_text(range, "23");
    test_range_moveend(range, characterW, 1, 1);
    test_range_text(range, "23\r\n\r\n\r\nd");
    test_range_moveend(range, characterW, -1, -1);
    test_range_text(range, "23");
    test_range_moveend(range, characterW, -1, -1);
    test_range_text(range, "23");
    test_range_moveend(range, characterW, -2, -2);
    test_range_text(range, "2");

    IHTMLTxtRange_Release(range);
}