#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_1__* ps_table_funcs; } ;
struct TYPE_22__ {char** elements; int* lengths; scalar_t__ init; } ;
struct TYPE_21__ {int /*<<< orphan*/  psaux; } ;
struct TYPE_18__ {char* limit; char* cursor; scalar_t__ error; int /*<<< orphan*/  memory; } ;
struct TYPE_19__ {TYPE_2__ root; } ;
struct TYPE_20__ {int num_glyphs; TYPE_6__ swap_table; TYPE_6__ glyph_names; TYPE_6__ charstrings; TYPE_3__ parser; } ;
struct TYPE_17__ {scalar_t__ (* init ) (TYPE_6__*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__* T42_Parser ;
typedef  TYPE_4__* T42_Loader ;
typedef  TYPE_5__* T42_Face ;
typedef  TYPE_6__* PS_Table ;
typedef  TYPE_7__* PSAux_Service ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  size_t FT_Int ;
typedef  scalar_t__ FT_Error ;
typedef  char FT_Byte ;
typedef  scalar_t__ FT_Bool ;

/* Variables and functions */
 scalar_t__ FT_BOOL (int) ; 
 int /*<<< orphan*/  FT_ERROR (char*) ; 
 scalar_t__ FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  Invalid_File_Format ; 
 scalar_t__ T1_Add_Table (TYPE_6__*,size_t,char*,int) ; 
 int /*<<< orphan*/  T1_Skip_PS_Token (TYPE_3__*) ; 
 int /*<<< orphan*/  T1_Skip_Spaces (TYPE_3__*) ; 
 int T1_ToInt (TYPE_3__*) ; 
 scalar_t__ ft_isdigit (char) ; 
 scalar_t__ ft_strcmp (char const*,char const*) ; 
 scalar_t__ stub1 (TYPE_6__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_6__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ t42_is_space (char) ; 

__attribute__((used)) static void
  t42_parse_charstrings( T42_Face    face,
                         T42_Loader  loader )
  {
    T42_Parser     parser       = &loader->parser;
    PS_Table       code_table   = &loader->charstrings;
    PS_Table       name_table   = &loader->glyph_names;
    PS_Table       swap_table   = &loader->swap_table;
    FT_Memory      memory       = parser->root.memory;
    FT_Error       error;

    PSAux_Service  psaux        = (PSAux_Service)face->psaux;

    FT_Byte*       cur;
    FT_Byte*       limit        = parser->root.limit;
    FT_Int         n;
    FT_Int         notdef_index = 0;
    FT_Byte        notdef_found = 0;


    T1_Skip_Spaces( parser );

    if ( parser->root.cursor >= limit )
    {
      FT_ERROR(( "t42_parse_charstrings: out of bounds\n" ));
      error = FT_THROW( Invalid_File_Format );
      goto Fail;
    }

    if ( ft_isdigit( *parser->root.cursor ) )
    {
      loader->num_glyphs = T1_ToInt( parser );
      if ( parser->root.error )
        return;
      if ( loader->num_glyphs < 0 )
      {
        FT_ERROR(( "t42_parse_encoding: invalid number of glyphs\n" ));
        error = FT_THROW( Invalid_File_Format );
        goto Fail;
      }

      /* we certainly need more than 4 bytes per glyph */
      if ( loader->num_glyphs > ( limit - parser->root.cursor ) >> 2 )
      {
        FT_TRACE0(( "t42_parse_charstrings: adjusting number of glyphs"
                    " (from %d to %d)\n",
                    loader->num_glyphs,
                    ( limit - parser->root.cursor ) >> 2 ));
        loader->num_glyphs = ( limit - parser->root.cursor ) >> 2;
      }

    }
    else if ( *parser->root.cursor == '<' )
    {
      /* We have `<< ... >>'.  Count the number of `/' in the dictionary */
      /* to get its size.                                                */
      FT_Int  count = 0;


      T1_Skip_PS_Token( parser );
      if ( parser->root.error )
        return;
      T1_Skip_Spaces( parser );
      cur = parser->root.cursor;

      while ( parser->root.cursor < limit )
      {
        if ( *parser->root.cursor == '/' )
          count++;
        else if ( *parser->root.cursor == '>' )
        {
          loader->num_glyphs  = count;
          parser->root.cursor = cur;        /* rewind */
          break;
        }
        T1_Skip_PS_Token( parser );
        if ( parser->root.error )
          return;
        T1_Skip_Spaces( parser );
      }
    }
    else
    {
      FT_ERROR(( "t42_parse_charstrings: invalid token\n" ));
      error = FT_THROW( Invalid_File_Format );
      goto Fail;
    }

    if ( parser->root.cursor >= limit )
    {
      FT_ERROR(( "t42_parse_charstrings: out of bounds\n" ));
      error = FT_THROW( Invalid_File_Format );
      goto Fail;
    }

    /* initialize tables */

    /* contrary to Type1, we disallow multiple CharStrings arrays */
    if ( swap_table->init )
    {
      FT_ERROR(( "t42_parse_charstrings:"
                 " only one CharStrings array allowed\n" ));
      error = FT_THROW( Invalid_File_Format );
      goto Fail;
    }

    error = psaux->ps_table_funcs->init( code_table,
                                         loader->num_glyphs,
                                         memory );
    if ( error )
      goto Fail;

    error = psaux->ps_table_funcs->init( name_table,
                                         loader->num_glyphs,
                                         memory );
    if ( error )
      goto Fail;

    /* Initialize table for swapping index notdef_index and */
    /* index 0 names and codes (if necessary).              */

    error = psaux->ps_table_funcs->init( swap_table, 4, memory );
    if ( error )
      goto Fail;

    n = 0;

    for (;;)
    {
      /* We support two formats.                     */
      /*                                             */
      /*   `/glyphname' + index [+ `def']            */
      /*   `(glyphname)' [+ `cvn'] + index [+ `def'] */
      /*                                             */
      /* The latter format gets created by the       */
      /* LilyPond typesetting program.               */

      T1_Skip_Spaces( parser );

      cur = parser->root.cursor;
      if ( cur >= limit )
        break;

      /* We stop when we find an `end' keyword or '>' */
      if ( *cur   == 'e'          &&
           cur + 3 < limit        &&
           cur[1] == 'n'          &&
           cur[2] == 'd'          &&
           t42_is_space( cur[3] ) )
        break;
      if ( *cur == '>' )
        break;

      T1_Skip_PS_Token( parser );
      if ( parser->root.cursor >= limit )
      {
        FT_ERROR(( "t42_parse_charstrings: out of bounds\n" ));
        error = FT_THROW( Invalid_File_Format );
        goto Fail;
      }
      if ( parser->root.error )
        return;

      if ( *cur == '/' || *cur == '(' )
      {
        FT_UInt  len;
        FT_Bool  have_literal = FT_BOOL( *cur == '(' );


        if ( cur + ( have_literal ? 3 : 2 ) >= limit )
        {
          FT_ERROR(( "t42_parse_charstrings: out of bounds\n" ));
          error = FT_THROW( Invalid_File_Format );
          goto Fail;
        }

        cur++;                              /* skip `/' */
        len = (FT_UInt)( parser->root.cursor - cur );
        if ( have_literal )
          len--;

        error = T1_Add_Table( name_table, n, cur, len + 1 );
        if ( error )
          goto Fail;

        /* add a trailing zero to the name table */
        name_table->elements[n][len] = '\0';

        /* record index of /.notdef */
        if ( *cur == '.'                                              &&
             ft_strcmp( ".notdef",
                        (const char*)(name_table->elements[n]) ) == 0 )
        {
          notdef_index = n;
          notdef_found = 1;
        }

        T1_Skip_Spaces( parser );

        if ( have_literal )
          T1_Skip_PS_Token( parser );

        cur = parser->root.cursor;

        (void)T1_ToInt( parser );
        if ( parser->root.cursor >= limit )
        {
          FT_ERROR(( "t42_parse_charstrings: out of bounds\n" ));
          error = FT_THROW( Invalid_File_Format );
          goto Fail;
        }

        len = (FT_UInt)( parser->root.cursor - cur );

        error = T1_Add_Table( code_table, n, cur, len + 1 );
        if ( error )
          goto Fail;

        code_table->elements[n][len] = '\0';

        n++;
        if ( n >= loader->num_glyphs )
          break;
      }
    }

    loader->num_glyphs = n;

    if ( !notdef_found )
    {
      FT_ERROR(( "t42_parse_charstrings: no /.notdef glyph\n" ));
      error = FT_THROW( Invalid_File_Format );
      goto Fail;
    }

    /* if /.notdef does not occupy index 0, do our magic. */
    if ( ft_strcmp( (const char*)".notdef",
                    (const char*)name_table->elements[0] ) )
    {
      /* Swap glyph in index 0 with /.notdef glyph.  First, add index 0  */
      /* name and code entries to swap_table.  Then place notdef_index   */
      /* name and code entries into swap_table.  Then swap name and code */
      /* entries at indices notdef_index and 0 using values stored in    */
      /* swap_table.                                                     */

      /* Index 0 name */
      error = T1_Add_Table( swap_table, 0,
                            name_table->elements[0],
                            name_table->lengths [0] );
      if ( error )
        goto Fail;

      /* Index 0 code */
      error = T1_Add_Table( swap_table, 1,
                            code_table->elements[0],
                            code_table->lengths [0] );
      if ( error )
        goto Fail;

      /* Index notdef_index name */
      error = T1_Add_Table( swap_table, 2,
                            name_table->elements[notdef_index],
                            name_table->lengths [notdef_index] );
      if ( error )
        goto Fail;

      /* Index notdef_index code */
      error = T1_Add_Table( swap_table, 3,
                            code_table->elements[notdef_index],
                            code_table->lengths [notdef_index] );
      if ( error )
        goto Fail;

      error = T1_Add_Table( name_table, notdef_index,
                            swap_table->elements[0],
                            swap_table->lengths [0] );
      if ( error )
        goto Fail;

      error = T1_Add_Table( code_table, notdef_index,
                            swap_table->elements[1],
                            swap_table->lengths [1] );
      if ( error )
        goto Fail;

      error = T1_Add_Table( name_table, 0,
                            swap_table->elements[2],
                            swap_table->lengths [2] );
      if ( error )
        goto Fail;

      error = T1_Add_Table( code_table, 0,
                            swap_table->elements[3],
                            swap_table->lengths [3] );
      if ( error )
        goto Fail;

    }

    return;

  Fail:
    parser->root.error = error;
  }