#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_5__ {int za_first_integer; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
zap_value_search(objset_t *os, uint64_t zapobj, uint64_t value, uint64_t mask,
    char *name)
{
	zap_cursor_t zc;
	int err;

	if (mask == 0)
		mask = -1ULL;

	zap_attribute_t *za = kmem_alloc(sizeof (*za), KM_SLEEP);
	for (zap_cursor_init(&zc, os, zapobj);
	    (err = zap_cursor_retrieve(&zc, za)) == 0;
	    zap_cursor_advance(&zc)) {
		if ((za->za_first_integer & mask) == (value & mask)) {
			(void) strcpy(name, za->za_name);
			break;
		}
	}
	zap_cursor_fini(&zc);
	kmem_free(za, sizeof (*za));
	return (err);
}