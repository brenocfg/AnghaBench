#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ num_dicts; } ;
struct TYPE_19__ {TYPE_1__ cid; } ;
struct TYPE_15__ {char* cursor; char* limit; scalar_t__ error; } ;
struct TYPE_17__ {TYPE_2__ root; int /*<<< orphan*/  num_dict; } ;
struct TYPE_18__ {TYPE_4__ parser; } ;
struct TYPE_16__ {scalar_t__ ident; } ;
typedef  TYPE_3__* T1_Field ;
typedef  int FT_ULong ;
typedef  int FT_UInt ;
typedef  scalar_t__ FT_Error ;
typedef  char FT_Byte ;
typedef  TYPE_4__ CID_Parser ;
typedef  TYPE_5__ CID_Loader ;
typedef  TYPE_6__* CID_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ERROR (char*) ; 
 scalar_t__ FT_Err_Ok ; 
 scalar_t__ FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Invalid_File_Format ; 
 int /*<<< orphan*/  cid_field_records ; 
 scalar_t__ cid_load_keyword (TYPE_6__*,TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cid_parser_skip_PS_token (TYPE_4__*) ; 
 int /*<<< orphan*/  cid_parser_skip_spaces (TYPE_4__*) ; 
 int ft_strlen (char const*) ; 
 scalar_t__ ft_strncmp (char*,char*,int) ; 

__attribute__((used)) static FT_Error
  cid_parse_dict( CID_Face     face,
                  CID_Loader*  loader,
                  FT_Byte*     base,
                  FT_ULong     size )
  {
    CID_Parser*  parser = &loader->parser;


    parser->root.cursor = base;
    parser->root.limit  = base + size;
    parser->root.error  = FT_Err_Ok;

    {
      FT_Byte*  cur   = base;
      FT_Byte*  limit = cur + size;


      for (;;)
      {
        FT_Byte*  newlimit;


        parser->root.cursor = cur;
        cid_parser_skip_spaces( parser );

        if ( parser->root.cursor >= limit )
          newlimit = limit - 1 - 17;
        else
          newlimit = parser->root.cursor - 17;

        /* look for `%ADOBeginFontDict' */
        for ( ; cur < newlimit; cur++ )
        {
          if ( *cur == '%'                                            &&
               ft_strncmp( (char*)cur, "%ADOBeginFontDict", 17 ) == 0 )
          {
            /* if /FDArray was found, then cid->num_dicts is > 0, and */
            /* we can start increasing parser->num_dict               */
            if ( face->cid.num_dicts > 0 )
              parser->num_dict++;
          }
        }

        cur = parser->root.cursor;
        /* no error can occur in cid_parser_skip_spaces */
        if ( cur >= limit )
          break;

        cid_parser_skip_PS_token( parser );
        if ( parser->root.cursor >= limit || parser->root.error )
          break;

        /* look for immediates */
        if ( *cur == '/' && cur + 2 < limit )
        {
          FT_UInt  len;


          cur++;
          len = (FT_UInt)( parser->root.cursor - cur );

          if ( len > 0 && len < 22 )
          {
            /* now compare the immediate name to the keyword table */
            T1_Field  keyword = (T1_Field)cid_field_records;


            for (;;)
            {
              FT_Byte*  name;


              name = (FT_Byte*)keyword->ident;
              if ( !name )
                break;

              if ( cur[0] == name[0]                     &&
                   len == ft_strlen( (const char*)name ) )
              {
                FT_UInt  n;


                for ( n = 1; n < len; n++ )
                  if ( cur[n] != name[n] )
                    break;

                if ( n >= len )
                {
                  /* we found it - run the parsing callback */
                  parser->root.error = cid_load_keyword( face,
                                                         loader,
                                                         keyword );
                  if ( parser->root.error )
                    return parser->root.error;
                  break;
                }
              }
              keyword++;
            }
          }
        }

        cur = parser->root.cursor;
      }

      if ( !face->cid.num_dicts )
      {
        FT_ERROR(( "cid_parse_dict: No font dictionary found\n" ));
        return FT_THROW( Invalid_File_Format );
      }
    }

    return parser->root.error;
  }