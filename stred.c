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


int Replace(char *String, char From, char To)
{

  int Replaced=0;

  if( From == '\0' )
    return(Replaced);

  for( ; *String != '\0'; String++ )
    if( *String == From ) {
      *String = To;
    Replaced++;
    }

  return(Replaced);
}

int Delete(char *String, char From)
{
  
  int Deleted = 0;
  char *c;
  
  if( From == '\0' )
    return(Deleted);
  
  for( ; *String != '\0'; String++ )
    if( *String == From ) {
      c = String;
      for( ;; c++ ) {
	*c = *(c+1);
	if( *c == '\0' ) 
	  break;
      }
      Deleted++;
      String--;
    }
  return(Deleted);
}
  
