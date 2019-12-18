#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wine_trailerW ;
struct TYPE_5__ {scalar_t__ build; scalar_t__ revision; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct assembly_identity {char* language; TYPE_1__ version; int /*<<< orphan*/  public_key; int /*<<< orphan*/  name; int /*<<< orphan*/  arch; } ;
typedef  int /*<<< orphan*/  lookup_fmtW ;
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {char* FileName; int FileNameLength; scalar_t__ NextEntryOffset; } ;
struct TYPE_6__ {scalar_t__ Information; } ;
typedef  TYPE_2__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_3__ FILE_BOTH_DIR_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FileBothDirectoryInformation ; 
 scalar_t__ NtQueryDirectoryFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ atoiW (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memicmpW (char*,char const*,int) ; 
 int /*<<< orphan*/  neutralW ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* strchrW (char*,char) ; 
 int /*<<< orphan*/  strcmpiW (char const*,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ ) ; 
 char* wildcardW ; 

__attribute__((used)) static WCHAR *lookup_manifest_file( HANDLE dir, struct assembly_identity *ai )
{
    static const WCHAR lookup_fmtW[] =
        {'%','s','_','%','s','_','%','s','_','%','u','.','%','u','.','*','.','*','_',
         '%','s','_','*','.','m','a','n','i','f','e','s','t',0};
    static const WCHAR wine_trailerW[] = {'d','e','a','d','b','e','e','f','.','m','a','n','i','f','e','s','t'};

    WCHAR *lookup, *ret = NULL;
    UNICODE_STRING lookup_us;
    IO_STATUS_BLOCK io;
    const WCHAR *lang = ai->language;
    unsigned int data_pos = 0, data_len;
    char buffer[8192];

    if (!(lookup = RtlAllocateHeap( RtlGetProcessHeap(), 0,
                                    (strlenW(ai->arch) + strlenW(ai->name)
                                     + strlenW(ai->public_key) + 20) * sizeof(WCHAR)
                                    + sizeof(lookup_fmtW) )))
        return NULL;

    if (!lang || !strcmpiW( lang, neutralW )) lang = wildcardW;
    sprintfW( lookup, lookup_fmtW, ai->arch, ai->name, ai->public_key,
              ai->version.major, ai->version.minor, lang );
    RtlInitUnicodeString( &lookup_us, lookup );

    if (!NtQueryDirectoryFile( dir, 0, NULL, NULL, &io, buffer, sizeof(buffer),
                               FileBothDirectoryInformation, FALSE, &lookup_us, TRUE ))
    {
        ULONG min_build = ai->version.build, min_revision = ai->version.revision;
        FILE_BOTH_DIR_INFORMATION *dir_info;
        WCHAR *tmp;
        ULONG build, revision;

        data_len = (ULONG)io.Information;

        for (;;)
        {
            if (data_pos >= data_len)
            {
                if (NtQueryDirectoryFile( dir, 0, NULL, NULL, &io, buffer, sizeof(buffer),
                                          FileBothDirectoryInformation, FALSE, &lookup_us, FALSE ))
                    break;
                data_len = (ULONG)io.Information;
                data_pos = 0;
            }
            dir_info = (FILE_BOTH_DIR_INFORMATION*)(buffer + data_pos);

            if (dir_info->NextEntryOffset) data_pos += dir_info->NextEntryOffset;
            else data_pos = data_len;

            tmp = (WCHAR *)dir_info->FileName + (strchrW(lookup, '*') - lookup);
            build = atoiW(tmp);
            if (build < min_build) continue;
            tmp = strchrW(tmp, '.') + 1;
            revision = atoiW(tmp);
            if (build == min_build && revision < min_revision) continue;
            tmp = strchrW(tmp, '_') + 1;
            tmp = strchrW(tmp, '_') + 1;
            if (dir_info->FileNameLength - (tmp - dir_info->FileName) * sizeof(WCHAR) == sizeof(wine_trailerW) &&
                !memicmpW( tmp, wine_trailerW, sizeof(wine_trailerW) / sizeof(WCHAR) ))
            {
                /* prefer a non-Wine manifest if we already have one */
                /* we'll still load the builtin dll if specified through DllOverrides */
                if (ret) continue;
            }
            else
            {
                min_build = build;
                min_revision = revision;
            }
            ai->version.build = build;
            ai->version.revision = revision;
            RtlFreeHeap( RtlGetProcessHeap(), 0, ret );
            if ((ret = RtlAllocateHeap( RtlGetProcessHeap(), 0, dir_info->FileNameLength + sizeof(WCHAR) )))
            {
                memcpy( ret, dir_info->FileName, dir_info->FileNameLength );
                ret[dir_info->FileNameLength/sizeof(WCHAR)] = 0;
            }
        }
    }
    else DPRINT1("no matching file for %S\n", lookup);
    RtlFreeHeap( RtlGetProcessHeap(), 0, lookup );
    return ret;
}