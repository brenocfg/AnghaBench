#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cUrl; int /*<<< orphan*/ * rgwszUrl; } ;
typedef  size_t DWORD ;
typedef  TYPE_1__ CRYPT_URL_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 

__attribute__((used)) static void compareUrlArray(const CRYPT_URL_ARRAY *expected,
 const CRYPT_URL_ARRAY *got)
{
    ok(expected->cUrl == got->cUrl, "Expected %d URLs, got %d\n",
     expected->cUrl, got->cUrl);
    if (expected->cUrl == got->cUrl)
    {
        DWORD i;

        for (i = 0; i < got->cUrl; i++)
            ok(!lstrcmpiW(expected->rgwszUrl[i], got->rgwszUrl[i]),
             "%d: unexpected URL\n", i);
    }
}