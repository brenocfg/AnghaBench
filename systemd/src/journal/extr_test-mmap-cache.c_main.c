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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  MMapFileDescriptor ;
typedef  int /*<<< orphan*/  MMapCache ;

/* Variables and functions */
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int mkostemp_safe (char*) ; 
 int /*<<< orphan*/ * mmap_cache_add_fd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmap_cache_free_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mmap_cache_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,unsigned long long,int,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmap_cache_new () ; 
 int /*<<< orphan*/  mmap_cache_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_close (int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int main(int argc, char *argv[]) {
        MMapFileDescriptor *fx;
        int x, y, z, r;
        char px[] = "/tmp/testmmapXXXXXXX", py[] = "/tmp/testmmapYXXXXXX", pz[] = "/tmp/testmmapZXXXXXX";
        MMapCache *m;
        void *p, *q;

        assert_se(m = mmap_cache_new());

        x = mkostemp_safe(px);
        assert_se(x >= 0);
        unlink(px);

        assert_se(fx = mmap_cache_add_fd(m, x));

        y = mkostemp_safe(py);
        assert_se(y >= 0);
        unlink(py);

        z = mkostemp_safe(pz);
        assert_se(z >= 0);
        unlink(pz);

        r = mmap_cache_get(m, fx, PROT_READ, 0, false, 1, 2, NULL, &p, NULL);
        assert_se(r >= 0);

        r = mmap_cache_get(m, fx, PROT_READ, 0, false, 2, 2, NULL, &q, NULL);
        assert_se(r >= 0);

        assert_se((uint8_t*) p + 1 == (uint8_t*) q);

        r = mmap_cache_get(m, fx, PROT_READ, 1, false, 3, 2, NULL, &q, NULL);
        assert_se(r >= 0);

        assert_se((uint8_t*) p + 2 == (uint8_t*) q);

        r = mmap_cache_get(m, fx, PROT_READ, 0, false, 16ULL*1024ULL*1024ULL, 2, NULL, &p, NULL);
        assert_se(r >= 0);

        r = mmap_cache_get(m, fx, PROT_READ, 1, false, 16ULL*1024ULL*1024ULL+1, 2, NULL, &q, NULL);
        assert_se(r >= 0);

        assert_se((uint8_t*) p + 1 == (uint8_t*) q);

        mmap_cache_free_fd(m, fx);
        mmap_cache_unref(m);

        safe_close(x);
        safe_close(y);
        safe_close(z);

        return 0;
}