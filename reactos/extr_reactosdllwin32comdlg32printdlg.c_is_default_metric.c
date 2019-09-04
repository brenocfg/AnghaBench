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
typedef  int /*<<< orphan*/  system ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int LOCALE_IMEASURE ; 
 int LOCALE_RETURN_NUMBER ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 

__attribute__((used)) static inline BOOL is_default_metric(void)
{
    DWORD system;
    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_IMEASURE | LOCALE_RETURN_NUMBER,
                   (LPWSTR)&system, sizeof(system));
    return system == 0;
}