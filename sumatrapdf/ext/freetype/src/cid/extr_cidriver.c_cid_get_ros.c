#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* registry; char* ordering; int /*<<< orphan*/  supplement; } ;
struct TYPE_5__ {TYPE_1__ cid; } ;
typedef  int /*<<< orphan*/  FT_Int ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  TYPE_1__* CID_FaceInfo ;
typedef  TYPE_2__* CID_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 

__attribute__((used)) static FT_Error
  cid_get_ros( CID_Face      face,
               const char*  *registry,
               const char*  *ordering,
               FT_Int       *supplement )
  {
    CID_FaceInfo  cid = &face->cid;


    if ( registry )
      *registry = cid->registry;

    if ( ordering )
      *ordering = cid->ordering;

    if ( supplement )
      *supplement = cid->supplement;

    return FT_Err_Ok;
  }