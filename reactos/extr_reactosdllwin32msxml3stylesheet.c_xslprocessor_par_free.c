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
struct xslprocessor_params {int /*<<< orphan*/  count; } ;
struct xslprocessor_par {int /*<<< orphan*/  value; int /*<<< orphan*/  name; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (struct xslprocessor_par*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xslprocessor_par_free(struct xslprocessor_params *params, struct xslprocessor_par *par)
{
    params->count--;
    list_remove(&par->entry);
    SysFreeString(par->name);
    SysFreeString(par->value);
    heap_free(par);
}