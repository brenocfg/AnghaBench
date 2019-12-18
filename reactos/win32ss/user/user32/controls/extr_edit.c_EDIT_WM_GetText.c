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
struct TYPE_3__ {int /*<<< orphan*/  text; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__* LPSTR ;
typedef  int INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (scalar_t__*) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT EDIT_WM_GetText(const EDITSTATE *es, INT count, LPWSTR dst, BOOL unicode)
{
    if(!count) return 0;

    if(unicode)
    {
	lstrcpynW(dst, es->text, count);
	return strlenW(dst);
    }
    else
    {
	LPSTR textA = (LPSTR)dst;
	if (!WideCharToMultiByte(CP_ACP, 0, es->text, -1, textA, count, NULL, NULL))
            textA[count - 1] = 0; /* ensure 0 termination */
	return strlen(textA);
    }
}