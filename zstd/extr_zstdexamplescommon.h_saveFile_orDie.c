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
 int /*<<< orphan*/  ERROR_fclose ; 
 int /*<<< orphan*/  ERROR_fwrite ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen_orDie (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void saveFile_orDie(const char* fileName, const void* buff, size_t buffSize)
{
    FILE* const oFile = fopen_orDie(fileName, "wb");
    size_t const wSize = fwrite(buff, 1, buffSize, oFile);
    if (wSize != (size_t)buffSize) {
        fprintf(stderr, "fwrite: %s : %s \n", fileName, strerror(errno));
        exit(ERROR_fwrite);
    }
    if (fclose(oFile)) {
        perror(fileName);
        exit(ERROR_fclose);
    }
}