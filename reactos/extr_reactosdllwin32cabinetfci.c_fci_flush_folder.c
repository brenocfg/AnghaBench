#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct folder {int dummy; } ;
typedef  scalar_t__ cab_ULONG ;
struct TYPE_13__ {scalar_t__ cbReserveCFFolder; scalar_t__ cb; } ;
struct TYPE_15__ {scalar_t__ fGetNextCabInVain; scalar_t__ fNextCab; scalar_t__ files_size; scalar_t__ pending_data_size; scalar_t__ placed_files_size; scalar_t__ folders_data_size; scalar_t__ folders_size; scalar_t__ cCompressedBytesInFolder; scalar_t__ cDataBlocks; scalar_t__ fSplitFolder; TYPE_2__* pccab; TYPE_1__ ccab; int /*<<< orphan*/  pv; scalar_t__ estimatedCabinetSize; scalar_t__ statusFolderTotal; scalar_t__ statusFolderCopied; } ;
struct TYPE_14__ {int /*<<< orphan*/  szDisk; int /*<<< orphan*/  szCab; int /*<<< orphan*/  iCab; } ;
typedef  int (* PFNFCISTATUS ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  (* PFNFCIGETNEXTCABINET ) (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ;
typedef  TYPE_3__ FCI_Int ;
typedef  int /*<<< orphan*/  CFFOLDER ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CB_MAX_CABINET_NAME ; 
 scalar_t__ CB_MAX_DISK_NAME ; 
 int /*<<< orphan*/  ERROR_BAD_ARGUMENTS ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_GEN_FAILURE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FCIERR_NONE ; 
 int /*<<< orphan*/  FCIERR_USER_ABORT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  add_data_block (TYPE_3__*,int (*) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  add_data_to_folder (TYPE_3__*,struct folder*,scalar_t__*,int (*) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  add_files_to_folder (TYPE_3__*,struct folder*,scalar_t__) ; 
 struct folder* add_folder (TYPE_3__*) ; 
 scalar_t__ get_header_size (TYPE_3__*) ; 
 int /*<<< orphan*/  set_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statusFolder ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL fci_flush_folder( FCI_Int *p_fci_internal,
	BOOL                  fGetNextCab,
	PFNFCIGETNEXTCABINET  pfnfcignc,
	PFNFCISTATUS          pfnfcis)
{
  cab_ULONG payload;
  cab_ULONG read_result;
  struct folder *folder;

  if ((!pfnfcignc) || (!pfnfcis)) {
    set_error( p_fci_internal, FCIERR_NONE, ERROR_BAD_ARGUMENTS );
    return FALSE;
  }

  if( p_fci_internal->fGetNextCabInVain &&
      p_fci_internal->fNextCab ){
    /* internal error */
    set_error( p_fci_internal, FCIERR_NONE, ERROR_GEN_FAILURE );
    return FALSE;
  }

  /* If there was no FCIAddFile or FCIFlushFolder has already been called */
  /* this function will return TRUE */
  if( p_fci_internal->files_size == 0 ) {
    if ( p_fci_internal->pending_data_size != 0 ) {
      /* error handling */
      set_error( p_fci_internal, FCIERR_NONE, ERROR_GEN_FAILURE );
      return FALSE;
    }
    return TRUE;
  }

  /* FCIFlushFolder has already been called... */
  if (p_fci_internal->fSplitFolder && p_fci_internal->placed_files_size!=0) {
    return TRUE;
  }

  /* This can be set already, because it makes only a difference */
  /* when the current function exits with return FALSE */
  p_fci_internal->fSplitFolder=FALSE;

  /* START of COPY */
  if (!add_data_block( p_fci_internal, pfnfcis )) return FALSE;

  /* reset to get the number of data blocks of this folder which are */
  /* actually in this cabinet ( at least partially ) */
  p_fci_internal->cDataBlocks=0;

  p_fci_internal->statusFolderTotal = get_header_size( p_fci_internal ) +
      sizeof(CFFOLDER) + p_fci_internal->ccab.cbReserveCFFolder +
      p_fci_internal->placed_files_size+
      p_fci_internal->folders_data_size + p_fci_internal->files_size+
      p_fci_internal->pending_data_size + p_fci_internal->folders_size;
  p_fci_internal->statusFolderCopied = 0;

  /* report status with pfnfcis about copied size of folder */
  if( (*pfnfcis)(statusFolder, p_fci_internal->statusFolderCopied,
      p_fci_internal->statusFolderTotal, /* TODO total folder size */
      p_fci_internal->pv) == -1) {
    set_error( p_fci_internal, FCIERR_USER_ABORT, 0 );
    return FALSE;
  }

  /* USE the variable read_result */
  read_result = get_header_size( p_fci_internal ) + p_fci_internal->folders_data_size +
      p_fci_internal->placed_files_size + p_fci_internal->folders_size;

  if(p_fci_internal->files_size!=0) {
    read_result+= sizeof(CFFOLDER)+p_fci_internal->ccab.cbReserveCFFolder;
  }

  /* Check if multiple cabinets have to be created. */

  /* Might be too much data for the maximum allowed cabinet size.*/
  /* When any further data will be added later, it might not */
  /* be possible to flush the cabinet, because there might */
  /* not be enough space to store the name of the following */
  /* cabinet and name of the corresponding disk. */
  /* So take care of this and get the name of the next cabinet */
  if( p_fci_internal->fGetNextCabInVain==FALSE &&
      p_fci_internal->fNextCab==FALSE &&
      (
        (
          p_fci_internal->ccab.cb < read_result +
          p_fci_internal->pending_data_size +
          p_fci_internal->files_size +
          CB_MAX_CABINET_NAME +   /* next cabinet name */
          CB_MAX_DISK_NAME        /* next disk name */
        ) || fGetNextCab
      )
  ) {
    /* increment cabinet index */
    ++(p_fci_internal->pccab->iCab);
    /* get name of next cabinet */
    p_fci_internal->estimatedCabinetSize=p_fci_internal->statusFolderTotal;
    if (!(*pfnfcignc)(p_fci_internal->pccab,
        p_fci_internal->estimatedCabinetSize, /* estimated size of cab */
        p_fci_internal->pv)) {
      set_error( p_fci_internal, FCIERR_NONE, ERROR_FUNCTION_FAILED );
      return FALSE;
    }

    /* Skip a few lines of code. This is caught by the next if. */
    p_fci_internal->fGetNextCabInVain=TRUE;
  }

  /* too much data for cabinet */
  if( (p_fci_internal->fGetNextCabInVain ||
        p_fci_internal->fNextCab ) &&
      (
        (
          p_fci_internal->ccab.cb < read_result +
          p_fci_internal->pending_data_size +
          p_fci_internal->files_size +
          strlen(p_fci_internal->pccab->szCab)+1 +   /* next cabinet name */
          strlen(p_fci_internal->pccab->szDisk)+1    /* next disk name */
        ) || fGetNextCab
      )
  ) {
    p_fci_internal->fGetNextCabInVain=FALSE;
    p_fci_internal->fNextCab=TRUE;

    /* return FALSE if there is not enough space left*/
    /* this should never happen */
    if (p_fci_internal->ccab.cb <=
        p_fci_internal->files_size +
        read_result +
        strlen(p_fci_internal->pccab->szCab)+1 + /* next cabinet name */
        strlen(p_fci_internal->pccab->szDisk)+1  /* next disk name */
    ) {

      return FALSE;
    }

    /* the folder will be split across cabinets */
    p_fci_internal->fSplitFolder=TRUE;

  } else {
    /* this should never happen */
    if (p_fci_internal->fNextCab) {
      /* internal error */
      set_error( p_fci_internal, FCIERR_NONE, ERROR_GEN_FAILURE );
      return FALSE;
    }
  }

  if (!(folder = add_folder( p_fci_internal ))) return FALSE;
  if (!add_data_to_folder( p_fci_internal, folder, &payload, pfnfcis )) return FALSE;
  if (!add_files_to_folder( p_fci_internal, folder, payload )) return FALSE;

  /* reset CFFolder specific information */
  p_fci_internal->cDataBlocks=0;
  p_fci_internal->cCompressedBytesInFolder=0;

  return TRUE;
}