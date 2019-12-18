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
struct TYPE_3__ {int /*<<< orphan*/ * comps_indices; int /*<<< orphan*/ * precision; } ;
typedef  TYPE_1__ opj_decompress_parameters ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_parameters(opj_decompress_parameters* parameters)
{
    if (parameters) {
        if (parameters->precision) {
            free(parameters->precision);
            parameters->precision = NULL;
        }

        free(parameters->comps_indices);
        parameters->comps_indices = NULL;
    }
}