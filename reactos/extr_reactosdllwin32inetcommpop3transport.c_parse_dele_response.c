#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; } ;
typedef  TYPE_1__ POP3Transport ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 void* STATE_DONE ; 
#define  STATE_OK 128 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static HRESULT parse_dele_response(POP3Transport *This, DWORD *dwPopId)
{
    switch (This->state)
    {
    case STATE_OK:
        *dwPopId = 0; /* FIXME */
        This->state = STATE_DONE;
        return S_OK;

    default:
        WARN("parse error\n");
        This->state = STATE_DONE;
        return S_FALSE;
    }
}