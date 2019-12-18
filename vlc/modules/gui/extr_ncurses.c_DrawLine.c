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

/* Variables and functions */
 int /*<<< orphan*/  A_REVERSE ; 
 int /*<<< orphan*/  attroff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attrset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvhline (int,int,char,int) ; 

__attribute__((used)) static void DrawLine(int y, int x, int w)
{
    if (w <= 0) return;

    attrset(A_REVERSE);
    mvhline(y, x, ' ', w);
    attroff(A_REVERSE);
}