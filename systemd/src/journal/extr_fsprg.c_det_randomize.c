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
typedef  int /*<<< orphan*/  gcry_md_hd_t ;

/* Variables and functions */
 int /*<<< orphan*/  RND_HASH ; 
 int /*<<< orphan*/  gcry_md_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_final (int /*<<< orphan*/ ) ; 
 size_t gcry_md_get_algo_dlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_putc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcry_md_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_write (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void det_randomize(void *buf, size_t buflen, const void *seed, size_t seedlen, uint32_t idx) {
        gcry_md_hd_t hd, hd2;
        size_t olen, cpylen;
        uint32_t ctr;

        olen = gcry_md_get_algo_dlen(RND_HASH);
        gcry_md_open(&hd, RND_HASH, 0);
        gcry_md_write(hd, seed, seedlen);
        gcry_md_putc(hd, (idx >> 24) & 0xff);
        gcry_md_putc(hd, (idx >> 16) & 0xff);
        gcry_md_putc(hd, (idx >>  8) & 0xff);
        gcry_md_putc(hd, (idx >>  0) & 0xff);

        for (ctr = 0; buflen; ctr++) {
                gcry_md_copy(&hd2, hd);
                gcry_md_putc(hd2, (ctr >> 24) & 0xff);
                gcry_md_putc(hd2, (ctr >> 16) & 0xff);
                gcry_md_putc(hd2, (ctr >>  8) & 0xff);
                gcry_md_putc(hd2, (ctr >>  0) & 0xff);
                gcry_md_final(hd2);
                cpylen = (buflen < olen) ? buflen : olen;
                memcpy(buf, gcry_md_read(hd2, RND_HASH), cpylen);
                gcry_md_close(hd2);
                buf += cpylen;
                buflen -= cpylen;
        }
        gcry_md_close(hd);
}