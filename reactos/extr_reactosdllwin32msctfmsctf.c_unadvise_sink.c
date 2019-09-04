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
typedef  int /*<<< orphan*/  Sink ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_E_NOCONNECTION ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  free_sink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * remove_Cookie (int /*<<< orphan*/ ) ; 

HRESULT unadvise_sink(DWORD cookie)
{
    Sink *sink;

    sink = remove_Cookie(cookie);
    if (!sink)
        return CONNECT_E_NOCONNECTION;

    free_sink(sink);
    return S_OK;
}