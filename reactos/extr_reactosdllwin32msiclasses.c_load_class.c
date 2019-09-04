#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_13__ {int /*<<< orphan*/  action; void* Attributes; int /*<<< orphan*/  Feature; int /*<<< orphan*/  Argument; void* DefInprocHandler32; void* DefInprocHandler; void* IconPath; void* FileTypeMask; int /*<<< orphan*/  AppID; void* Description; void* ProgIDText; int /*<<< orphan*/  ProgID; int /*<<< orphan*/  Component; void* Context; void* clsid; int /*<<< orphan*/  entry; } ;
struct TYPE_12__ {int /*<<< orphan*/  classes; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSICLASS ;
typedef  void* LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  void* INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  INSTALLSTATE_UNKNOWN ; 
 int MSI_NULL_INTEGER ; 
 void* MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSI_RecordIsNull (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  deformat_string (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_given_appid (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  load_given_progid (TYPE_1__*,void*) ; 
 void* msi_alloc (int) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 void* msi_build_icon_path (TYPE_1__*,scalar_t__) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_free (void*) ; 
 int /*<<< orphan*/  msi_get_loaded_component (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  msi_get_loaded_feature (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  msi_reduce_to_long_filename (void*) ; 
 int /*<<< orphan*/  sprintfW (void*,char const*,void*,void*) ; 
 void* strdupW (char const*) ; 
 int strlenW (void*) ; 

__attribute__((used)) static MSICLASS *load_class( MSIPACKAGE* package, MSIRECORD *row )
{
    MSICLASS *cls;
    DWORD i;
    LPCWSTR buffer;

    /* fill in the data */

    cls = msi_alloc_zero( sizeof(MSICLASS) );
    if (!cls)
        return NULL;

    list_add_tail( &package->classes, &cls->entry );

    cls->clsid = msi_dup_record_field( row, 1 );
    TRACE("loading class %s\n",debugstr_w(cls->clsid));
    cls->Context = msi_dup_record_field( row, 2 );
    buffer = MSI_RecordGetString(row,3);
    cls->Component = msi_get_loaded_component( package, buffer );

    cls->ProgIDText = msi_dup_record_field(row,4);
    cls->ProgID = load_given_progid(package, cls->ProgIDText);

    cls->Description = msi_dup_record_field(row,5);

    buffer = MSI_RecordGetString(row,6);
    if (buffer)
        cls->AppID = load_given_appid(package, buffer);

    cls->FileTypeMask = msi_dup_record_field(row,7);

    if (!MSI_RecordIsNull(row,9))
    {

        INT icon_index = MSI_RecordGetInteger(row,9); 
        LPCWSTR FileName = MSI_RecordGetString(row,8);
        LPWSTR FilePath;
        static const WCHAR fmt[] = {'%','s',',','%','i',0};

        FilePath = msi_build_icon_path(package, FileName);
       
        cls->IconPath = msi_alloc( (strlenW(FilePath)+5)* sizeof(WCHAR) );

        sprintfW(cls->IconPath,fmt,FilePath,icon_index);

        msi_free(FilePath);
    }
    else
    {
        buffer = MSI_RecordGetString(row,8);
        if (buffer)
            cls->IconPath = msi_build_icon_path(package, buffer);
    }

    if (!MSI_RecordIsNull(row,10))
    {
        i = MSI_RecordGetInteger(row,10);
        if (i != MSI_NULL_INTEGER && i > 0 &&  i < 4)
        {
            static const WCHAR ole2[] = {'o','l','e','2','.','d','l','l',0};
            static const WCHAR ole32[] = {'o','l','e','3','2','.','d','l','l',0};

            switch(i)
            {
                case 1:
                    cls->DefInprocHandler = strdupW(ole2);
                    break;
                case 2:
                    cls->DefInprocHandler32 = strdupW(ole32);
                    break;
                case 3:
                    cls->DefInprocHandler = strdupW(ole2);
                    cls->DefInprocHandler32 = strdupW(ole32);
                    break;
            }
        }
        else
        {
            cls->DefInprocHandler32 = msi_dup_record_field( row, 10 );
            msi_reduce_to_long_filename( cls->DefInprocHandler32 );
        }
    }
    buffer = MSI_RecordGetString(row,11);
    deformat_string(package,buffer,&cls->Argument);

    buffer = MSI_RecordGetString(row,12);
    cls->Feature = msi_get_loaded_feature(package, buffer);

    cls->Attributes = MSI_RecordGetInteger(row,13);
    cls->action = INSTALLSTATE_UNKNOWN;
    return cls;
}