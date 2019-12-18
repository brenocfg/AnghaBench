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
struct TYPE_3__ {int has_arg; int* flag; int val; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ opj_option_t ;
typedef  int /*<<< orphan*/  longopts ;

/* Variables and functions */
 int BADCH ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* opj_optarg ; 
 scalar_t__ opj_opterr ; 
 int opj_optind ; 
 int opj_optopt ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

int opj_getopt_long(int argc, char * const argv[], const char *optstring,
                    const opj_option_t *longopts, int totlen)
{
    static int lastidx, lastofs;
    const char *tmp;
    int i, len;
    char param = 1;

again:
    if (opj_optind >= argc || !argv[opj_optind] || *argv[opj_optind] != '-') {
        return -1;
    }

    if (argv[opj_optind][0] == '-' && argv[opj_optind][1] == 0) {
        if (opj_optind >= (argc - 1)) { /* no more input parameters */
            param = 0;
        } else { /* more input parameters */
            if (argv[opj_optind + 1][0] == '-') {
                param = 0; /* Missing parameter after '-' */
            } else {
                param = 2;
            }
        }
    }

    if (param == 0) {
        ++opj_optind;
        return (BADCH);
    }

    if (argv[opj_optind][0] == '-') { /* long option */
        char* arg;
        const opj_option_t* o;
        o = longopts;
        len = sizeof(longopts[0]);

        if (param > 1) {
            if (opj_optind + 1 >= argc) {
                return -1;
            }
            arg = argv[opj_optind + 1];
            opj_optind++;
        } else {
            arg = argv[opj_optind] + 1;
        }

        if (strlen(arg) > 1) {
            for (i = 0; i < totlen; i = i + len, o++) {
                if (!strcmp(o->name, arg)) { /* match */
                    if (o->has_arg == 0) {
                        if ((argv[opj_optind + 1]) && (!(argv[opj_optind + 1][0] == '-'))) {
                            fprintf(stderr, "%s: option does not require an argument. Ignoring %s\n", arg,
                                    argv[opj_optind + 1]);
                            ++opj_optind;
                        }
                    } else {
                        opj_optarg = argv[opj_optind + 1];
                        if (opj_optarg) {
                            if (opj_optarg[0] ==
                                    '-') { /* Has read next input parameter: No arg for current parameter */
                                if (opj_opterr) {
                                    fprintf(stderr, "%s: option requires an argument\n", arg);
                                    return (BADCH);
                                }
                            }
                        }
                        if (!opj_optarg && o->has_arg == 1) { /* no argument there */
                            if (opj_opterr) {
                                fprintf(stderr, "%s: option requires an argument \n", arg);
                                return (BADCH);
                            }
                        }
                        ++opj_optind;
                    }
                    ++opj_optind;
                    if (o->flag) {
                        *(o->flag) = o->val;
                    } else {
                        return o->val;
                    }
                    return 0;
                }
            }/*(end for)String not found in the list*/
            fprintf(stderr, "Invalid option %s\n", arg);
            ++opj_optind;
            return (BADCH);
        } else { /*Single character input parameter*/
            if (*optstring == ':') {
                return ':';
            }
            if (lastidx != opj_optind) {
                lastidx = opj_optind;
                lastofs = 0;
            }
            opj_optopt = argv[opj_optind][lastofs + 1];
            if ((tmp = strchr(optstring, opj_optopt))) { /*Found input parameter in list*/
                if (*tmp == 0) { /* apparently, we looked for \0, i.e. end of argument */
                    ++opj_optind;
                    goto again;
                }
                if (tmp[1] == ':') { /* argument expected */
                    if (tmp[2] == ':' ||
                            argv[opj_optind][lastofs + 2]) { /* "-foo", return "oo" as opj_optarg */
                        if (!*(opj_optarg = argv[opj_optind] + lastofs + 2)) {
                            opj_optarg = 0;
                        }
                        goto found;
                    }
                    opj_optarg = argv[opj_optind + 1];
                    if (opj_optarg) {
                        if (opj_optarg[0] ==
                                '-') { /* Has read next input parameter: No arg for current parameter */
                            if (opj_opterr) {
                                fprintf(stderr, "%s: option requires an argument\n", arg);
                                ++opj_optind;
                                return (BADCH);
                            }
                        }
                    }
                    if (!opj_optarg) {  /* missing argument */
                        if (opj_opterr) {
                            fprintf(stderr, "%s: option requires an argument\n", arg);
                            ++opj_optind;
                            return (BADCH);
                        }
                    }
                    ++opj_optind;
                } else {/*Argument not expected*/
                    ++lastofs;
                    return opj_optopt;
                }
found:
                ++opj_optind;
                return opj_optopt;
            }   else {  /* not found */
                fprintf(stderr, "Invalid option %s\n", arg);
                ++opj_optind;
                return (BADCH);
            }/*end of not found*/

        }/* end of single character*/
    }/*end '-'*/
    fprintf(stderr, "Invalid option\n");
    ++opj_optind;
    return (BADCH);;
}