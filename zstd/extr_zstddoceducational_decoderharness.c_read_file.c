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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 size_t fread (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

size_t read_file(const char *path, u8 **ptr) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "failed to open file %s\n", path);
        exit(1);
    }

    fseek(f, 0L, SEEK_END);
    size_t size = ftell(f);
    rewind(f);

    *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "failed to allocate memory to hold %s\n", path);
        exit(1);
    }

    size_t pos = 0;
    while (!feof(f)) {
        size_t read = fread(&(*ptr)[pos], 1, size, f);
        if (ferror(f)) {
            fprintf(stderr, "error while reading file %s\n", path);
            exit(1);
        }
        pos += read;
    }

    fclose(f);

    return pos;
}