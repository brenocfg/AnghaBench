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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  cmsMLU ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/ * cmsMLUalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsMLUsetWide (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void SetOneStr(cmsMLU** mlu, wchar_t* s1, wchar_t* s2)
{
    *mlu = cmsMLUalloc(DbgThread(), 0);
    cmsMLUsetWide(DbgThread(), *mlu, "en", "US", s1);
    cmsMLUsetWide(DbgThread(), *mlu, "es", "ES", s2);
}