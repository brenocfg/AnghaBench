#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ TLBVarDesc ;
typedef  int /*<<< orphan*/  OLECHAR ;

/* Variables and functions */
 int /*<<< orphan*/  TLB_get_bstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline TLBVarDesc *TLB_get_vardesc_by_name(TLBVarDesc *vardescs,
        UINT n, const OLECHAR *name)
{
    while(n){
        if(!lstrcmpiW(TLB_get_bstr(vardescs->Name), name))
            return vardescs;
        ++vardescs;
        --n;
    }
    return NULL;
}