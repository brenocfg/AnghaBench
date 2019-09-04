#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ type; int location; int /*<<< orphan*/  (* reader ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  font_bbox; int /*<<< orphan*/  font_extra; int /*<<< orphan*/  font_info; } ;
struct TYPE_18__ {TYPE_2__ type1; } ;
struct TYPE_15__ {int /*<<< orphan*/  error; } ;
struct TYPE_14__ {TYPE_1__ root; } ;
struct TYPE_17__ {TYPE_10__ parser; } ;
typedef  TYPE_3__* T42_Loader ;
typedef  TYPE_4__* T42_Face ;
typedef  TYPE_5__* T1_Field ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  int /*<<< orphan*/  FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
#define  T1_FIELD_LOCATION_BBOX 130 
#define  T1_FIELD_LOCATION_FONT_EXTRA 129 
#define  T1_FIELD_LOCATION_FONT_INFO 128 
 scalar_t__ T1_FIELD_TYPE_CALLBACK ; 
 scalar_t__ T1_FIELD_TYPE_FIXED_ARRAY ; 
 scalar_t__ T1_FIELD_TYPE_INTEGER_ARRAY ; 
 int /*<<< orphan*/  T1_Load_Field (TYPE_10__*,TYPE_5__*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T1_Load_Field_Table (TYPE_10__*,TYPE_5__*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static FT_Error
  t42_load_keyword( T42_Face    face,
                    T42_Loader  loader,
                    T1_Field    field )
  {
    FT_Error  error;
    void*     dummy_object;
    void**    objects;
    FT_UInt   max_objects = 0;


    /* if the keyword has a dedicated callback, call it */
    if ( field->type == T1_FIELD_TYPE_CALLBACK )
    {
      field->reader( (FT_Face)face, loader );
      error = loader->parser.root.error;
      goto Exit;
    }

    /* now the keyword is either a simple field or a table of fields; */
    /* we are now going to take care of it                            */

    switch ( field->location )
    {
    case T1_FIELD_LOCATION_FONT_INFO:
      dummy_object = &face->type1.font_info;
      break;

    case T1_FIELD_LOCATION_FONT_EXTRA:
      dummy_object = &face->type1.font_extra;
      break;

    case T1_FIELD_LOCATION_BBOX:
      dummy_object = &face->type1.font_bbox;
      break;

    default:
      dummy_object = &face->type1;
    }

    objects = &dummy_object;

    if ( field->type == T1_FIELD_TYPE_INTEGER_ARRAY ||
         field->type == T1_FIELD_TYPE_FIXED_ARRAY   )
      error = T1_Load_Field_Table( &loader->parser, field,
                                   objects, max_objects, 0 );
    else
      error = T1_Load_Field( &loader->parser, field,
                             objects, max_objects, 0 );

   Exit:
    return error;
  }