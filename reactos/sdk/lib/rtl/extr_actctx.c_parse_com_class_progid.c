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
typedef  int /*<<< orphan*/  xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
struct entity {int dummy; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  asmv1W ; 
 int /*<<< orphan*/  com_class_add_progid (int /*<<< orphan*/ *,struct entity*) ; 
 scalar_t__ parse_expect_end_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_expect_no_attr (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  parse_text_content (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  progidW ; 

__attribute__((used)) static BOOL parse_com_class_progid(xmlbuf_t* xmlbuf, struct entity *entity)
{
    xmlstr_t content;
    BOOL end = FALSE;

    if (!parse_expect_no_attr(xmlbuf, &end) || end || !parse_text_content(xmlbuf, &content))
        return FALSE;

    if (!com_class_add_progid(&content, entity)) return FALSE;
    return parse_expect_end_elem(xmlbuf, progidW, asmv1W);
}