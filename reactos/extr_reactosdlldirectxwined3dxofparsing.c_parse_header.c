#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int txt; scalar_t__ rem_bytes; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ parse_buffer ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  decomp_file_size ;
typedef  int /*<<< orphan*/  decomp_chunk_size ;
typedef  int /*<<< orphan*/  comp_chunk_size ;
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DXFILEERR_BADALLOC ; 
 int /*<<< orphan*/  DXFILEERR_BADFILEFLOATSIZE ; 
 int /*<<< orphan*/  DXFILEERR_BADFILETYPE ; 
 int /*<<< orphan*/  DXFILEERR_BADFILEVERSION ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 scalar_t__ XOFFILE_FORMAT_BINARY ; 
 scalar_t__ XOFFILE_FORMAT_BINARY_MSZIP ; 
 scalar_t__ XOFFILE_FORMAT_FLOAT_BITS_32 ; 
 scalar_t__ XOFFILE_FORMAT_FLOAT_BITS_64 ; 
 scalar_t__ XOFFILE_FORMAT_MAGIC ; 
 scalar_t__ XOFFILE_FORMAT_TEXT ; 
 scalar_t__ XOFFILE_FORMAT_TEXT_MSZIP ; 
 scalar_t__ XOFFILE_FORMAT_VERSION_302 ; 
 scalar_t__ XOFFILE_FORMAT_VERSION_303 ; 
 int /*<<< orphan*/  d3dxof_parsing ; 
 int debugstr_fourcc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,int) ; 
 int mszip_decompress (scalar_t__,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  read_bytes (TYPE_1__*,scalar_t__*,int) ; 

HRESULT parse_header(parse_buffer * buf, BYTE ** decomp_buffer_ptr)
{
  /* X File common header:
   *  0-3  -> Magic Number (format identifier)
   *  4-7  -> Format Version
   *  8-11 -> Format Type (text or binary, decompressed or compressed)
   * 12-15 -> Float Size (32 or 64 bits) */
  DWORD header[4];

  if (!read_bytes(buf, header, sizeof(header)))
    return DXFILEERR_BADFILETYPE;

  if (TRACE_ON(d3dxof_parsing))
  {
    char string[17];
    memcpy(string, header, 16);
    string[16] = 0;
    TRACE("header = '%s'\n", string);
  }

  if (header[0] != XOFFILE_FORMAT_MAGIC)
    return DXFILEERR_BADFILETYPE;

  if (header[1] != XOFFILE_FORMAT_VERSION_302 && header[1] != XOFFILE_FORMAT_VERSION_303)
    return DXFILEERR_BADFILEVERSION;

  if (header[2] != XOFFILE_FORMAT_BINARY && header[2] != XOFFILE_FORMAT_TEXT &&
      header[2] != XOFFILE_FORMAT_BINARY_MSZIP && header[2] != XOFFILE_FORMAT_TEXT_MSZIP)
  {
    WARN("File type %s unknown\n", debugstr_fourcc(header[2]));
    return DXFILEERR_BADFILETYPE;
  }

  if (header[3] != XOFFILE_FORMAT_FLOAT_BITS_32 && header[3] != XOFFILE_FORMAT_FLOAT_BITS_64)
    return DXFILEERR_BADFILEFLOATSIZE;

  buf->txt = header[2] == XOFFILE_FORMAT_TEXT || header[2] == XOFFILE_FORMAT_TEXT_MSZIP;

  if (header[2] == XOFFILE_FORMAT_BINARY_MSZIP || header[2] == XOFFILE_FORMAT_TEXT_MSZIP)
  {
    /* Extended header for compressed data:
     * 16-19 -> size of decompressed file including xof header,
     * 20-21 -> size of first decompressed MSZIP chunk, 22-23 -> size of first compressed MSZIP chunk
     * 24-xx -> compressed MSZIP data chunk
     * xx-xx -> size of next decompressed MSZIP chunk, xx-xx -> size of next compressed MSZIP chunk
     * xx-xx -> compressed MSZIP data chunk
     * .............................................................................................. */
    int err;
    DWORD decomp_file_size;
    WORD decomp_chunk_size;
    WORD comp_chunk_size;
    LPBYTE decomp_buffer;

    if (!read_bytes(buf, &decomp_file_size, sizeof(decomp_file_size)))
      return DXFILEERR_BADFILETYPE;

    TRACE("Compressed format %s detected: decompressed file size with xof header = %d\n",
          debugstr_fourcc(header[2]), decomp_file_size);

    /* Does not take xof header into account */
    decomp_file_size -= 16;

    decomp_buffer = HeapAlloc(GetProcessHeap(), 0, decomp_file_size);
    if (!decomp_buffer)
    {
        ERR("Out of memory\n");
        return DXFILEERR_BADALLOC;
    }
    *decomp_buffer_ptr = decomp_buffer;

    while (buf->rem_bytes)
    {
      if (!read_bytes(buf, &decomp_chunk_size, sizeof(decomp_chunk_size)))
        return DXFILEERR_BADFILETYPE;
      if (!read_bytes(buf, &comp_chunk_size, sizeof(comp_chunk_size)))
        return DXFILEERR_BADFILETYPE;

      TRACE("Process chunk: compressed_size = %d, decompressed_size = %d\n",
            comp_chunk_size, decomp_chunk_size);

      err = mszip_decompress(comp_chunk_size, decomp_chunk_size, (char*)buf->buffer, (char*)decomp_buffer);
      if (err)
      {
        WARN("Error while decompressing MSZIP chunk %d\n", err);
        HeapFree(GetProcessHeap(), 0, decomp_buffer);
        return DXFILEERR_BADALLOC;
      }
      buf->rem_bytes -= comp_chunk_size;
      buf->buffer += comp_chunk_size;
      decomp_buffer += decomp_chunk_size;
    }

    if ((decomp_buffer - *decomp_buffer_ptr) != decomp_file_size)
      ERR("Size of all decompressed chunks (%u) does not match decompressed file size (%u)\n",
          (DWORD)(decomp_buffer - *decomp_buffer_ptr), decomp_file_size);

    /* Use decompressed data */
    buf->buffer = *decomp_buffer_ptr;
    buf->rem_bytes = decomp_file_size;
  }

  TRACE("Header is correct\n");

  return S_OK;
}