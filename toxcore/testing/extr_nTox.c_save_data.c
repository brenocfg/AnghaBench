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
typedef  int /*<<< orphan*/  Tox ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  data_file_name ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 size_t fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tox_get_savedata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t tox_get_savedata_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int save_data(Tox *m)
{
    FILE *data_file = fopen(data_file_name, "w");

    if (!data_file) {
        perror("[!] load_key");
        return 0;
    }

    int res = 1;
    size_t size = tox_get_savedata_size(m);
    uint8_t data[size];
    tox_get_savedata(m, data);

    if (fwrite(data, sizeof(uint8_t), size, data_file) != size) {
        fputs("[!] could not write data file (1)!", stderr);
        res = 0;
    }

    if (fclose(data_file) < 0) {
        perror("[!] could not write data file (2)");
        res = 0;
    }

    return res;
}