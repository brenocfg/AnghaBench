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
typedef  int UChar ;
typedef  int Int32 ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 int ADDWEIGHTS (int,int) ; 
 int /*<<< orphan*/  AssertH (int,int) ; 
 int BZ_MAX_ALPHA_SIZE ; 
 int /*<<< orphan*/  DOWNHEAP (int) ; 
 scalar_t__ False ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  UPHEAP (int) ; 

void BZ2_hbMakeCodeLengths ( UChar *len, 
                             Int32 *freq,
                             Int32 alphaSize,
                             Int32 maxLen )
{
   /*--
      Nodes and heap entries run from 1.  Entry 0
      for both the heap and nodes is a sentinel.
   --*/
   Int32 nNodes, nHeap, n1, n2, i, j, k;
   Bool  tooLong;

   Int32 heap   [ BZ_MAX_ALPHA_SIZE + 2 ];
   Int32 weight [ BZ_MAX_ALPHA_SIZE * 2 ];
   Int32 parent [ BZ_MAX_ALPHA_SIZE * 2 ]; 

   for (i = 0; i < alphaSize; i++)
      weight[i+1] = (freq[i] == 0 ? 1 : freq[i]) << 8;

   while (True) {

      nNodes = alphaSize;
      nHeap = 0;

      heap[0] = 0;
      weight[0] = 0;
      parent[0] = -2;

      for (i = 1; i <= alphaSize; i++) {
         parent[i] = -1;
         nHeap++;
         heap[nHeap] = i;
         UPHEAP(nHeap);
      }

      AssertH( nHeap < (BZ_MAX_ALPHA_SIZE+2), 2001 );
   
      while (nHeap > 1) {
         n1 = heap[1]; heap[1] = heap[nHeap]; nHeap--; DOWNHEAP(1);
         n2 = heap[1]; heap[1] = heap[nHeap]; nHeap--; DOWNHEAP(1);
         nNodes++;
         parent[n1] = parent[n2] = nNodes;
         weight[nNodes] = ADDWEIGHTS(weight[n1], weight[n2]);
         parent[nNodes] = -1;
         nHeap++;
         heap[nHeap] = nNodes;
         UPHEAP(nHeap);
      }

      AssertH( nNodes < (BZ_MAX_ALPHA_SIZE * 2), 2002 );

      tooLong = False;
      for (i = 1; i <= alphaSize; i++) {
         j = 0;
         k = i;
         while (parent[k] >= 0) { k = parent[k]; j++; }
         len[i-1] = j;
         if (j > maxLen) tooLong = True;
      }
      
      if (! tooLong) break;

      /* 17 Oct 04: keep-going condition for the following loop used
         to be 'i < alphaSize', which missed the last element,
         theoretically leading to the possibility of the compressor
         looping.  However, this count-scaling step is only needed if
         one of the generated Huffman code words is longer than
         maxLen, which up to and including version 1.0.2 was 20 bits,
         which is extremely unlikely.  In version 1.0.3 maxLen was
         changed to 17 bits, which has minimal effect on compression
         ratio, but does mean this scaling step is used from time to
         time, enough to verify that it works.

         This means that bzip2-1.0.3 and later will only produce
         Huffman codes with a maximum length of 17 bits.  However, in
         order to preserve backwards compatibility with bitstreams
         produced by versions pre-1.0.3, the decompressor must still
         handle lengths of up to 20. */

      for (i = 1; i <= alphaSize; i++) {
         j = weight[i] >> 8;
         j = 1 + (j / 2);
         weight[i] = j << 8;
      }
   }
}