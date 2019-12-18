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
struct TYPE_4__ {int (* headers ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ ks_magic; int ks_type; int /*<<< orphan*/  ks_raw_buf; int /*<<< orphan*/  ks_raw_bufsize; TYPE_1__ ks_raw_ops; int /*<<< orphan*/  ks_snaptime; int /*<<< orphan*/  ks_crtime; scalar_t__ ks_data_size; int /*<<< orphan*/  ks_ndata; int /*<<< orphan*/  ks_flags; int /*<<< orphan*/  ks_kid; } ;
typedef  TYPE_2__ kstat_t ;

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
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kstat_seq_show_headers(struct seq_file *f)
{
	kstat_t *ksp = (kstat_t *)f->private;
	int rc = 0;

	ASSERT(ksp->ks_magic == KS_MAGIC);

	seq_printf(f, "%d %d 0x%02x %d %d %lld %lld\n",
	    ksp->ks_kid, ksp->ks_type, ksp->ks_flags,
	    ksp->ks_ndata, (int)ksp->ks_data_size,
	    ksp->ks_crtime, ksp->ks_snaptime);

	switch (ksp->ks_type) {
		case KSTAT_TYPE_RAW:
restart:
			if (ksp->ks_raw_ops.headers) {
				rc = ksp->ks_raw_ops.headers(
				    ksp->ks_raw_buf, ksp->ks_raw_bufsize);
				if (rc == ENOMEM && !kstat_resize_raw(ksp))
					goto restart;
				if (!rc)
					seq_puts(f, ksp->ks_raw_buf);
			} else {
				seq_printf(f, "raw data\n");
			}
			break;
		case KSTAT_TYPE_NAMED:
			seq_printf(f, "%-31s %-4s %s\n",
			    "name", "type", "data");
			break;
		case KSTAT_TYPE_INTR:
			seq_printf(f, "%-8s %-8s %-8s %-8s %-8s\n",
			    "hard", "soft", "watchdog",
			    "spurious", "multsvc");
			break;
		case KSTAT_TYPE_IO:
			seq_printf(f,
			    "%-8s %-8s %-8s %-8s %-8s %-8s "
			    "%-8s %-8s %-8s %-8s %-8s %-8s\n",
			    "nread", "nwritten", "reads", "writes",
			    "wtime", "wlentime", "wupdate",
			    "rtime", "rlentime", "rupdate",
			    "wcnt", "rcnt");
			break;
		case KSTAT_TYPE_TIMER:
			seq_printf(f,
			    "%-31s %-8s "
			    "%-8s %-8s %-8s %-8s %-8s\n",
			    "name", "events", "elapsed",
			    "min", "max", "start", "stop");
			break;
		default:
			PANIC("Undefined kstat type %d\n", ksp->ks_type);
	}

	return (-rc);
}