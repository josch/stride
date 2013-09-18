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


#include <string.h>
#include <stdio.h>

char ThreeToOne(char *Three)
{
  if( !strcmp(Three,"ALA") ) return('A');
  else if( !strcmp(Three,"ARG") ) return('R');
  else if( !strcmp(Three,"ASN") ) return('N');
  else if( !strcmp(Three,"ASP") ) return('D');
  else if( !strcmp(Three,"ASX") ) return('B');
  else if( !strcmp(Three,"CYS") ) return('C');
  else if( !strcmp(Three,"GLN") ) return('Q');
  else if( !strcmp(Three,"GLU") ) return('E');
  else if( !strcmp(Three,"GLX") ) return('Z');
  else if( !strcmp(Three,"GLY") ) return('G');
  else if( !strcmp(Three,"HIS") ) return('H');
  else if( !strcmp(Three,"ILE") ) return('I');
  else if( !strcmp(Three,"LEU") ) return('L');
  else if( !strcmp(Three,"LYS") ) return('K');
  else if( !strcmp(Three,"MET") ) return('M');
  else if( !strcmp(Three,"PRO") ) return('P');
  else if( !strcmp(Three,"PHE") ) return('F');
  else if( !strcmp(Three,"SER") ) return('S');
  else if( !strcmp(Three,"THR") ) return('T');
  else if( !strcmp(Three,"TRP") ) return('W');
  else if( !strcmp(Three,"TYR") ) return('Y');
  else if( !strcmp(Three,"VAL") ) return('V');
  else    return('X');
}
      
