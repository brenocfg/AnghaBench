#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int decod_format; int cod_format; int /*<<< orphan*/  core; } ;
typedef  TYPE_1__ opj_decompress_parameters ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_set_default_decoder_parameters (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_default_parameters(opj_decompress_parameters* parameters)
{
    if (parameters) {
        memset(parameters, 0, sizeof(opj_decompress_parameters));

        /* default decoding parameters (command line specific) */
        parameters->decod_format = -1;
        parameters->cod_format = -1;

        /* default decoding parameters (core) */
        opj_set_default_decoder_parameters(&(parameters->core));
    }
}