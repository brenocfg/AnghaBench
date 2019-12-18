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
typedef  int /*<<< orphan*/  jpip_dec_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  decode_jpip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_jpipdecoder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fread_jpip (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite_jp2k (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * init_jpipdecoder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jpip_to_j2k(char *argv[])
{
    jpip_dec_param_t *dec;

    dec = init_jpipdecoder(OPJ_FALSE);

    if (!(fread_jpip(argv[1], dec))) {
        return 1;
    }

    decode_jpip(dec);

    if (!(fwrite_jp2k(argv[2], dec))) {
        return 1;
    }

    /*  output_log( OPJ_TRUE, OPJ_FALSE, OPJ_FALSE, dec); */

    destroy_jpipdecoder(&dec);

    return 0;
}