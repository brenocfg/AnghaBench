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

/* Variables and functions */
 int UCDN_GENERAL_CATEGORY_LL ; 
 int UCDN_GENERAL_CATEGORY_LU ; 
 int UCDN_GENERAL_CATEGORY_ND ; 
 int UCDN_GENERAL_CATEGORY_NO ; 
 int /*<<< orphan*/  fz_chartorune (int*,char*) ; 
 int ucdn_get_general_category (int) ; 

__attribute__((used)) static inline int myisalnum(char *s)
{
	int cat, c;
	fz_chartorune(&c, s);
	cat = ucdn_get_general_category(c);
	if (cat >= UCDN_GENERAL_CATEGORY_LL && cat <= UCDN_GENERAL_CATEGORY_LU)
		return 1;
	if (cat >= UCDN_GENERAL_CATEGORY_ND && cat <= UCDN_GENERAL_CATEGORY_NO)
		return 1;
	return 0;
}