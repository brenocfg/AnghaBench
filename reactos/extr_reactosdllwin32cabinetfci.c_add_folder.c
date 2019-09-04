#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int handle; } ;
struct folder {int /*<<< orphan*/  entry; int /*<<< orphan*/  blocks_list; int /*<<< orphan*/  files_list; int /*<<< orphan*/  compression; scalar_t__ data_count; int /*<<< orphan*/  data_start; TYPE_1__ data; } ;
struct TYPE_7__ {scalar_t__ cbReserveCFFolder; } ;
struct TYPE_8__ {int /*<<< orphan*/  cFolders; TYPE_2__ ccab; int /*<<< orphan*/  folders_size; int /*<<< orphan*/  folders_list; int /*<<< orphan*/  compression; int /*<<< orphan*/  folders_data_size; struct folder* (* alloc ) (int) ;} ;
typedef  TYPE_3__ FCI_Int ;
typedef  int /*<<< orphan*/  CFFOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  FCIERR_ALLOC_FAIL ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct folder* stub1 (int) ; 

__attribute__((used)) static struct folder *add_folder( FCI_Int *fci )
{
    struct folder *folder = fci->alloc( sizeof(*folder) );

    if (!folder)
    {
        set_error( fci, FCIERR_ALLOC_FAIL, ERROR_NOT_ENOUGH_MEMORY );
        return NULL;
    }
    folder->data.handle = -1;
    folder->data_start  = fci->folders_data_size;
    folder->data_count  = 0;
    folder->compression = fci->compression;
    list_init( &folder->files_list );
    list_init( &folder->blocks_list );
    list_add_tail( &fci->folders_list, &folder->entry );
    fci->folders_size += sizeof(CFFOLDER) + fci->ccab.cbReserveCFFolder;
    fci->cFolders++;
    return folder;
}