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

FILE *efopen(char *file, char *mode, char *progname)    /* fopen file, die if can't */
{
  FILE *fp;
  
  if( (fp=fopen(file,mode)) ) 
    return fp;
  else 
    die("%s: can't open file %s mode %s\n",progname,file,mode);
  return(FAILURE);
}


int Uniq(char **List, int ListLength)
{
    int i, j;

    for( i=1; i<ListLength-1; i++ ) {
      if( *List[i] != '-' ) continue;
      for( j=i+1; j<ListLength; j++ ) {
	if( *List[j] != '-' ) continue;
	if( !strcmp(List[i],List[j] ) ) return(0);
      }
    }
    
    return(1);
}

BOOLEAN Specified(char **List, int ListLength, char Option)
{
    int i;

    for( i=1; i<ListLength; i++ )
      if( *List[i] == '-' && *(List[i]+1) == Option ) 
	return(YES);

    return(NO);
}

int Parse(char **List, int ListLength, char *Option)
{
    int i;

    for( i=1; i<ListLength; i++ ) {
      if( *List[i] != '-' ) continue;
      if( !strcmp(List[i],Option) ) return(i);
    }
    
    return(0);
}

int CollectOptions(char **List, int ListLength, int Stream, int *Options)
{
    int OptCnt, i;

    OptCnt = 0;

    for( i=1; i<ListLength; i++ )
	if( *List[i] == '-' && !isdigit( *(List[i]+1) ) && atoi( List[i]+2 ) == Stream )
	    Options[OptCnt++] = i;

    return(OptCnt);

}



