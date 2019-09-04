#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/ * szClassName; int /*<<< orphan*/ * szAppName; } ;
struct TYPE_5__ {TYPE_2__* classes; } ;
typedef  TYPE_1__* PTHEME_FILE ;
typedef  TYPE_2__* PTHEME_CLASS ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PTHEME_CLASS MSSTYLES_FindClass(PTHEME_FILE tf, LPCWSTR pszAppName, LPCWSTR pszClassName)
{
    PTHEME_CLASS cur = tf->classes;
    while(cur) {
        if(!pszAppName) {
            if(!*cur->szAppName && !lstrcmpiW(pszClassName, cur->szClassName))
                return cur;
        }
        else {
            if(!lstrcmpiW(pszAppName, cur->szAppName) && !lstrcmpiW(pszClassName, cur->szClassName))
                return cur;
        }
        cur = cur->next;
    }
    return NULL;
}