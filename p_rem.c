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

int Process_REMARK(BUFFER Buffer, enum METHOD *Method, float *Resolution, BOOLEAN *DsspAssigned)
{
  char *Field[MAX_FIELD];
  int NFields;

  NFields = SplitString(Buffer,Field,10);
  
  if( NFields >= 5 &&  !strncmp(Field[2],"RESOLUTION",10) && 
      !strncmp(Field[4],"ANGSTROMS",9) && isdigit(*Field[3]) ) 
    *Resolution = atof(Field[3]);

  if( NFields >= 9 && !strcmp(Field[2],"THESE") && !strcmp(Field[3],"COORDINATES") &&
      !strcmp(Field[4],"WERE")  && !strcmp(Field[5],"GENERATED") &&
      !strcmp(Field[6],"FROM")  && !strcmp(Field[7],"SOLUTION") &&
      ( !strcmp(Field[8],"NMR") || !strcmp(Field[8],"/NMR$") ) ) *Method = NMR;

  if( strstr(Buffer,"SANDER ") || strstr(Buffer,"SANDER,") || strstr(Buffer,"SANDER:") || 
      strstr(Buffer,"SANDER;") || strstr(Buffer,"SANDER.") || strstr(Buffer,"SANDER(") || 
      strstr(Buffer,"SANDER)") || strstr(Buffer,"DSSP") )
    *DsspAssigned = YES;
  
  return(SUCCESS);
}

