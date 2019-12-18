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
struct TYPE_5__ {int /*<<< orphan*/ * (* ci_tmpl_init ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * ci_tmpl_free; } ;
typedef  TYPE_1__ zio_checksum_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  spa_cksum_tmpls_lock; int /*<<< orphan*/ ** spa_cksum_tmpls; int /*<<< orphan*/  spa_cksum_salt; } ;
typedef  TYPE_2__ spa_t ;
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* zio_checksum_table ; 

__attribute__((used)) static void
zio_checksum_template_init(enum zio_checksum checksum, spa_t *spa)
{
	zio_checksum_info_t *ci = &zio_checksum_table[checksum];

	if (ci->ci_tmpl_init == NULL)
		return;
	if (spa->spa_cksum_tmpls[checksum] != NULL)
		return;

	VERIFY(ci->ci_tmpl_free != NULL);
	mutex_enter(&spa->spa_cksum_tmpls_lock);
	if (spa->spa_cksum_tmpls[checksum] == NULL) {
		spa->spa_cksum_tmpls[checksum] =
		    ci->ci_tmpl_init(&spa->spa_cksum_salt);
		VERIFY(spa->spa_cksum_tmpls[checksum] != NULL);
	}
	mutex_exit(&spa->spa_cksum_tmpls_lock);
}