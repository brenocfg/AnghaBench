#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_5__ {int za_integer_length; scalar_t__ za_name; int /*<<< orphan*/  za_num_integers; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uchar_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  ddt_key_t ;
struct TYPE_6__ {int /*<<< orphan*/  dde_key; int /*<<< orphan*/  dde_phys; } ;
typedef  TYPE_2__ ddt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DDT_KEY_WORDS ; 
 int /*<<< orphan*/  ddt_decompress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init_noprefetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_cursor_init_serialized (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zap_cursor_serialize (int /*<<< orphan*/ *) ; 
 int zap_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ddt_zap_walk(objset_t *os, uint64_t object, ddt_entry_t *dde, uint64_t *walk)
{
	zap_cursor_t zc;
	zap_attribute_t za;
	int error;

	if (*walk == 0) {
		/*
		 * We don't want to prefetch the entire ZAP object, because
		 * it can be enormous.  Also the primary use of DDT iteration
		 * is for scrubbing, in which case we will be issuing many
		 * scrub I/Os for each ZAP block that we read in, so
		 * reading the ZAP is unlikely to be the bottleneck.
		 */
		zap_cursor_init_noprefetch(&zc, os, object);
	} else {
		zap_cursor_init_serialized(&zc, os, object, *walk);
	}
	if ((error = zap_cursor_retrieve(&zc, &za)) == 0) {
		uchar_t cbuf[sizeof (dde->dde_phys) + 1];
		uint64_t csize = za.za_num_integers;
		ASSERT(za.za_integer_length == 1);
		error = zap_lookup_uint64(os, object, (uint64_t *)za.za_name,
		    DDT_KEY_WORDS, 1, csize, cbuf);
		ASSERT(error == 0);
		if (error == 0) {
			ddt_decompress(cbuf, dde->dde_phys, csize,
			    sizeof (dde->dde_phys));
			dde->dde_key = *(ddt_key_t *)za.za_name;
		}
		zap_cursor_advance(&zc);
		*walk = zap_cursor_serialize(&zc);
	}
	zap_cursor_fini(&zc);
	return (error);
}