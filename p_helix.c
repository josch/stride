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

int Process_HELIX(BUFFER Buffer, CHAIN **Chain, int *ChainNumber, COMMAND *Cmd)
{
  int CC, HC;
  char *Field[MAX_FIELD];
  BUFFER Tmp;

  if( Cmd->NActive && !ChInStr(Cmd->Active,SpaceToDash(Buffer[19])) )
     return(SUCCESS);
     
  for( CC=0; CC < *ChainNumber && Chain[CC]->Id != Buffer[19]; CC++ );

  if( CC == *ChainNumber ) {
    InitChain(&Chain[CC]); 
    Chain[CC]->Id = Buffer[19];
    (*ChainNumber)++;
  }

  HC = Chain[CC]->NHelix;
  Chain[CC]->Helix[HC] =  (HELIX *)ckalloc(sizeof(HELIX));

  SplitString(Buffer+15,Field,1);

  strcpy(Chain[CC]->Helix[HC]->Res1,Field[0]);

  SplitString(Buffer+27,Field,1);

  strcpy(Chain[CC]->Helix[HC]->Res2,Field[0]);

  strcpy(Tmp,Buffer);
  Tmp[25] = ' ';
  Tmp[37] = ' ';
  SplitString(Tmp+21,Field,1);
  strcpy(Chain[CC]->Helix[HC]->PDB_ResNumb1,Field[0]);
  SplitString(Tmp+33,Field,1);
  strcpy(Chain[CC]->Helix[HC]->PDB_ResNumb2,Field[0]);

  Chain[CC]->Helix[HC]->InsCode1 = Buffer[25];
  Chain[CC]->Helix[HC]->InsCode2 = Buffer[37];

  Tmp[40] = ' ';
  SplitString(Tmp+38,Field,1);
  Chain[CC]->Helix[HC]->Class = atoi(Field[0]);

  Chain[CC]->NHelix++;

  return(SUCCESS);
}

