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
struct sltg_impl_info {int res00; int next; int res04; int res07; int res08; short ref; int res0c; int res0e; int res10; int res12; scalar_t__ pos; scalar_t__ impltypeflags; } ;
struct sltg_data {int dummy; } ;
typedef  int /*<<< orphan*/  impl_info ;

/* Variables and functions */
 int /*<<< orphan*/  append_data (struct sltg_data*,struct sltg_impl_info*,int) ; 

__attribute__((used)) static void write_impl_href(struct sltg_data *data, short href)
{
    struct sltg_impl_info impl_info;

    impl_info.res00 = 0x004a;
    impl_info.next = -1;
    impl_info.res04 = -1;
    impl_info.impltypeflags = 0;
    impl_info.res07 = 0x80;
    impl_info.res08 = 0x0012;
    impl_info.ref = href;
    impl_info.res0c = 0x4001;
    impl_info.res0e = -2; /* 0xfffe */
    impl_info.res10 = -1;
    impl_info.res12 = 0x001d;
    impl_info.pos = 0;

    append_data(data, &impl_info, sizeof(impl_info));
}