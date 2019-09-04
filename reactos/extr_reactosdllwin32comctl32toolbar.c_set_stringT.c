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
typedef  int /*<<< orphan*/  TBUTTON_INFO ;
typedef  int DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ IS_INTRESOURCE (int) ; 
 int /*<<< orphan*/  set_string_index (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_stringT( TBUTTON_INFO *btn, const WCHAR *str, BOOL unicode )
{
    if (IS_INTRESOURCE( (DWORD_PTR)str ) || (DWORD_PTR)str == -1) return;
    set_string_index( btn, (DWORD_PTR)str, unicode );
}