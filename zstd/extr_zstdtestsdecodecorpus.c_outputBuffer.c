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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const* const) ; 
 scalar_t__ fwrite (int /*<<< orphan*/  const*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void outputBuffer(const void* buf, size_t size, const char* const path)
{
    /* write data out to file */
    const BYTE* ip = (const BYTE*)buf;
    FILE* out;
    if (path) {
        out = fopen(path, "wb");
    } else {
        out = stdout;
    }
    if (!out) {
        fprintf(stderr, "Failed to open file at %s: ", path);
        perror(NULL);
        exit(1);
    }

    {   size_t fsize = size;
        size_t written = 0;
        while (written < fsize) {
            written += fwrite(ip + written, 1, fsize - written, out);
            if (ferror(out)) {
                fprintf(stderr, "Failed to write to file at %s: ", path);
                perror(NULL);
                exit(1);
            }
        }
    }

    if (path) {
        fclose(out);
    }
}