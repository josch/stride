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


/* Split a char string into text fields */

#include "stride.h"

int SplitString(char *Buffer, char **Fields, int MaxField)
{
  int FieldCnt, SymbCnt, FieldFlag, BuffLen;
  static char LocalBuffer[BUFSZ];


  FieldCnt =0; FieldFlag = 0;
  BuffLen = (int)strlen(Buffer) - 1;

  strcpy(LocalBuffer,Buffer);

  for(SymbCnt=0; SymbCnt<BuffLen; SymbCnt++) {
    if( (isspace(LocalBuffer[SymbCnt])) && FieldFlag == 0 && SymbCnt != BuffLen-1 ) continue;
    if( (!isspace(LocalBuffer[SymbCnt])) && FieldFlag == 1 && SymbCnt == BuffLen-1 ) {
      LocalBuffer[SymbCnt+1] = '\0';
      return(FieldCnt);
    }
    else
    if( (isspace(LocalBuffer[SymbCnt])) && FieldFlag == 1 ) {
      LocalBuffer[SymbCnt] = '\0';
      FieldFlag = 0;
      if( FieldCnt == MaxField ) return(FieldCnt);
    }
    else
    if( (!isspace(LocalBuffer[SymbCnt])) && FieldFlag == 0 ) {
      FieldFlag = 1;
      Fields[FieldCnt] = LocalBuffer+SymbCnt;
      FieldCnt++;
    }
  }
  
     return(FieldCnt);
 }
