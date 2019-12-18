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
 int /*<<< orphan*/  BufMapType ; 
 int /*<<< orphan*/  BufferType ; 
 int /*<<< orphan*/  CurrentType ; 
 int /*<<< orphan*/  DictionaryType ; 
 int /*<<< orphan*/  FunctionType ; 
 int /*<<< orphan*/  IterType ; 
 int /*<<< orphan*/  ListType ; 
 int /*<<< orphan*/  LoaderType ; 
 int /*<<< orphan*/  OptionsType ; 
 int /*<<< orphan*/  OutputType ; 
 int /*<<< orphan*/  PYTYPE_READY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeType ; 
 int /*<<< orphan*/  TabListType ; 
 int /*<<< orphan*/  TabPageType ; 
 int /*<<< orphan*/  WinListType ; 
 int /*<<< orphan*/  WindowType ; 

__attribute__((used)) static int
init_types(void)
{
    PYTYPE_READY(IterType);
    PYTYPE_READY(BufferType);
    PYTYPE_READY(RangeType);
    PYTYPE_READY(WindowType);
    PYTYPE_READY(TabPageType);
    PYTYPE_READY(BufMapType);
    PYTYPE_READY(WinListType);
    PYTYPE_READY(TabListType);
    PYTYPE_READY(CurrentType);
    PYTYPE_READY(DictionaryType);
    PYTYPE_READY(ListType);
    PYTYPE_READY(FunctionType);
    PYTYPE_READY(OptionsType);
    PYTYPE_READY(OutputType);
    PYTYPE_READY(LoaderType);
    return 0;
}