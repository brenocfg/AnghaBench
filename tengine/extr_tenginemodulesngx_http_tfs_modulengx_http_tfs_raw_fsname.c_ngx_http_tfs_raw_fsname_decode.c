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
typedef  int uint32_t ;
typedef  int u_char ;
typedef  int ngx_uint_t ;

/* Variables and functions */
 int NGX_HTTP_TFS_FILE_NAME_EXCEPT_SUFFIX_LEN ; 
 int NGX_HTTP_TFS_FILE_NAME_LEN ; 
 int* dec_table ; 
 int /*<<< orphan*/  xor_mask (int*,int,int*) ; 

void
ngx_http_tfs_raw_fsname_decode(u_char *input, u_char *output)
{
    u_char      buffer[NGX_HTTP_TFS_FILE_NAME_EXCEPT_SUFFIX_LEN];
    uint32_t    value;
    ngx_uint_t  i, k;

    k = 0;

    if (input != NULL && output != NULL) {
        for (i = 0; i < NGX_HTTP_TFS_FILE_NAME_LEN - 2; i += 4) {
            value = (dec_table[input[i] & 0xff] << 18)
                     + (dec_table[input[i + 1] & 0xff] << 12)
                        + (dec_table[input[i + 2] & 0xff] << 6)
                           + dec_table[input[i + 3] & 0xff];
            buffer[k++] = (u_char) ((value >> 16) & 0xff);
            buffer[k++] = (u_char) ((value >> 8) & 0xff);
            buffer[k++] = (u_char) (value & 0xff);
        }
        xor_mask(buffer, NGX_HTTP_TFS_FILE_NAME_EXCEPT_SUFFIX_LEN, output);
    }
}