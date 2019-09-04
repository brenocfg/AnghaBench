#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int size; } ;
struct TYPE_14__ {scalar_t__ version; int count; scalar_t__ offset; scalar_t__ size; struct TYPE_14__* tables; } ;
struct TYPE_15__ {TYPE_1__ toc; } ;
struct TYPE_13__ {int /*<<< orphan*/  memory; } ;
typedef  TYPE_1__* PCF_Toc ;
typedef  TYPE_1__ PCF_TableRec ;
typedef  TYPE_1__* PCF_Table ;
typedef  TYPE_4__* PCF_Face ;
typedef  scalar_t__ FT_ULong ;
typedef  int FT_UInt ;
typedef  TYPE_5__* FT_Stream ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  Cannot_Open_Resource ; 
 int /*<<< orphan*/  FT_Err_Ok ; 
 TYPE_11__* FT_FACE (TYPE_4__*) ; 
 int /*<<< orphan*/  FT_FREE (TYPE_1__*) ; 
 int FT_MIN (int,int) ; 
 scalar_t__ FT_NEW_ARRAY (TYPE_1__*,int) ; 
 scalar_t__ FT_STREAM_READ_FIELDS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ FT_STREAM_SEEK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  Invalid_File_Format ; 
 int /*<<< orphan*/  Invalid_Offset ; 
 int /*<<< orphan*/  Invalid_Table ; 
 scalar_t__ PCF_FILE_VERSION ; 
 int /*<<< orphan*/  pcf_table_header ; 
 int /*<<< orphan*/  pcf_toc_header ; 

__attribute__((used)) static FT_Error
  pcf_read_TOC( FT_Stream  stream,
                PCF_Face   face )
  {
    FT_Error   error;
    PCF_Toc    toc = &face->toc;
    PCF_Table  tables;

    FT_Memory  memory = FT_FACE( face )->memory;
    FT_UInt    n;

    FT_ULong   size;


    if ( FT_STREAM_SEEK( 0 )                          ||
         FT_STREAM_READ_FIELDS( pcf_toc_header, toc ) )
      return FT_THROW( Cannot_Open_Resource );

    if ( toc->version != PCF_FILE_VERSION ||
         toc->count   == 0                )
      return FT_THROW( Invalid_File_Format );

    if ( stream->size < 16 )
      return FT_THROW( Invalid_File_Format );

    /* we need 16 bytes per TOC entry, */
    /* and there can be most 9 tables  */
    if ( toc->count > ( stream->size >> 4 ) ||
         toc->count > 9                     )
    {
      FT_TRACE0(( "pcf_read_TOC: adjusting number of tables"
                  " (from %d to %d)\n",
                  toc->count,
                  FT_MIN( stream->size >> 4, 9 ) ));
      toc->count = FT_MIN( stream->size >> 4, 9 );
    }

    if ( FT_NEW_ARRAY( face->toc.tables, toc->count ) )
      return error;

    tables = face->toc.tables;
    for ( n = 0; n < toc->count; n++ )
    {
      if ( FT_STREAM_READ_FIELDS( pcf_table_header, tables ) )
        goto Exit;
      tables++;
    }

    /* Sort tables and check for overlaps.  Because they are almost      */
    /* always ordered already, an in-place bubble sort with simultaneous */
    /* boundary checking seems appropriate.                              */
    tables = face->toc.tables;

    for ( n = 0; n < toc->count - 1; n++ )
    {
      FT_UInt  i, have_change;


      have_change = 0;

      for ( i = 0; i < toc->count - 1 - n; i++ )
      {
        PCF_TableRec  tmp;


        if ( tables[i].offset > tables[i + 1].offset )
        {
          tmp           = tables[i];
          tables[i]     = tables[i + 1];
          tables[i + 1] = tmp;

          have_change = 1;
        }

        if ( ( tables[i].size   > tables[i + 1].offset )                  ||
             ( tables[i].offset > tables[i + 1].offset - tables[i].size ) )
        {
          error = FT_THROW( Invalid_Offset );
          goto Exit;
        }
      }

      if ( !have_change )
        break;
    }

    /*
     *  We now check whether the `size' and `offset' values are reasonable:
     *  `offset' + `size' must not exceed the stream size.
     *
     *  Note, however, that X11's `pcfWriteFont' routine (used by the
     *  `bdftopcf' program to create PDF font files) has two special
     *  features.
     *
     *  - It always assigns the accelerator table a size of 100 bytes in the
     *    TOC, regardless of its real size, which can vary between 34 and 72
     *    bytes.
     *
     *  - Due to the way the routine is designed, it ships out the last font
     *    table with its real size, ignoring the TOC's size value.  Since
     *    the TOC size values are always rounded up to a multiple of 4, the
     *    difference can be up to three bytes for all tables except the
     *    accelerator table, for which the difference can be as large as 66
     *    bytes.
     *
     */

    tables = face->toc.tables;
    size   = stream->size;

    for ( n = 0; n < toc->count - 1; n++ )
    {
      /* we need two checks to avoid overflow */
      if ( ( tables->size   > size                ) ||
           ( tables->offset > size - tables->size ) )
      {
        error = FT_THROW( Invalid_Table );
        goto Exit;
      }
      tables++;
    }

    /* only check `tables->offset' for last table element ... */
    if ( ( tables->offset > size ) )
    {
      error = FT_THROW( Invalid_Table );
      goto Exit;
    }
    /* ... and adjust `tables->size' to the real value if necessary */
    if ( tables->size > size - tables->offset )
      tables->size = size - tables->offset;

#ifdef FT_DEBUG_LEVEL_TRACE

    {
      FT_UInt      i, j;
      const char*  name = "?";


      FT_TRACE4(( "pcf_read_TOC:\n" ));

      FT_TRACE4(( "  number of tables: %ld\n", face->toc.count ));

      tables = face->toc.tables;
      for ( i = 0; i < toc->count; i++ )
      {
        for ( j = 0; j < sizeof ( tableNames ) / sizeof ( tableNames[0] );
              j++ )
          if ( tables[i].type == (FT_UInt)( 1 << j ) )
            name = tableNames[j];

        FT_TRACE4(( "  %d: type=%s, format=0x%X,"
                    " size=%ld (0x%lX), offset=%ld (0x%lX)\n",
                    i, name,
                    tables[i].format,
                    tables[i].size, tables[i].size,
                    tables[i].offset, tables[i].offset ));
      }
    }

#endif

    return FT_Err_Ok;

  Exit:
    FT_FREE( face->toc.tables );
    return error;
  }