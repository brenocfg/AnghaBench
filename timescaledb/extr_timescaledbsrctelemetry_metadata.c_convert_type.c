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
typedef  int /*<<< orphan*/  PGFunction ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static Datum
convert_type(PGFunction func, Datum value, Oid from_type)
{
	bool value_is_varlena;
	Oid value_out;

	getTypeOutputInfo(from_type, &value_out, &value_is_varlena);

	if (!OidIsValid(value_out))
		TYPE_ERROR("output", from_type);

	return DirectFunctionCall1(func, OidFunctionCall1(value_out, value));
}