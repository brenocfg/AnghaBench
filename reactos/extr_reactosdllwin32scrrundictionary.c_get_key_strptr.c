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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;

/* Variables and functions */
 scalar_t__ VT_BSTR ; 
 int /*<<< orphan*/ * V_BSTR (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ ** V_BSTRREF (int /*<<< orphan*/  const*) ; 
 scalar_t__ V_VT (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline WCHAR *get_key_strptr(const VARIANT *key)
{
    if (V_VT(key) == VT_BSTR)
        return V_BSTR(key);

    if (V_BSTRREF(key))
        return *V_BSTRREF(key);

    return NULL;
}