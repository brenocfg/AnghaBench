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
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  type_new_alias (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * type_new_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static type_t *make_safearray(type_t *type)
{
  return type_new_array(NULL, type_new_alias(type, "SAFEARRAY"), TRUE, 0,
                        NULL, NULL, FC_RP);
}