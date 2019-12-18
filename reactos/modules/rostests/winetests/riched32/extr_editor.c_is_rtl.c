#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* lsUsb; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  TYPE_1__ LOCALESIGNATURE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ GetLocaleInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOCALE_FONTSIGNATURE ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 

__attribute__((used)) static BOOL is_rtl(void) {
  LOCALESIGNATURE sig;

  return (GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_FONTSIGNATURE,
                         (LPSTR) &sig, sizeof(LOCALESIGNATURE)) &&
          (sig.lsUsb[3] & 0x08000000) != 0);
}