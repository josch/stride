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

int Process_SSBOND(BUFFER Buffer, CHAIN **Chain, int *ChainNumber, COMMAND *Cmd)
{
  int CC, BC;
  char *Field[MAX_FIELD];
  BUFFER Tmp;

  if( Cmd->NActive && !ChInStr(Cmd->Active,SpaceToDash(Buffer[15])) )
     return(SUCCESS);

  CC = 0;

  if( *ChainNumber == 0 ) {
    InitChain(&Chain[CC]); 
    Chain[CC]->Id = Buffer[15];
    (*ChainNumber)++;
  }

  BC = Chain[CC]->NBond;
  Chain[CC]->SSbond[BC] =  (SSBOND *)ckalloc(sizeof(SSBOND));

  strcpy(Tmp,Buffer);
  Tmp[21] = ' ';
  Tmp[35] = ' ';
  SplitString(Tmp+17,Field,1);
  strcpy(Chain[CC]->SSbond[BC]->PDB_ResNumb1,Field[0]);
  SplitString(Tmp+31,Field,1);
  strcpy(Chain[CC]->SSbond[BC]->PDB_ResNumb2,Field[0]);

  Chain[CC]->SSbond[BC]->ChainId1 = Buffer[15];
  Chain[CC]->SSbond[BC]->ChainId2 = Buffer[29];

  Chain[CC]->SSbond[BC]->InsCode1 = Buffer[21];
  Chain[CC]->SSbond[BC]->InsCode2 = Buffer[35];

  Chain[CC]->SSbond[BC]->AsnSource = Pdb;

  Chain[CC]->NBond++;

  return(SUCCESS);
}

