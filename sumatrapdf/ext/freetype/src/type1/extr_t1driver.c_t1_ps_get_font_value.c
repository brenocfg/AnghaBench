#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct TYPE_14__ {int is_fixed_pitch; scalar_t__ italic_angle; scalar_t__ weight; scalar_t__ family_name; scalar_t__ full_name; scalar_t__ notice; scalar_t__ version; int /*<<< orphan*/  underline_thickness; int /*<<< orphan*/  underline_position; } ;
struct TYPE_13__ {int /*<<< orphan*/  fs_type; } ;
struct TYPE_12__ {int num_blue_values; int num_other_blues; int num_family_blues; int num_family_other_blues; int num_snap_widths; int num_snap_heights; int round_stem_up; int force_bold; scalar_t__ password; scalar_t__ language_group; int /*<<< orphan*/  lenIV; int /*<<< orphan*/ * min_feature; int /*<<< orphan*/ * snap_heights; int /*<<< orphan*/ * snap_widths; int /*<<< orphan*/ * family_other_blues; int /*<<< orphan*/ * family_blues; int /*<<< orphan*/ * other_blues; int /*<<< orphan*/  blue_shift; int /*<<< orphan*/  blue_fuzz; int /*<<< orphan*/  blue_scale; int /*<<< orphan*/ * blue_values; int /*<<< orphan*/ * standard_height; int /*<<< orphan*/ * standard_width; int /*<<< orphan*/  unique_id; } ;
struct TYPE_11__ {scalar_t__* char_name; int /*<<< orphan*/  num_chars; } ;
struct TYPE_10__ {int /*<<< orphan*/  yMax; int /*<<< orphan*/  xMax; int /*<<< orphan*/  yMin; int /*<<< orphan*/  xMin; } ;
struct TYPE_9__ {int /*<<< orphan*/  yy; int /*<<< orphan*/  yx; int /*<<< orphan*/  xy; int /*<<< orphan*/  xx; } ;
struct TYPE_15__ {int font_type; int paint_type; TYPE_6__ font_info; TYPE_5__ font_extra; TYPE_4__ private_dict; scalar_t__* subrs; int /*<<< orphan*/ * subrs_len; int /*<<< orphan*/  num_subrs; int /*<<< orphan*/  subrs_hash; TYPE_3__ encoding; int /*<<< orphan*/  encoding_type; scalar_t__* charstrings; int /*<<< orphan*/ * charstrings_len; int /*<<< orphan*/  num_glyphs; scalar_t__* glyph_names; scalar_t__ font_name; TYPE_2__ font_bbox; TYPE_1__ font_matrix; } ;
struct TYPE_16__ {TYPE_7__ type1; } ;
typedef  TYPE_7__* T1_Font ;
typedef  TYPE_8__* T1_Face ;
typedef  int /*<<< orphan*/  T1_EncodingType ;
typedef  int PS_Dict_Keys ;
typedef  int /*<<< orphan*/  FT_UShort ;
typedef  size_t FT_ULong ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Short ;
typedef  scalar_t__ FT_Long ;
typedef  int /*<<< orphan*/  FT_Int ;
typedef  int /*<<< orphan*/  FT_Fixed ;
typedef  int /*<<< orphan*/  FT_Face ;
typedef  int /*<<< orphan*/  FT_Char ;
typedef  int FT_Byte ;
typedef  int FT_Bool ;

/* Variables and functions */
#define  PS_DICT_BLUE_FUZZ 173 
#define  PS_DICT_BLUE_SCALE 172 
#define  PS_DICT_BLUE_SHIFT 171 
#define  PS_DICT_BLUE_VALUE 170 
#define  PS_DICT_CHAR_STRING 169 
#define  PS_DICT_CHAR_STRING_KEY 168 
#define  PS_DICT_ENCODING_ENTRY 167 
#define  PS_DICT_ENCODING_TYPE 166 
#define  PS_DICT_FAMILY_BLUE 165 
#define  PS_DICT_FAMILY_NAME 164 
#define  PS_DICT_FAMILY_OTHER_BLUE 163 
#define  PS_DICT_FONT_BBOX 162 
#define  PS_DICT_FONT_MATRIX 161 
#define  PS_DICT_FONT_NAME 160 
#define  PS_DICT_FONT_TYPE 159 
#define  PS_DICT_FORCE_BOLD 158 
#define  PS_DICT_FS_TYPE 157 
#define  PS_DICT_FULL_NAME 156 
#define  PS_DICT_IS_FIXED_PITCH 155 
#define  PS_DICT_ITALIC_ANGLE 154 
#define  PS_DICT_LANGUAGE_GROUP 153 
#define  PS_DICT_LEN_IV 152 
#define  PS_DICT_MIN_FEATURE 151 
#define  PS_DICT_NOTICE 150 
#define  PS_DICT_NUM_BLUE_VALUES 149 
#define  PS_DICT_NUM_CHAR_STRINGS 148 
#define  PS_DICT_NUM_FAMILY_BLUES 147 
#define  PS_DICT_NUM_FAMILY_OTHER_BLUES 146 
#define  PS_DICT_NUM_OTHER_BLUES 145 
#define  PS_DICT_NUM_STEM_SNAP_H 144 
#define  PS_DICT_NUM_STEM_SNAP_V 143 
#define  PS_DICT_NUM_SUBRS 142 
#define  PS_DICT_OTHER_BLUE 141 
#define  PS_DICT_PAINT_TYPE 140 
#define  PS_DICT_PASSWORD 139 
#define  PS_DICT_RND_STEM_UP 138 
#define  PS_DICT_STD_HW 137 
#define  PS_DICT_STD_VW 136 
#define  PS_DICT_STEM_SNAP_H 135 
#define  PS_DICT_STEM_SNAP_V 134 
#define  PS_DICT_SUBR 133 
#define  PS_DICT_UNDERLINE_POSITION 132 
#define  PS_DICT_UNDERLINE_THICKNESS 131 
#define  PS_DICT_UNIQUE_ID 130 
#define  PS_DICT_VERSION 129 
#define  PS_DICT_WEIGHT 128 
 int /*<<< orphan*/  T1_ENCODING_TYPE_ARRAY ; 
 size_t* ft_hash_num_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ft_memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  ft_strlen (scalar_t__) ; 

__attribute__((used)) static FT_Long
  t1_ps_get_font_value( FT_Face       face,
                        PS_Dict_Keys  key,
                        FT_UInt       idx,
                        void         *value,
                        FT_Long       value_len_ )
  {
    FT_ULong  retval    = 0; /* always >= 1 if valid */
    FT_ULong  value_len = value_len_ < 0 ? 0 : (FT_ULong)value_len_;

    T1_Face  t1face = (T1_Face)face;
    T1_Font  type1  = &t1face->type1;


    switch ( key )
    {
    case PS_DICT_FONT_TYPE:
      retval = sizeof ( type1->font_type );
      if ( value && value_len >= retval )
        *((FT_Byte *)value) = type1->font_type;
      break;

    case PS_DICT_FONT_MATRIX:
      if ( idx < sizeof ( type1->font_matrix ) /
                   sizeof ( type1->font_matrix.xx ) )
      {
        FT_Fixed  val = 0;


        retval = sizeof ( val );
        if ( value && value_len >= retval )
        {
          switch ( idx )
          {
          case 0:
            val = type1->font_matrix.xx;
            break;
          case 1:
            val = type1->font_matrix.xy;
            break;
          case 2:
            val = type1->font_matrix.yx;
            break;
          case 3:
            val = type1->font_matrix.yy;
            break;
          }
          *((FT_Fixed *)value) = val;
        }
      }
      break;

    case PS_DICT_FONT_BBOX:
      if ( idx < sizeof ( type1->font_bbox ) /
                   sizeof ( type1->font_bbox.xMin ) )
      {
        FT_Fixed  val = 0;


        retval = sizeof ( val );
        if ( value && value_len >= retval )
        {
          switch ( idx )
          {
          case 0:
            val = type1->font_bbox.xMin;
            break;
          case 1:
            val = type1->font_bbox.yMin;
            break;
          case 2:
            val = type1->font_bbox.xMax;
            break;
          case 3:
            val = type1->font_bbox.yMax;
            break;
          }
          *((FT_Fixed *)value) = val;
        }
      }
      break;

    case PS_DICT_PAINT_TYPE:
      retval = sizeof ( type1->paint_type );
      if ( value && value_len >= retval )
        *((FT_Byte *)value) = type1->paint_type;
      break;

    case PS_DICT_FONT_NAME:
      if ( type1->font_name )
      {
        retval = ft_strlen( type1->font_name ) + 1;
        if ( value && value_len >= retval )
          ft_memcpy( value, (void *)( type1->font_name ), retval );
      }
      break;

    case PS_DICT_UNIQUE_ID:
      retval = sizeof ( type1->private_dict.unique_id );
      if ( value && value_len >= retval )
        *((FT_Int *)value) = type1->private_dict.unique_id;
      break;

    case PS_DICT_NUM_CHAR_STRINGS:
      retval = sizeof ( type1->num_glyphs );
      if ( value && value_len >= retval )
        *((FT_Int *)value) = type1->num_glyphs;
      break;

    case PS_DICT_CHAR_STRING_KEY:
      if ( idx < (FT_UInt)type1->num_glyphs )
      {
        retval = ft_strlen( type1->glyph_names[idx] ) + 1;
        if ( value && value_len >= retval )
        {
          ft_memcpy( value, (void *)( type1->glyph_names[idx] ), retval );
          ((FT_Char *)value)[retval - 1] = (FT_Char)'\0';
        }
      }
      break;

    case PS_DICT_CHAR_STRING:
      if ( idx < (FT_UInt)type1->num_glyphs )
      {
        retval = type1->charstrings_len[idx] + 1;
        if ( value && value_len >= retval )
        {
          ft_memcpy( value, (void *)( type1->charstrings[idx] ),
                     retval - 1 );
          ((FT_Char *)value)[retval - 1] = (FT_Char)'\0';
        }
      }
      break;

    case PS_DICT_ENCODING_TYPE:
      retval = sizeof ( type1->encoding_type );
      if ( value && value_len >= retval )
        *((T1_EncodingType *)value) = type1->encoding_type;
      break;

    case PS_DICT_ENCODING_ENTRY:
      if ( type1->encoding_type == T1_ENCODING_TYPE_ARRAY &&
           idx < (FT_UInt)type1->encoding.num_chars       )
      {
        retval = ft_strlen( type1->encoding.char_name[idx] ) + 1;
        if ( value && value_len >= retval )
        {
          ft_memcpy( value, (void *)( type1->encoding.char_name[idx] ),
                     retval - 1 );
          ((FT_Char *)value)[retval - 1] = (FT_Char)'\0';
        }
      }
      break;

    case PS_DICT_NUM_SUBRS:
      retval = sizeof ( type1->num_subrs );
      if ( value && value_len >= retval )
        *((FT_Int *)value) = type1->num_subrs;
      break;

    case PS_DICT_SUBR:
      {
        FT_Bool  ok = 0;


        if ( type1->subrs_hash )
        {
          /* convert subr index to array index */
          size_t*  val = ft_hash_num_lookup( (FT_Int)idx,
                                             type1->subrs_hash );


          if ( val )
          {
            idx = *val;
            ok  = 1;
          }
        }
        else
        {
          if ( idx < (FT_UInt)type1->num_subrs )
            ok = 1;
        }

        if ( ok && type1->subrs )
        {
          retval = type1->subrs_len[idx] + 1;
          if ( value && value_len >= retval )
          {
            ft_memcpy( value, (void *)( type1->subrs[idx] ), retval - 1 );
            ((FT_Char *)value)[retval - 1] = (FT_Char)'\0';
          }
        }
      }
      break;

    case PS_DICT_STD_HW:
      retval = sizeof ( type1->private_dict.standard_width[0] );
      if ( value && value_len >= retval )
        *((FT_UShort *)value) = type1->private_dict.standard_width[0];
      break;

    case PS_DICT_STD_VW:
      retval = sizeof ( type1->private_dict.standard_height[0] );
      if ( value && value_len >= retval )
        *((FT_UShort *)value) = type1->private_dict.standard_height[0];
      break;

    case PS_DICT_NUM_BLUE_VALUES:
      retval = sizeof ( type1->private_dict.num_blue_values );
      if ( value && value_len >= retval )
        *((FT_Byte *)value) = type1->private_dict.num_blue_values;
      break;

    case PS_DICT_BLUE_VALUE:
      if ( idx < type1->private_dict.num_blue_values )
      {
        retval = sizeof ( type1->private_dict.blue_values[idx] );
        if ( value && value_len >= retval )
          *((FT_Short *)value) = type1->private_dict.blue_values[idx];
      }
      break;

    case PS_DICT_BLUE_SCALE:
      retval = sizeof ( type1->private_dict.blue_scale );
      if ( value && value_len >= retval )
        *((FT_Fixed *)value) = type1->private_dict.blue_scale;
      break;

    case PS_DICT_BLUE_FUZZ:
      retval = sizeof ( type1->private_dict.blue_fuzz );
      if ( value && value_len >= retval )
        *((FT_Int *)value) = type1->private_dict.blue_fuzz;
      break;

    case PS_DICT_BLUE_SHIFT:
      retval = sizeof ( type1->private_dict.blue_shift );
      if ( value && value_len >= retval )
        *((FT_Int *)value) = type1->private_dict.blue_shift;
      break;

    case PS_DICT_NUM_OTHER_BLUES:
      retval = sizeof ( type1->private_dict.num_other_blues );
      if ( value && value_len >= retval )
        *((FT_Byte *)value) = type1->private_dict.num_other_blues;
      break;

    case PS_DICT_OTHER_BLUE:
      if ( idx < type1->private_dict.num_other_blues )
      {
        retval = sizeof ( type1->private_dict.other_blues[idx] );
        if ( value && value_len >= retval )
          *((FT_Short *)value) = type1->private_dict.other_blues[idx];
      }
      break;

    case PS_DICT_NUM_FAMILY_BLUES:
      retval = sizeof ( type1->private_dict.num_family_blues );
      if ( value && value_len >= retval )
        *((FT_Byte *)value) = type1->private_dict.num_family_blues;
      break;

    case PS_DICT_FAMILY_BLUE:
      if ( idx < type1->private_dict.num_family_blues )
      {
        retval = sizeof ( type1->private_dict.family_blues[idx] );
        if ( value && value_len >= retval )
          *((FT_Short *)value) = type1->private_dict.family_blues[idx];
      }
      break;

    case PS_DICT_NUM_FAMILY_OTHER_BLUES:
      retval = sizeof ( type1->private_dict.num_family_other_blues );
      if ( value && value_len >= retval )
        *((FT_Byte *)value) = type1->private_dict.num_family_other_blues;
      break;

    case PS_DICT_FAMILY_OTHER_BLUE:
      if ( idx < type1->private_dict.num_family_other_blues )
      {
        retval = sizeof ( type1->private_dict.family_other_blues[idx] );
        if ( value && value_len >= retval )
          *((FT_Short *)value) = type1->private_dict.family_other_blues[idx];
      }
      break;

    case PS_DICT_NUM_STEM_SNAP_H:
      retval = sizeof ( type1->private_dict.num_snap_widths );
      if ( value && value_len >= retval )
        *((FT_Byte *)value) = type1->private_dict.num_snap_widths;
      break;

    case PS_DICT_STEM_SNAP_H:
      if ( idx < type1->private_dict.num_snap_widths )
      {
        retval = sizeof ( type1->private_dict.snap_widths[idx] );
        if ( value && value_len >= retval )
          *((FT_Short *)value) = type1->private_dict.snap_widths[idx];
      }
      break;

    case PS_DICT_NUM_STEM_SNAP_V:
      retval = sizeof ( type1->private_dict.num_snap_heights );
      if ( value && value_len >= retval )
        *((FT_Byte *)value) = type1->private_dict.num_snap_heights;
      break;

    case PS_DICT_STEM_SNAP_V:
      if ( idx < type1->private_dict.num_snap_heights )
      {
        retval = sizeof ( type1->private_dict.snap_heights[idx] );
        if ( value && value_len >= retval )
          *((FT_Short *)value) = type1->private_dict.snap_heights[idx];
      }
      break;

    case PS_DICT_RND_STEM_UP:
      retval = sizeof ( type1->private_dict.round_stem_up );
      if ( value && value_len >= retval )
        *((FT_Bool *)value) = type1->private_dict.round_stem_up;
      break;

    case PS_DICT_FORCE_BOLD:
      retval = sizeof ( type1->private_dict.force_bold );
      if ( value && value_len >= retval )
        *((FT_Bool *)value) = type1->private_dict.force_bold;
      break;

    case PS_DICT_MIN_FEATURE:
      if ( idx < sizeof ( type1->private_dict.min_feature ) /
                   sizeof ( type1->private_dict.min_feature[0] ) )
      {
        retval = sizeof ( type1->private_dict.min_feature[idx] );
        if ( value && value_len >= retval )
          *((FT_Short *)value) = type1->private_dict.min_feature[idx];
      }
      break;

    case PS_DICT_LEN_IV:
      retval = sizeof ( type1->private_dict.lenIV );
      if ( value && value_len >= retval )
        *((FT_Int *)value) = type1->private_dict.lenIV;
      break;

    case PS_DICT_PASSWORD:
      retval = sizeof ( type1->private_dict.password );
      if ( value && value_len >= retval )
        *((FT_Long *)value) = type1->private_dict.password;
      break;

    case PS_DICT_LANGUAGE_GROUP:
      retval = sizeof ( type1->private_dict.language_group );
      if ( value && value_len >= retval )
        *((FT_Long *)value) = type1->private_dict.language_group;
      break;

    case PS_DICT_IS_FIXED_PITCH:
      retval = sizeof ( type1->font_info.is_fixed_pitch );
      if ( value && value_len >= retval )
        *((FT_Bool *)value) = type1->font_info.is_fixed_pitch;
      break;

    case PS_DICT_UNDERLINE_POSITION:
      retval = sizeof ( type1->font_info.underline_position );
      if ( value && value_len >= retval )
        *((FT_Short *)value) = type1->font_info.underline_position;
      break;

    case PS_DICT_UNDERLINE_THICKNESS:
      retval = sizeof ( type1->font_info.underline_thickness );
      if ( value && value_len >= retval )
        *((FT_UShort *)value) = type1->font_info.underline_thickness;
      break;

    case PS_DICT_FS_TYPE:
      retval = sizeof ( type1->font_extra.fs_type );
      if ( value && value_len >= retval )
        *((FT_UShort *)value) = type1->font_extra.fs_type;
      break;

    case PS_DICT_VERSION:
      if ( type1->font_info.version )
      {
        retval = ft_strlen( type1->font_info.version ) + 1;
        if ( value && value_len >= retval )
          ft_memcpy( value, (void *)( type1->font_info.version ), retval );
      }
      break;

    case PS_DICT_NOTICE:
      if ( type1->font_info.notice )
      {
        retval = ft_strlen( type1->font_info.notice ) + 1;
        if ( value && value_len >= retval )
          ft_memcpy( value, (void *)( type1->font_info.notice ), retval );
      }
      break;

    case PS_DICT_FULL_NAME:
      if ( type1->font_info.full_name )
      {
        retval = ft_strlen( type1->font_info.full_name ) + 1;
        if ( value && value_len >= retval )
          ft_memcpy( value, (void *)( type1->font_info.full_name ), retval );
      }
      break;

    case PS_DICT_FAMILY_NAME:
      if ( type1->font_info.family_name )
      {
        retval = ft_strlen( type1->font_info.family_name ) + 1;
        if ( value && value_len >= retval )
          ft_memcpy( value, (void *)( type1->font_info.family_name ),
                     retval );
      }
      break;

    case PS_DICT_WEIGHT:
      if ( type1->font_info.weight )
      {
        retval = ft_strlen( type1->font_info.weight ) + 1;
        if ( value && value_len >= retval )
          ft_memcpy( value, (void *)( type1->font_info.weight ), retval );
      }
      break;

    case PS_DICT_ITALIC_ANGLE:
      retval = sizeof ( type1->font_info.italic_angle );
      if ( value && value_len >= retval )
        *((FT_Long *)value) = type1->font_info.italic_angle;
      break;
    }

    return retval == 0 ? -1 : (FT_Long)retval;
  }