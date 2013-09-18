/*
 * Copyright (C) 1992-1994 Dmitrij Frishman <d.frishman at wzw.tum.de>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "stride.h"

int OutSeq(CHAIN **Chain, int NChain, COMMAND *Cmd)
{
  int Cn, Res;
  FILE *Seq;

  if( (int)strlen(Cmd->SeqFile) == 0 )
    Seq = stdout;
  else 
    if( (Seq = fopen(Cmd->SeqFile,"a")) == NULL )
      die("Error writing sequence file %s\n",Cmd->SeqFile);

  for( Cn=0; Cn<NChain; Cn++ ) {

    if( !Chain[Cn]->Valid )
       continue;

    fprintf(Seq,">%s %c  %d %7.3f\n",
	    Chain[Cn]->File,SpaceToDash(Chain[Cn]->Id),Chain[Cn]->NRes,
	    Chain[Cn]->Resolution);

    for( Res=0; Res<Chain[Cn]->NRes; Res++ ) {
      if( Res%60 == 0 && Res != 0 ) fprintf(Seq,"\n");
      fprintf(Seq,"%c",ThreeToOne(Chain[Cn]->Rsd[Res]->ResType));
    }
    fprintf(Seq,"\n");
  }
  fclose(Seq);
  exit(0);

  return(SUCCESS);
}

      

