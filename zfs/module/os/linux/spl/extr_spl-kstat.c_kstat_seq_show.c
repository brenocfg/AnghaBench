#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {scalar_t__ private; } ;
typedef  int /*<<< orphan*/  kstat_timer_t ;
struct TYPE_4__ {int (* data ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_5__ {scalar_t__ ks_magic; int ks_type; int ks_ndata; int /*<<< orphan*/  ks_data_size; int /*<<< orphan*/  ks_data; int /*<<< orphan*/  ks_raw_buf; int /*<<< orphan*/  ks_raw_bufsize; TYPE_1__ ks_raw_ops; } ;
typedef  TYPE_2__ kstat_t ;
typedef  int /*<<< orphan*/  kstat_named_t ;
typedef  int /*<<< orphan*/  kstat_io_t ;
typedef  int /*<<< orphan*/  kstat_intr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOMEM ; 
#define  KSTAT_TYPE_INTR 132 
#define  KSTAT_TYPE_IO 131 
#define  KSTAT_TYPE_NAMED 130 
#define  KSTAT_TYPE_RAW 129 
#define  KSTAT_TYPE_TIMER 128 
 scalar_t__ KS_MAGIC ; 
 int /*<<< orphan*/  PANIC (char*,int) ; 
 int /*<<< orphan*/  kstat_resize_raw (TYPE_2__*) ; 
 int kstat_seq_show_intr (struct seq_file*,int /*<<< orphan*/ *) ; 
 int kstat_seq_show_io (struct seq_file*,int /*<<< orphan*/ *) ; 
 int kstat_seq_show_named (struct seq_file*,int /*<<< orphan*/ *) ; 
 int kstat_seq_show_raw (struct seq_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstat_seq_show_timer (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
kstat_seq_show(struct seq_file *f, void *p)
{
	kstat_t *ksp = (kstat_t *)f->private;
	int rc = 0;

	ASSERT(ksp->ks_magic == KS_MAGIC);

	switch (ksp->ks_type) {
		case KSTAT_TYPE_RAW:
restart:
			if (ksp->ks_raw_ops.data) {
				rc = ksp->ks_raw_ops.data(
				    ksp->ks_raw_buf, ksp->ks_raw_bufsize, p);
				if (rc == ENOMEM && !kstat_resize_raw(ksp))
					goto restart;
				if (!rc)
					seq_puts(f, ksp->ks_raw_buf);
			} else {
				ASSERT(ksp->ks_ndata == 1);
				rc = kstat_seq_show_raw(f, ksp->ks_data,
				    ksp->ks_data_size);
			}
			break;
		case KSTAT_TYPE_NAMED:
			rc = kstat_seq_show_named(f, (kstat_named_t *)p);
			break;
		case KSTAT_TYPE_INTR:
			rc = kstat_seq_show_intr(f, (kstat_intr_t *)p);
			break;
		case KSTAT_TYPE_IO:
			rc = kstat_seq_show_io(f, (kstat_io_t *)p);
			break;
		case KSTAT_TYPE_TIMER:
			rc = kstat_seq_show_timer(f, (kstat_timer_t *)p);
			break;
		default:
			PANIC("Undefined kstat type %d\n", ksp->ks_type);
	}

	return (-rc);
}