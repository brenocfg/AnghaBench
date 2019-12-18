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
typedef  int /*<<< orphan*/  crypto_mech_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  kcf_mech_hash_find (char*) ; 

crypto_mech_type_t
crypto_mech2id_common(char *mechname, boolean_t load_module)
{
	crypto_mech_type_t mt = kcf_mech_hash_find(mechname);
	return (mt);
}