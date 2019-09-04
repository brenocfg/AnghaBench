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
typedef  int /*<<< orphan*/  xmlbuf_t ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  asmv1W ; 
 int /*<<< orphan*/  noInheritW ; 
 scalar_t__ parse_expect_end_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_expect_no_attr (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static BOOL parse_noinherit_elem(xmlbuf_t* xmlbuf)
{
    BOOL end = FALSE;

    if (!parse_expect_no_attr(xmlbuf, &end)) return FALSE;
    return end || parse_expect_end_elem(xmlbuf, noInheritW, asmv1W);
}