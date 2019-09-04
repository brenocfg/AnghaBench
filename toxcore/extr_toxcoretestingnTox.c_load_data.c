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
struct Tox_Options {size_t savedata_length; int /*<<< orphan*/ * savedata_data; int /*<<< orphan*/  savedata_type; } ;
typedef  int /*<<< orphan*/  Tox ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  TOX_SAVEDATA_TYPE_TOX_SAVE ; 
 int /*<<< orphan*/  data_file_name ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 size_t fread (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * tox_new (struct Tox_Options*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_options_default (struct Tox_Options*) ; 

__attribute__((used)) static Tox *load_data()
{
    FILE *data_file = fopen(data_file_name, "r");

    if (data_file) {
        fseek(data_file, 0, SEEK_END);
        size_t size = ftell(data_file);
        rewind(data_file);

        uint8_t data[size];

        if (fread(data, sizeof(uint8_t), size, data_file) != size) {
            fputs("[!] could not read data file!\n", stderr);
            fclose(data_file);
            return 0;
        }

        struct Tox_Options options;

        tox_options_default(&options);

        options.savedata_type = TOX_SAVEDATA_TYPE_TOX_SAVE;

        options.savedata_data = data;

        options.savedata_length = size;

        Tox *m = tox_new(&options, NULL);

        if (fclose(data_file) < 0) {
            perror("[!] fclose failed");
            /* we got it open and the expected data read... let it be ok */
            /* return 0; */
        }

        return m;
    }

    return tox_new(NULL, NULL);
}