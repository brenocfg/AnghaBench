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
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ IStorage_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_DIRECT ; 
 int STGM_FAILIFTHERE ; 
 int STGM_PRIORITY ; 
 int STGM_READ ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_DENY_NONE ; 
 int STGM_SHARE_DENY_WRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_TRANSACTED ; 
 int STGM_WRITE ; 
 scalar_t__ STG_E_FILEALREADYEXISTS ; 
 scalar_t__ STG_E_INVALIDFLAG ; 
 scalar_t__ STG_E_INVALIDPARAMETER ; 
 scalar_t__ STG_E_INVALIDPOINTER ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * filename ; 
 int /*<<< orphan*/  filenameA ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_create_storage_modes(void)
{
   IStorage *stg = NULL;
   HRESULT r;

   DeleteFileA(filenameA);

   /* test with some invalid parameters */
   r = StgCreateDocfile( NULL, 0, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, 0, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_CREATE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_CREATE | STGM_READWRITE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, NULL);
   ok(r==STG_E_INVALIDPOINTER, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 1, &stg);
   ok(r==STG_E_INVALIDPARAMETER, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_DENY_WRITE | STGM_READWRITE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READ, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_PRIORITY, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");

   /* StgCreateDocfile seems to be very particular about the flags it accepts */
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED | STGM_WRITE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED | 8, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED | 0x80, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED | 0x800, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED | 0x8000, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED | 0x80000, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED | 0x800000, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   ok(stg == NULL, "stg was set\n");

   /* check what happens if the file already exists (which is how it's meant to be used) */
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, &stg);
   ok(r==S_OK, "StgCreateDocfile failed\n");
   r = IStorage_Release(stg);
   ok(r == 0, "storage not released\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED, 0, &stg);
   ok(r==STG_E_FILEALREADYEXISTS, "StgCreateDocfile wrong error\n"); /* FAILIFTHERE is default */
   r = StgCreateDocfile( filename, STGM_READ, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n"); /* need at least readmode and sharemode */
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_SHARE_DENY_WRITE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_SHARE_DENY_NONE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile failed\n");
   r = StgCreateDocfile( filename, STGM_SHARE_DENY_NONE | STGM_TRANSACTED, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile failed\n");
   r = StgCreateDocfile( filename, STGM_SHARE_DENY_NONE | STGM_READWRITE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile failed\n");
   r = StgCreateDocfile( filename, STGM_SHARE_DENY_NONE | STGM_WRITE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile failed\n");
   r = StgCreateDocfile( filename, STGM_SHARE_DENY_WRITE | STGM_WRITE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile failed\n");
   r = StgCreateDocfile( filename, STGM_SHARE_DENY_WRITE | STGM_READ, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile wrong error\n");
   r = StgCreateDocfile( filename, STGM_TRANSACTED | STGM_SHARE_DENY_WRITE | STGM_READ, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile wrong error\n");
   ok(DeleteFileA(filenameA), "failed to delete file\n");

   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED, 0, &stg);
   ok(r==S_OK, "StgCreateDocfile failed\n");
   r = IStorage_Release(stg);
   ok(r == 0, "storage not released\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED |STGM_FAILIFTHERE, 0, &stg);
   ok(r==STG_E_FILEALREADYEXISTS, "StgCreateDocfile wrong error\n");
   r = StgCreateDocfile( filename, STGM_SHARE_EXCLUSIVE | STGM_WRITE, 0, &stg);
   ok(r==STG_E_FILEALREADYEXISTS, "StgCreateDocfile wrong error\n");

   r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_DENY_WRITE | STGM_READWRITE, 0, &stg);
   ok(r==STG_E_INVALIDFLAG, "StgCreateDocfile succeeded\n");
   r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE |STGM_TRANSACTED, 0, &stg);
   ok(r==S_OK, "StgCreateDocfile failed\n");
   r = IStorage_Release(stg);
   ok(r == 0, "storage not released\n");
   ok(DeleteFileA(filenameA), "failed to delete file\n");

   r = StgCreateDocfile( filename, STGM_CREATE | STGM_READWRITE |STGM_TRANSACTED, 0, &stg);
   ok(r==S_OK, "StgCreateDocfile failed\n");
   r = IStorage_Release(stg);
   ok(r == 0, "storage not released\n");
   ok(DeleteFileA(filenameA), "failed to delete file\n");

   /* test the way excel uses StgCreateDocFile */
   r = StgCreateDocfile( filename, STGM_TRANSACTED|STGM_CREATE|STGM_SHARE_DENY_WRITE|STGM_READWRITE, 0, &stg);
   ok(r==S_OK, "StgCreateDocfile the excel way failed\n");
   if(r == S_OK)
   {
      r = IStorage_Release(stg);
      ok(r == 0, "storage not released\n");
      ok(DeleteFileA(filenameA), "failed to delete file\n");
   }

   /* and the way windows media uses it ... */
   r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_DENY_NONE | STGM_READWRITE | STGM_TRANSACTED, 0, &stg);
   ok(r==S_OK, "StgCreateDocfile the windows media way failed\n");
   if (r == S_OK)
   {
      r = IStorage_Release(stg);
      ok(r == 0, "storage not released\n");
      ok(DeleteFileA(filenameA), "failed to delete file\n");
   }

   /* looks like we need STGM_TRANSACTED or STGM_CREATE */
   r = StgCreateDocfile( filename, STGM_TRANSACTED|STGM_SHARE_DENY_WRITE|STGM_READWRITE, 0, &stg);
   ok(r==S_OK, "StgCreateDocfile the excel way failed\n");
   if(r == S_OK)
   {
      r = IStorage_Release(stg);
      ok(r == 0, "storage not released\n");
      ok(DeleteFileA(filenameA), "failed to delete file\n");
   }

   r = StgCreateDocfile( filename, STGM_TRANSACTED|STGM_CREATE|STGM_SHARE_DENY_WRITE|STGM_WRITE, 0, &stg);
   ok(r==S_OK, "StgCreateDocfile the excel way failed\n");
   if(r == S_OK)
   {
      r = IStorage_Release(stg);
      ok(r == 0, "storage not released\n");
      ok(DeleteFileA(filenameA), "failed to delete file\n");
   }

   r = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, &stg);
   ok(r==S_OK, "StgCreateDocfile the powerpoint way failed\n");
   if(r == S_OK)
   {
      r = IStorage_Release(stg);
      ok(r == 0, "storage not released\n");
      ok(DeleteFileA(filenameA), "failed to delete file\n");
   }

   /* test the way msi uses StgCreateDocfile */
   r = StgCreateDocfile( filename, STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &stg);
   ok(r==S_OK, "StgCreateDocFile failed\n");
   r = IStorage_Release(stg);
   ok(r == 0, "storage not released\n");
   ok(DeleteFileA(filenameA), "failed to delete file\n");
}