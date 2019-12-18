#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ i_cmd_r; scalar_t__ i_cmd_w; struct TYPE_6__* psz_file; int /*<<< orphan*/  p_filew; int /*<<< orphan*/  p_filer; struct TYPE_6__* p_cmd; } ;
typedef  TYPE_1__ ts_storage_t ;
typedef  int /*<<< orphan*/  ts_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CmdClean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TsStoragePopCmd (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_unlink (TYPE_1__*) ; 

__attribute__((used)) static void TsStorageDelete( ts_storage_t *p_storage )
{
    while( p_storage->i_cmd_r < p_storage->i_cmd_w )
    {
        ts_cmd_t cmd;

        TsStoragePopCmd( p_storage, &cmd, true );

        CmdClean( &cmd );
    }
    free( p_storage->p_cmd );

    fclose( p_storage->p_filer );
    fclose( p_storage->p_filew );
#ifdef _WIN32
    vlc_unlink( p_storage->psz_file );
    free( p_storage->psz_file );
#endif
    free( p_storage );
}