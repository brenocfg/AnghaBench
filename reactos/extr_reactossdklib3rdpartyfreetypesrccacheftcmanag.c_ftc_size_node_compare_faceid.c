#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ face_id; } ;
struct TYPE_4__ {TYPE_1__ scaler; } ;
typedef  int /*<<< orphan*/  FT_Pointer ;
typedef  int /*<<< orphan*/  FT_Bool ;
typedef  TYPE_2__* FTC_SizeNode ;
typedef  int /*<<< orphan*/  FTC_MruNode ;
typedef  scalar_t__ FTC_FaceID ;

/* Variables and functions */
 int /*<<< orphan*/  FT_BOOL (int) ; 

__attribute__((used)) static FT_Bool
  ftc_size_node_compare_faceid( FTC_MruNode  ftcnode,
                                FT_Pointer   ftcface_id )
  {
    FTC_SizeNode  node    = (FTC_SizeNode)ftcnode;
    FTC_FaceID    face_id = (FTC_FaceID)ftcface_id;


    return FT_BOOL( node->scaler.face_id == face_id );
  }