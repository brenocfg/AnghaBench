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
struct TYPE_5__ {int za_integer_length; int za_num_integers; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
zap_join_key(objset_t *os, uint64_t fromobj, uint64_t intoobj,
    uint64_t value, dmu_tx_t *tx)
{
	zap_cursor_t zc;
	int err = 0;

	zap_attribute_t *za = kmem_alloc(sizeof (*za), KM_SLEEP);
	for (zap_cursor_init(&zc, os, fromobj);
	    zap_cursor_retrieve(&zc, za) == 0;
	    (void) zap_cursor_advance(&zc)) {
		if (za->za_integer_length != 8 || za->za_num_integers != 1) {
			err = SET_ERROR(EINVAL);
			break;
		}
		err = zap_add(os, intoobj, za->za_name,
		    8, 1, &value, tx);
		if (err != 0)
			break;
	}
	zap_cursor_fini(&zc);
	kmem_free(za, sizeof (*za));
	return (err);
}