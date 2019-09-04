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
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  const IRichEditOleImpl ;

/* Variables and functions */
 int /*<<< orphan*/  IID_Igetrichole ; 
 int /*<<< orphan*/  ITextRange_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static inline const IRichEditOleImpl *get_range_reole(ITextRange *range)
{
    IRichEditOleImpl *reole = NULL;
    ITextRange_QueryInterface(range, &IID_Igetrichole, (void**)&reole);
    return reole;
}