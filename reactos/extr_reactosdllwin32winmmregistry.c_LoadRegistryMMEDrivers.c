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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  char* INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  char* BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 char* FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  MMDRV_Install (char*,char*,char*) ; 
 scalar_t__ REG_SZ ; 
 scalar_t__ RegEnumValue (int /*<<< orphan*/ ,char*,char*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 char* TRUE ; 
 int /*<<< orphan*/  _strnicmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  stricmp (char*,char*) ; 

BOOL LoadRegistryMMEDrivers(char* key)
{
    INT driver_count = 0;
    INT driver_index = 0;
    HKEY drivers_key;

    DWORD value_name_length = 256;
    char value_name[256];

    DWORD value_data_length = 256;
    char value_data[256];

    char wavemapper[256] = { 0 };
    char midimapper[256] = { 0 };

    DWORD value_type;

    if ( RegOpenKeyA(HKEY_LOCAL_MACHINE, key, &drivers_key) != ERROR_SUCCESS )
    {
        TRACE("ERROR: Could not open: HKEY_LOCAL_MACHINE\\%s\n", key);
        return 0;
    }

    while ( RegEnumValue(drivers_key,
                         driver_index,
                         value_name,
                         &value_name_length,
                         NULL,
                         &value_type,
                         (LPBYTE)value_data,
                         &value_data_length) == ERROR_SUCCESS )
    {
        BOOL valid_driver = FALSE;
        BOOL is_mapper = FALSE;

        if ( value_type == REG_SZ )
        {
            /* We look for mappers first so they don't match
               something else later on! */

            if ( ! stricmp("wavemapper", value_name) )
            {
                TRACE("Found a Wave-mapper: %s\n", value_data);
                /* Delay loading Wave mapper driver */
                strcpy(wavemapper, value_data);
                is_mapper = TRUE;
                driver_count ++;
            }
            else if ( ! stricmp("midimapper", value_name) )
            {
                TRACE("Found a MIDI-mapper: %s\n", value_data);
                /* Delay loading MIDI mapper driver */
                strcpy(midimapper, value_data);
                is_mapper = TRUE;
                driver_count ++;
            }
            else if ( ! _strnicmp("wave", value_name, 4) )
            {
                TRACE("Found a Wave driver: %s\n", value_data);
                valid_driver = TRUE;
                driver_count ++;
            }
            else if ( ! _strnicmp("midi", value_name, 4) )
            {
                TRACE("Found a MIDI driver: %s\n", value_data);
                valid_driver = TRUE;
                driver_count ++;
            }
            else if ( ! _strnicmp("mixer", value_name, 5) )
            {
                TRACE("Found a mixer driver: %s\n", value_data);
                valid_driver = TRUE;
                driver_count ++;
            }
            else if ( ! _strnicmp("aux", value_name, 4) )
            {
                TRACE("Found an aux driver: %s\n", value_data);
                valid_driver = TRUE;
                driver_count ++;
            }
            else
            {
                TRACE("Not supported: %s\n", value_data);
            }

            /* If we have a valid driver now, we get it "installed" in
               winmm itself so it can be used */

            if ( valid_driver )
            {
                if ( ! MMDRV_Install(value_name, value_data, is_mapper) )
                {
                    TRACE("FAILED when initializing %s\n", value_data);
                }
            }
        }
        else
        {
            TRACE("Invalid data format\n");
        }

        /* Reinitialize */
        value_name_length = 256;
        value_data_length = 256;
        memset(value_name, 0, value_name_length);
        memset(value_data, 0, value_data_length);

        driver_index ++;
    }

    /* Finally load mapper drivers, since they expect device drivers already loaded */
    if (*wavemapper)
    {
        if (!MMDRV_Install("wavemapper", wavemapper, TRUE))
        {
            TRACE("FAILED when initializing %s\n", wavemapper);
        }
    }

    if (*midimapper)
    {
        if (!MMDRV_Install("midimapper", midimapper, TRUE))
        {
            TRACE("FAILED when initializing %s\n", midimapper);
        }
    }

    TRACE("Found a total of %d drivers\n", driver_count);

    return driver_count;
}