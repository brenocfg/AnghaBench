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
struct TYPE_3__ {int /*<<< orphan*/  target_len; int /*<<< orphan*/  target; int /*<<< orphan*/  field_len; int /*<<< orphan*/  field; } ;
typedef  TYPE_1__ ParseFieldVec ;

/* Variables and functions */
 int parse_field (void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_fieldv(const void *data, size_t length, const ParseFieldVec *fields, unsigned n_fields) {
        unsigned i;

        for (i = 0; i < n_fields; i++) {
                const ParseFieldVec *f = &fields[i];
                int r;

                r = parse_field(data, length, f->field, f->field_len, f->target, f->target_len);
                if (r < 0)
                        return r;
                else if (r > 0)
                        break;
        }

        return 0;
}