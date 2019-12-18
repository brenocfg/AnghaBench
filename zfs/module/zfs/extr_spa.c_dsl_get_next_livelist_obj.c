#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_3__ {int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
dsl_get_next_livelist_obj(objset_t *os, uint64_t zap_obj, uint64_t *llp)
{
	int err;
	zap_cursor_t zc;
	zap_attribute_t za;
	zap_cursor_init(&zc, os, zap_obj);
	err = zap_cursor_retrieve(&zc, &za);
	zap_cursor_fini(&zc);
	if (err == 0)
		*llp = za.za_first_integer;
	return (err);
}