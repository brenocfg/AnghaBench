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
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ CoercionPathType ;

/* Variables and functions */
 int /*<<< orphan*/  COERCION_EXPLICIT ; 
 scalar_t__ COERCION_PATH_FUNC ; 
 int /*<<< orphan*/  TEXTOID ; 
 scalar_t__ find_coercion_pathway (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static Oid
find_text_coercion_func(Oid type)
{
	Oid funcid;
	bool is_varlena;
	CoercionPathType cpt;

	/*
	 * First look for an explicit cast type. Needed since the output of for
	 * example character(20) not the same as character(20)::text
	 */
	cpt = find_coercion_pathway(TEXTOID, type, COERCION_EXPLICIT, &funcid);

	if (cpt != COERCION_PATH_FUNC)
		getTypeOutputInfo(type, &funcid, &is_varlena);

	return funcid;
}