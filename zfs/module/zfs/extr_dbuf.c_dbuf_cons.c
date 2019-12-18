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
struct TYPE_3__ {int /*<<< orphan*/  db_holds; int /*<<< orphan*/  db_cache_link; int /*<<< orphan*/  db_changed; int /*<<< orphan*/  db_rwlock; int /*<<< orphan*/  db_mtx; } ;
typedef  TYPE_1__ dmu_buf_impl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  RW_DEFAULT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multilist_link_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dbuf_cons(void *vdb, void *unused, int kmflag)
{
	dmu_buf_impl_t *db = vdb;
	bzero(db, sizeof (dmu_buf_impl_t));

	mutex_init(&db->db_mtx, NULL, MUTEX_DEFAULT, NULL);
	rw_init(&db->db_rwlock, NULL, RW_DEFAULT, NULL);
	cv_init(&db->db_changed, NULL, CV_DEFAULT, NULL);
	multilist_link_init(&db->db_cache_link);
	zfs_refcount_create(&db->db_holds);

	return (0);
}