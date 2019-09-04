#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  strings; int /*<<< orphan*/  bytes_per_strref; int /*<<< orphan*/  transforms; int /*<<< orphan*/  tables; void* deletefile; scalar_t__ mode; int /*<<< orphan*/ * storage; int /*<<< orphan*/  media_transform_disk_id; int /*<<< orphan*/  media_transform_offset; void* path; } ;
struct TYPE_6__ {int /*<<< orphan*/  clsid; } ;
typedef  TYPE_1__ STATSTG ;
typedef  TYPE_2__ MSIDATABASE ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_MsiDatabase ; 
 int /*<<< orphan*/  CLSID_MsiPatch ; 
 int /*<<< orphan*/  CLSID_MsiTransform ; 
 int /*<<< orphan*/  CopyFileW (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_OPEN_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_INTMSIDBOPEN (scalar_t__) ; 
 int /*<<< orphan*/  IStorage_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_Stat (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ MSIDBOPEN_CREATE ; 
 scalar_t__ MSIDBOPEN_CREATEDIRECT ; 
 scalar_t__ MSIDBOPEN_DIRECT ; 
 scalar_t__ MSIDBOPEN_PATCHFILE ; 
 scalar_t__ MSIDBOPEN_READONLY ; 
 scalar_t__ MSIDBOPEN_TRANSACT ; 
 int /*<<< orphan*/  MSIHANDLETYPE_DATABASE ; 
 int /*<<< orphan*/  MSI_CloseDatabase ; 
 int /*<<< orphan*/  MSI_INITIAL_MEDIA_TRANSFORM_DISKID ; 
 int /*<<< orphan*/  MSI_INITIAL_MEDIA_TRANSFORM_OFFSET ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 int STGM_CREATE ; 
 int STGM_DIRECT ; 
 int STGM_READ ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_DENY_WRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_TRANSACTED ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StgCreateDocfile (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  StgOpenStorage (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* alloc_msiobject (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 
 int /*<<< orphan*/  enum_stream_names (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msi ; 
 int /*<<< orphan*/  msi_load_string_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strchrW (scalar_t__,char) ; 
 void* strdupW (scalar_t__) ; 
 scalar_t__ szBackSlash ; 

UINT MSI_OpenDatabaseW(LPCWSTR szDBPath, LPCWSTR szPersist, MSIDATABASE **pdb)
{
    IStorage *stg = NULL;
    HRESULT r;
    MSIDATABASE *db = NULL;
    UINT ret = ERROR_FUNCTION_FAILED;
    LPCWSTR szMode, save_path;
    STATSTG stat;
    BOOL created = FALSE, patch = FALSE;
    WCHAR path[MAX_PATH];

    TRACE("%s %s\n",debugstr_w(szDBPath),debugstr_w(szPersist) );

    if( !pdb )
        return ERROR_INVALID_PARAMETER;

    if (szPersist - MSIDBOPEN_PATCHFILE <= MSIDBOPEN_CREATEDIRECT)
    {
        TRACE("Database is a patch\n");
        szPersist -= MSIDBOPEN_PATCHFILE;
        patch = TRUE;
    }

    save_path = szDBPath;
    szMode = szPersist;
    if( !IS_INTMSIDBOPEN(szPersist) )
    {
        if (!CopyFileW( szDBPath, szPersist, FALSE ))
            return ERROR_OPEN_FAILED;

        szDBPath = szPersist;
        szPersist = MSIDBOPEN_TRANSACT;
        created = TRUE;
    }

    if( szPersist == MSIDBOPEN_READONLY )
    {
        r = StgOpenStorage( szDBPath, NULL,
              STGM_DIRECT|STGM_READ|STGM_SHARE_DENY_WRITE, NULL, 0, &stg);
    }
    else if( szPersist == MSIDBOPEN_CREATE )
    {
        r = StgCreateDocfile( szDBPath,
              STGM_CREATE|STGM_TRANSACTED|STGM_READWRITE|STGM_SHARE_EXCLUSIVE, 0, &stg );

        if( SUCCEEDED(r) )
            r = db_initialize( stg, patch ? &CLSID_MsiPatch : &CLSID_MsiDatabase );
        created = TRUE;
    }
    else if( szPersist == MSIDBOPEN_CREATEDIRECT )
    {
        r = StgCreateDocfile( szDBPath,
              STGM_CREATE|STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE, 0, &stg );

        if( SUCCEEDED(r) )
            r = db_initialize( stg, patch ? &CLSID_MsiPatch : &CLSID_MsiDatabase );
        created = TRUE;
    }
    else if( szPersist == MSIDBOPEN_TRANSACT )
    {
        r = StgOpenStorage( szDBPath, NULL,
              STGM_TRANSACTED|STGM_READWRITE|STGM_SHARE_DENY_WRITE, NULL, 0, &stg);
    }
    else if( szPersist == MSIDBOPEN_DIRECT )
    {
        r = StgOpenStorage( szDBPath, NULL,
              STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE, NULL, 0, &stg);
    }
    else
    {
        ERR("unknown flag %p\n",szPersist);
        return ERROR_INVALID_PARAMETER;
    }

    if( FAILED( r ) || !stg )
    {
        WARN("open failed r = %08x for %s\n", r, debugstr_w(szDBPath));
        return ERROR_FUNCTION_FAILED;
    }

    r = IStorage_Stat( stg, &stat, STATFLAG_NONAME );
    if( FAILED( r ) )
    {
        FIXME("Failed to stat storage\n");
        goto end;
    }

    if ( !IsEqualGUID( &stat.clsid, &CLSID_MsiDatabase ) &&
         !IsEqualGUID( &stat.clsid, &CLSID_MsiPatch ) &&
         !IsEqualGUID( &stat.clsid, &CLSID_MsiTransform ) )
    {
        ERR("storage GUID is not a MSI database GUID %s\n",
             debugstr_guid(&stat.clsid) );
        goto end;
    }

    if ( patch && !IsEqualGUID( &stat.clsid, &CLSID_MsiPatch ) )
    {
        ERR("storage GUID is not the MSI patch GUID %s\n",
             debugstr_guid(&stat.clsid) );
        ret = ERROR_OPEN_FAILED;
        goto end;
    }

    db = alloc_msiobject( MSIHANDLETYPE_DATABASE, sizeof (MSIDATABASE),
                              MSI_CloseDatabase );
    if( !db )
    {
        FIXME("Failed to allocate a handle\n");
        goto end;
    }

    if (!strchrW( save_path, '\\' ))
    {
        GetCurrentDirectoryW( MAX_PATH, path );
        lstrcatW( path, szBackSlash );
        lstrcatW( path, save_path );
    }
    else
        lstrcpyW( path, save_path );

    db->path = strdupW( path );
    db->media_transform_offset = MSI_INITIAL_MEDIA_TRANSFORM_OFFSET;
    db->media_transform_disk_id = MSI_INITIAL_MEDIA_TRANSFORM_DISKID;

    if( TRACE_ON( msi ) )
        enum_stream_names( stg );

    db->storage = stg;
    db->mode = szMode;
    if (created)
        db->deletefile = strdupW( szDBPath );
    list_init( &db->tables );
    list_init( &db->transforms );

    db->strings = msi_load_string_table( stg, &db->bytes_per_strref );
    if( !db->strings )
        goto end;

    ret = ERROR_SUCCESS;

    msiobj_addref( &db->hdr );
    IStorage_AddRef( stg );
    *pdb = db;

end:
    if( db )
        msiobj_release( &db->hdr );
    if( stg )
        IStorage_Release( stg );

    return ret;
}