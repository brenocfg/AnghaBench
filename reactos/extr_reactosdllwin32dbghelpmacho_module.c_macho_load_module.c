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
struct process {int dummy; } ;
struct module {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */

struct module*  macho_load_module(struct process* pcs, const WCHAR* name, unsigned long addr)
{
    return NULL;
}