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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BYTES_PER_DUMP_LINE ; 
 scalar_t__ derived ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ isprint (int) ; 
 scalar_t__ raw ; 
 int /*<<< orphan*/  xml_out_dump_hex (int /*<<< orphan*/ *,char*,int,char*) ; 

void xml_out_dump_hex_and_ascii(FILE* xmlout, char *data, int data_len,
                                char* s)
{
    /* s is a string of spaces for indent */
    int i, j;

    if (raw) {
        xml_out_dump_hex(xmlout, data, data_len, s);
    }

    if (derived) {
        fprintf(xmlout,  "%s<AsHexAndASCII>\n", s);
        for (i = 0; i < data_len;) {
            fprintf(xmlout, "%s ", s); /* Additional leading space added in loop */
            /* First column: hex */
            for (j = 0; j < BYTES_PER_DUMP_LINE; j++) { /* Dump bytes */
                fprintf(xmlout, " %02x", data[i + j]);
            }
            /* Space between columns... */ fprintf(xmlout,  "  ");
            /* Second column: ASCII */
            for (j = 0; j < BYTES_PER_DUMP_LINE; j++, i++) {
                if (isprint((int)data[i]) && i < data_len) {
                    fprintf(xmlout, "%c", data[i]);
                } else {
                    fprintf(xmlout, " ");
                }
            }
            /* If we also wanted to output UCS-2 Unicode as a third column, then entire document
            must use fwprintf.  Forget about it for now.  As it stands, if data is UCS-2 format but still
            the ASCII set, then we'll be able to read every other byte as ASCII in column 2.  If
            data is UTF-8 format but still ASCII, then we'll be able to read every byte as ASCII
            in column 2. */
        }
        fprintf(xmlout,  "%s</AsHexAndASCII>\n", s);
    }
}