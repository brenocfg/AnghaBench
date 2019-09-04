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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSCallback ;

/* Variables and functions */
 int /*<<< orphan*/  S_FALSE ; 

__attribute__((used)) static HRESULT ScriptBSC_beginning_transaction(BSCallback *bsc, WCHAR **additional_headers)
{
    return S_FALSE;
}