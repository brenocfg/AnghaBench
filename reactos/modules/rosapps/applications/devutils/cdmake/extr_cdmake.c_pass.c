#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int header_id; int platform_id; } ;
struct TYPE_15__ {int sector; int offset; int /*<<< orphan*/ * file; } ;
struct TYPE_14__ {int boot_id; int boot_emu_type; int load_segment; int sector_count; int load_rba; char const* bootimage; } ;
struct TYPE_13__ {int boot_id; int boot_emu_type; int load_segment; int sector_count; int load_rba; char const* bootimage; struct TYPE_13__* next_entry; } ;
struct TYPE_12__ {int header_id; int platform_id; int num_entries; struct TYPE_12__* next_header; TYPE_3__* entry_list; } ;
struct TYPE_11__ {int sector; int path_table_index; char* name_on_cd; int joliet_sector; char* joliet_name; int flags; int size; int joliet_size; char* orig_name; struct TYPE_11__* next_in_directory; struct TYPE_11__* first_record; struct TYPE_11__* parent; struct TYPE_11__* next_in_path_table; } ;
typedef  TYPE_1__* PDIR_RECORD ;
typedef  TYPE_2__* PBOOT_HEADER ;
typedef  TYPE_3__* PBOOT_ENTRY ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 char* APP_ID ; 
 char* DATA_PREP_ID ; 
 int DIRECTORY_FLAG ; 
 int /*<<< orphan*/  DOT_DOT_RECORD ; 
 int /*<<< orphan*/  DOT_RECORD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_RECORD ; 
 char* MANUFACTURER_ID ; 
 char* PUBLISHER_ID ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SUBDIRECTORY_RECORD ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VERBOSE ; 
 int big_endian_path_table_sector ; 
 int boot_catalog_sector ; 
 TYPE_2__* boot_header_list ; 
 TYPE_9__ boot_validation_header ; 
 int bytes_in_directories ; 
 int bytes_in_files ; 
 TYPE_8__ cd ; 
 TYPE_7__ default_boot_entry ; 
 scalar_t__ eltorito ; 
 char* end_source ; 
 int /*<<< orphan*/  error_exit (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_sector () ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_file_specifications (TYPE_1__*) ; 
 int /*<<< orphan*/  get_time_string (char*) ; 
 scalar_t__ joliet ; 
 int joliet_big_endian_path_table_sector ; 
 int joliet_little_endian_path_table_sector ; 
 int joliet_path_table_size ; 
 int little_endian_path_table_sector ; 
 scalar_t__ make_bridged_udf ; 
 int /*<<< orphan*/  number_of_directories ; 
 int /*<<< orphan*/  number_of_files ; 
 int path_table_size ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 TYPE_1__ root ; 
 char* source ; 
 int strlen (char*) ; 
 int total_sectors ; 
 int /*<<< orphan*/  unused_bytes_at_ends_of_files ; 
 scalar_t__ verbosity ; 
 char* volume_label ; 
 int /*<<< orphan*/  write_big_endian_dword (int) ; 
 int /*<<< orphan*/  write_big_endian_word (int) ; 
 int /*<<< orphan*/  write_block (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_both_endian_dword (int) ; 
 int /*<<< orphan*/  write_both_endian_word (int) ; 
 int /*<<< orphan*/  write_byte (int) ; 
 int /*<<< orphan*/  write_bytecounted_string (int,char*,char) ; 
 int /*<<< orphan*/  write_bytecounted_string_as_big_endian_unicode (int,char*,char) ; 
 int /*<<< orphan*/  write_directory_record (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_from_file (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_little_endian_dword (int) ; 
 int /*<<< orphan*/  write_little_endian_word (int) ; 
 int /*<<< orphan*/  write_string (char*) ; 
 int /*<<< orphan*/  write_string_as_big_endian_unicode (char*) ; 

__attribute__((used)) static void pass(void)
{
    PDIR_RECORD d, q;
    unsigned int index;
    unsigned int name_length;
    DWORD size;
    DWORD number_of_sectors;
    char *old_end_source;
    FILE *file;

    PBOOT_HEADER header;
    PBOOT_ENTRY  entry;

    char timestring[17];

    get_time_string(timestring);

    // first 16 sectors are zeros
    write_block(16 * SECTOR_SIZE, 0);


    // Primary Volume Descriptor
    if (make_bridged_udf)
    {
        write_string("\1CD001\1");
        write_byte(0);
        write_bytecounted_string(32, "", ' ');           // system identifier
        write_bytecounted_string(32, volume_label, ' '); // volume label

        write_block(8, 0);
        write_both_endian_dword(total_sectors);
        write_block(32, 0);
        write_both_endian_word(1); // volume set size
        write_both_endian_word(1); // volume sequence number
        write_both_endian_word(2048); // sector size
        write_both_endian_dword(path_table_size);
        write_little_endian_dword(little_endian_path_table_sector);
        write_little_endian_dword(0);  // second little endian path table
        write_big_endian_dword(big_endian_path_table_sector);
        write_big_endian_dword(0);  // second big endian path table
        write_directory_record(&root, DOT_RECORD, FALSE);

        write_bytecounted_string(128, volume_label, ' '); // volume set identifier
        write_bytecounted_string(128, PUBLISHER_ID, ' '); // publisher identifier
        write_bytecounted_string(128, DATA_PREP_ID, ' '); // data preparer identifier
        write_bytecounted_string(128, APP_ID, ' ');       // application identifier

        write_bytecounted_string(37, "", ' '); // copyright file identifier
        write_bytecounted_string(37, "", ' '); // abstract file identifier
        write_bytecounted_string(37, "", ' '); // bibliographic file identifier

        write_string(timestring);  // volume creation
        write_byte(0);
        write_string(timestring);  // most recent modification
        write_byte(0);
        write_string("0000000000000000");  // volume expires
        write_byte(0);
        write_string("0000000000000000");  // volume is effective
        write_byte(0);
        write_byte(1);
        write_byte(0);
        fill_sector();
    }

    // Boot Volume Descriptor
    if (eltorito)
    {
        write_byte(0);  // Boot record ID
        write_string("CD001\1");
        write_bytecounted_string(32, "EL TORITO SPECIFICATION", 0); // El-Torito identifier
        write_block(32, 0);  // unused
        write_little_endian_dword(boot_catalog_sector);  // pointer to boot catalog
        fill_sector();
    }

    // Supplementary Volume Descriptor
    if (joliet)
    {
        write_string("\2CD001\1");
        write_byte(0);
        write_bytecounted_string_as_big_endian_unicode(32, "", ' ');           // system identifier
        write_bytecounted_string_as_big_endian_unicode(32, volume_label, ' '); // volume label

        write_block(8, 0);
        write_both_endian_dword(total_sectors);
        write_string("%/E");
        write_block(29, 0);
        write_both_endian_word(1); // volume set size
        write_both_endian_word(1); // volume sequence number
        write_both_endian_word(2048); // sector size
        write_both_endian_dword(joliet_path_table_size);
        write_little_endian_dword(joliet_little_endian_path_table_sector);
        write_little_endian_dword(0);  // second little endian path table
        write_big_endian_dword(joliet_big_endian_path_table_sector);
        write_big_endian_dword(0);  // second big endian path table
        write_directory_record(&root, DOT_RECORD, TRUE);

        write_bytecounted_string_as_big_endian_unicode(128, volume_label, ' '); // volume set identifier
        write_bytecounted_string_as_big_endian_unicode(128, PUBLISHER_ID, ' '); // publisher identifier
        write_bytecounted_string_as_big_endian_unicode(128, DATA_PREP_ID, ' '); // data preparer identifier
        write_bytecounted_string_as_big_endian_unicode(128, APP_ID, ' ');       // application identifier

        write_bytecounted_string_as_big_endian_unicode(37, "", ' '); // copyright file identifier
        write_bytecounted_string_as_big_endian_unicode(37, "", ' '); // abstract file identifier
        write_bytecounted_string_as_big_endian_unicode(37, "", ' '); // bibliographic file identifier

        write_string(timestring);  // volume creation
        write_byte(0);
        write_string(timestring);  // most recent modification
        write_byte(0);
        write_string("0000000000000000");  // volume expires
        write_byte(0);
        write_string("0000000000000000");  // volume is effective
        write_byte(0);
        write_byte(1);
        write_byte(0);
        fill_sector();
    }

    // Volume Descriptor Set Terminator
    if (make_bridged_udf)
    {
        write_string("\377CD001\1");
        fill_sector();
    }

    // TODO: Add UDF support!

    // Boot Catalog
    if (eltorito)
    {
        boot_catalog_sector = cd.sector;

        // Validation entry header
        write_byte(boot_validation_header.header_id);
        write_byte(boot_validation_header.platform_id);
        write_little_endian_word(0);  // reserved
        write_bytecounted_string(24, MANUFACTURER_ID, 0); // Manufacturer identifier
        write_little_endian_word(0x62E);  // checksum // FIXME: This is hardcoded!!
        write_little_endian_word(0xAA55);  // signature

        // Default entry
        write_byte(default_boot_entry.boot_id);
        write_byte(default_boot_entry.boot_emu_type);
        write_little_endian_word(default_boot_entry.load_segment);
        write_byte(0);  // partition type
        write_byte(0);  // unused
        write_little_endian_word(default_boot_entry.sector_count);
        write_little_endian_dword(default_boot_entry.load_rba);
        write_block(20, 0); // unused

        // Loop through each boot header
        header = boot_header_list;
        while (header)
        {
            write_byte(header->header_id);
            write_byte(header->platform_id);
            write_little_endian_word(header->num_entries);
            write_block(28, 0); // Identifier string (unused)

            // Loop through each boot entry
            entry = header->entry_list;
            while (entry)
            {
                write_byte(entry->boot_id);
                write_byte(entry->boot_emu_type);
                write_little_endian_word(entry->load_segment);
                write_byte(0);  // partition type
                write_byte(0);  // unused
                write_little_endian_word(entry->sector_count);
                write_little_endian_dword(entry->load_rba);
                write_block(20, 0); // Selection criteria (unused)

                entry = entry->next_entry;
            }

            header = header->next_header;
        }

        fill_sector();
    }


    // Boot Images
    if (eltorito)
    {
        default_boot_entry.load_rba = cd.sector;

        file = fopen(default_boot_entry.bootimage, "rb");
        if (file == NULL)
            error_exit("Cannot open '%s'\n", default_boot_entry.bootimage);
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        if (size == 0 || (size % 2048))
        {
            fclose(file);
            error_exit("Invalid boot image size (%lu bytes)\n", size);
        }
        // Sector count in 512 byte sectors and rounded up
        default_boot_entry.sector_count = (size + 511) / 512;
        if (!write_from_file(file, size))
        {
            fclose(file);
            error_exit("Read error in file '%s'\n", default_boot_entry.bootimage);
        }
        fclose(file);

        // Loop through each boot header
        header = boot_header_list;
        while (header)
        {
            // Loop through each boot entry
            entry = header->entry_list;
            while (entry)
            {
                entry->load_rba = cd.sector;

                file = fopen(entry->bootimage, "rb");
                if (file == NULL)
                    error_exit("Cannot open '%s'\n", entry->bootimage);
                fseek(file, 0, SEEK_END);
                size = ftell(file);
                if (size == 0 || (size % 2048))
                {
                    fclose(file);
                    error_exit("Invalid boot image size (%lu bytes)\n", size);
                }
                // Sector count in 512 byte sectors and rounded up
                entry->sector_count = (size + 511) / 512;
                if (!write_from_file(file, size))
                {
                    fclose(file);
                    error_exit("Read error in file '%s'\n", entry->bootimage);
                }
                fclose(file);

                entry = entry->next_entry;
            }

            header = header->next_header;
        }

//      fill_sector();
    }


    // Little Endian Path Table

    little_endian_path_table_sector = cd.sector;
    write_byte(1);
    write_byte(0);  // number of sectors in extended attribute record
    write_little_endian_dword(root.sector);
    write_little_endian_word(1);
    write_byte(0);
    write_byte(0);

    index = 1;
    root.path_table_index = 1;
    for (d = root.next_in_path_table; d != NULL; d = d->next_in_path_table)
    {
        name_length = strlen(d->name_on_cd);
        write_byte((BYTE)name_length);
        write_byte(0);  // number of sectors in extended attribute record
        write_little_endian_dword(d->sector);
        write_little_endian_word(d->parent->path_table_index);
        write_string(d->name_on_cd);
        if (name_length & 1)
            write_byte(0);
        d->path_table_index = ++index;
    }

    path_table_size = (cd.sector - little_endian_path_table_sector) *
                       SECTOR_SIZE + cd.offset;
    fill_sector();


    // Big Endian Path Table

    big_endian_path_table_sector = cd.sector;
    write_byte(1);
    write_byte(0);  // number of sectors in extended attribute record
    write_big_endian_dword(root.sector);
    write_big_endian_word(1);
    write_byte(0);
    write_byte(0);

    for (d = root.next_in_path_table; d != NULL; d = d->next_in_path_table)
    {
        name_length = strlen(d->name_on_cd);
        write_byte((BYTE)name_length);
        write_byte(0);  // number of sectors in extended attribute record
        write_big_endian_dword(d->sector);
        write_big_endian_word(d->parent->path_table_index);
        write_string(d->name_on_cd);
        if (name_length & 1)
            write_byte(0);
    }
    fill_sector();

    if (joliet)
    {
        // Little Endian Path Table

        joliet_little_endian_path_table_sector = cd.sector;
        write_byte(1);
        write_byte(0);  // number of sectors in extended attribute record
        write_little_endian_dword(root.joliet_sector);
        write_little_endian_word(1);
        write_byte(0);
        write_byte(0);

        for (d = root.next_in_path_table; d != NULL; d = d->next_in_path_table)
        {
            name_length = strlen(d->joliet_name) * 2;
            write_byte((BYTE)name_length);
            write_byte(0);  // number of sectors in extended attribute record
            write_little_endian_dword(d->joliet_sector);
            write_little_endian_word(d->parent->path_table_index);
            write_string_as_big_endian_unicode(d->joliet_name);
        }

        joliet_path_table_size = (cd.sector - joliet_little_endian_path_table_sector) *
                                  SECTOR_SIZE + cd.offset;
        fill_sector();

        // Big Endian Path Table

        joliet_big_endian_path_table_sector = cd.sector;
        write_byte(1);
        write_byte(0);  // number of sectors in extended attribute record
        write_big_endian_dword(root.joliet_sector);
        write_big_endian_word(1);
        write_byte(0);
        write_byte(0);

        for (d = root.next_in_path_table; d != NULL; d = d->next_in_path_table)
        {
            name_length = strlen(d->joliet_name) * 2;
            write_byte((BYTE)name_length);
            write_byte(0);  // number of sectors in extended attribute record
            write_big_endian_dword(d->joliet_sector);
            write_big_endian_word(d->parent->path_table_index);
            write_string_as_big_endian_unicode(d->joliet_name);
        }
        fill_sector();
    }

    // TODO: Add UDF support!

#if 0
    // Boot Images ??
#endif

    // TODO: Add CRC block for header!

    // Directories and files
    for (d = &root; d != NULL; d = d->next_in_path_table)
    {
        // write directory
        d->sector = cd.sector;
        write_directory_record(d, DOT_RECORD, FALSE);
        write_directory_record(d == &root ? d : d->parent, DOT_DOT_RECORD, FALSE);
        for (q = d->first_record; q != NULL; q = q->next_in_directory)
        {
            write_directory_record(q,
                                   q->flags & DIRECTORY_FLAG ? SUBDIRECTORY_RECORD : FILE_RECORD,
                                   FALSE);
        }
        fill_sector();
        d->size = (cd.sector - d->sector) * SECTOR_SIZE;

        // write directory for joliet
        if (joliet)
        {
            d->joliet_sector = cd.sector;
            write_directory_record(d, DOT_RECORD, TRUE);
            write_directory_record(d == &root ? d : d->parent, DOT_DOT_RECORD, TRUE);
            for (q = d->first_record; q != NULL; q = q->next_in_directory)
            {
                write_directory_record(q,
                                       q->flags & DIRECTORY_FLAG ? SUBDIRECTORY_RECORD : FILE_RECORD,
                                       TRUE);
            }
            fill_sector();
            d->joliet_size = (cd.sector - d->joliet_sector) * SECTOR_SIZE;
            bytes_in_directories += d->joliet_size;
        }

        number_of_directories++;
        bytes_in_directories += d->size;

        // write file data
        for (q = d->first_record; q != NULL; q = q->next_in_directory)
        {
            if ((q->flags & DIRECTORY_FLAG) == 0)
            {
                q->sector = q->joliet_sector = cd.sector;
                size = q->size;
                if (cd.file == NULL)
                {
                    number_of_sectors = (size + SECTOR_SIZE - 1) / SECTOR_SIZE;
                    cd.sector += number_of_sectors;
                    number_of_files++;
                    bytes_in_files += size;
                    unused_bytes_at_ends_of_files +=
                    number_of_sectors * SECTOR_SIZE - size;
                }
                else
                {
                    const char *file_source;
                    old_end_source = end_source;
                    if (!q->orig_name)
                    {
                        get_file_specifications(q);
                        *end_source = 0;
                        file_source = source;
                    }
                    else
                    {
                        file_source = q->orig_name;
                    }
                    if (verbosity == VERBOSE)
                        printf("Writing contents of %s\n", file_source);
                    file = fopen(file_source, "rb");
                    if (file == NULL)
                        error_exit("Cannot open '%s'\n", file_source);
                    if (!write_from_file(file, size))
                    {
                        fclose(file);
                        error_exit("Read error in file '%s'\n", file_source);
                    }
                    fclose(file);
                    end_source = old_end_source;
                    fill_sector();
                }
            }
        }
    }

    // TODO: Add final CRC block!

    total_sectors = (DWORD)cd.sector;
}