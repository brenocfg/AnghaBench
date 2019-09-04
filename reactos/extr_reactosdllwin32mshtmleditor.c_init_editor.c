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
typedef  int /*<<< orphan*/  HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  UPDATE_UI ; 
 int /*<<< orphan*/  set_ns_fontname (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  update_doc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void init_editor(HTMLDocument *This)
{
    update_doc(This, UPDATE_UI);

    set_ns_fontname(This, "Times New Roman");
}