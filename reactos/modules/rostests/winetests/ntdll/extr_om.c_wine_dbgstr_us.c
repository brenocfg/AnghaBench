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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  char* LPCSTR ;

/* Variables and functions */
 char* wine_dbgstr_wn (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LPCSTR wine_dbgstr_us( const UNICODE_STRING *us )
{
    if (!us) return "(null)";
    return wine_dbgstr_wn(us->Buffer, us->Length / sizeof(WCHAR));
}