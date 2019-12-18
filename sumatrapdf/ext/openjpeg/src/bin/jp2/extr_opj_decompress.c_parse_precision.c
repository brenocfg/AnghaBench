#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int prec; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ opj_precision ;
struct TYPE_7__ {unsigned int nb_precision; TYPE_1__* precision; } ;
typedef  TYPE_2__ opj_decompress_parameters ;
typedef  unsigned int OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_PREC_MODE_CLIP ; 
 int /*<<< orphan*/  OPJ_PREC_MODE_SCALE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ realloc (TYPE_1__*,unsigned int) ; 
 int sscanf (char const*,char*,int*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static OPJ_BOOL parse_precision(const char* option,
                                opj_decompress_parameters* parameters)
{
    const char* l_remaining = option;
    OPJ_BOOL l_result = OPJ_TRUE;

    /* reset */
    if (parameters->precision) {
        free(parameters->precision);
        parameters->precision = NULL;
    }
    parameters->nb_precision = 0U;

    for (;;) {
        int prec;
        char mode;
        char comma;
        int count;

        count = sscanf(l_remaining, "%d%c%c", &prec, &mode, &comma);
        if (count == 1) {
            mode = 'C';
            count++;
        }
        if ((count == 2) || (mode == ',')) {
            if (mode == ',') {
                mode = 'C';
            }
            comma = ',';
            count = 3;
        }
        if (count == 3) {
            if ((prec < 1) || (prec > 32)) {
                fprintf(stderr, "Invalid precision %d in precision option %s\n", prec, option);
                l_result = OPJ_FALSE;
                break;
            }
            if ((mode != 'C') && (mode != 'S')) {
                fprintf(stderr, "Invalid precision mode %c in precision option %s\n", mode,
                        option);
                l_result = OPJ_FALSE;
                break;
            }
            if (comma != ',') {
                fprintf(stderr, "Invalid character %c in precision option %s\n", comma, option);
                l_result = OPJ_FALSE;
                break;
            }

            if (parameters->precision == NULL) {
                /* first one */
                parameters->precision = (opj_precision *)malloc(sizeof(opj_precision));
                if (parameters->precision == NULL) {
                    fprintf(stderr, "Could not allocate memory for precision option\n");
                    l_result = OPJ_FALSE;
                    break;
                }
            } else {
                OPJ_UINT32 l_new_size = parameters->nb_precision + 1U;
                opj_precision* l_new;

                if (l_new_size == 0U) {
                    fprintf(stderr, "Could not allocate memory for precision option\n");
                    l_result = OPJ_FALSE;
                    break;
                }

                l_new = (opj_precision *)realloc(parameters->precision,
                                                 l_new_size * sizeof(opj_precision));
                if (l_new == NULL) {
                    fprintf(stderr, "Could not allocate memory for precision option\n");
                    l_result = OPJ_FALSE;
                    break;
                }
                parameters->precision = l_new;
            }

            parameters->precision[parameters->nb_precision].prec = (OPJ_UINT32)prec;
            switch (mode) {
            case 'C':
                parameters->precision[parameters->nb_precision].mode = OPJ_PREC_MODE_CLIP;
                break;
            case 'S':
                parameters->precision[parameters->nb_precision].mode = OPJ_PREC_MODE_SCALE;
                break;
            default:
                break;
            }
            parameters->nb_precision++;

            l_remaining = strchr(l_remaining, ',');
            if (l_remaining == NULL) {
                break;
            }
            l_remaining += 1;
        } else {
            fprintf(stderr, "Could not parse precision option %s\n", option);
            l_result = OPJ_FALSE;
            break;
        }
    }

    return l_result;
}