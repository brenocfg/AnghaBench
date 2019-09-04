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
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  is_text (scalar_t__) ; 
 int lstrlenA (int /*<<< orphan*/ ) ; 
 int lstrlenW (scalar_t__) ; 

__attribute__((used)) static inline int textlenT(LPCWSTR text, BOOL isW)
{
    return !is_text(text) ? 0 :
	   isW ? lstrlenW(text) : lstrlenA((LPCSTR)text);
}