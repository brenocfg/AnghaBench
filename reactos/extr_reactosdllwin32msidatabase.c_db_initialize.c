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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_Commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_SetClass (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_init_string_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_stream_data (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT db_initialize( IStorage *stg, const GUID *clsid )
{
    static const WCHAR szTables[]  = { '_','T','a','b','l','e','s',0 };
    HRESULT hr;

    hr = IStorage_SetClass( stg, clsid );
    if (FAILED( hr ))
    {
        WARN("failed to set class id 0x%08x\n", hr);
        return hr;
    }

    /* create the _Tables stream */
    hr = write_stream_data( stg, szTables, NULL, 0, TRUE );
    if (FAILED( hr ))
    {
        WARN("failed to create _Tables stream 0x%08x\n", hr);
        return hr;
    }

    hr = msi_init_string_table( stg );
    if (FAILED( hr ))
    {
        WARN("failed to initialize string table 0x%08x\n", hr);
        return hr;
    }

    hr = IStorage_Commit( stg, 0 );
    if (FAILED( hr ))
    {
        WARN("failed to commit changes 0x%08x\n", hr);
        return hr;
    }

    return S_OK;
}