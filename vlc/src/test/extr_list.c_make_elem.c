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
struct vlc_list {int dummy; } ;
struct test_elem {int i; struct vlc_list node; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 struct test_elem* malloc (int) ; 

__attribute__((used)) static struct vlc_list *make_elem(int i)
{
    struct test_elem *e = malloc(sizeof (*e));
    if (e == NULL)
        abort();

    e->i = i;
    return &e->node;
}