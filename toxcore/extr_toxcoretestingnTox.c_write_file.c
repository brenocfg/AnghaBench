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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Tox ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fwrite (int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_lines (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

void write_file(Tox *tox, uint32_t friendnumber, uint32_t filenumber, uint64_t position, const uint8_t *data,
                size_t length, void *user_data)
{
    if (length == 0) {
        char msg[512];
        sprintf(msg, "[t] %u file transfer: %u completed", friendnumber, filenumber);
        new_lines(msg);
        return;
    }

    char filename[256];
    sprintf(filename, "%u.%u.bin", friendnumber, filenumber);
    FILE *pFile = fopen(filename, "r+b");

    if (pFile == NULL)
        pFile = fopen(filename, "wb");

    fseek(pFile, position, SEEK_SET);

    if (fwrite(data, length, 1, pFile) != 1)
        new_lines("Error writing to file");

    fclose(pFile);
}