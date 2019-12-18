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
struct TYPE_3__ {int cbElements; } ;
typedef  scalar_t__ SF_TYPE ;
typedef  TYPE_1__* LPSAFEARRAY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ SF_BSTR ; 

__attribute__((used)) static DWORD elem_wire_size(LPSAFEARRAY lpsa, SF_TYPE sftype)
{
    if (sftype == SF_BSTR)
        return sizeof(DWORD);
    else
        return lpsa->cbElements;
}