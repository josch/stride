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

int CheckAtom(char *At)
{
  int AtomTypeCnt, AtomTypeNumber = 95;
  static char *Atom[MAX_AtomType] = {
    "AD1", "AD2", "AE1", "AE2", "C", "CA", "CB", "CD", "CD1", "CD2", "CE", "CE1", "CE2", 
    "CE3", "CG", "CG1", "CG2", "CH2", "CH3", "CZ", "CZ2", "CZ3", "HG", "HG1", "HH", "HH2", 
    "HZ", "HZ2", "HZ3", "N", "ND1", "ND2", "NE", "NE1", "NE2", "NH1", "NH2", "NZ", "O", 
    "OD1", "OD2", "OE", "OE1", "OE2", "OG", "OG1", "OH", "OXT", "SD", "SG", "H", "HA", "HB", 
    "HD1", "HD2", "HE", "HE1", "HE2", "HE3", "1H", "1HA", "1HB", "1HD", "1HD1", "1HD2", 
    "1HE", "1HE2", "1HG", "1HG1", "1HG2", "1HH1", "1HH2", "1HZ", "2H", "2HA", "2HB", "2HD", 
    "2HD1", "2HD2", "2HE", "2HE2", "2HG", "2HG1", "2HG2", "2HH1", "2HH2", "2HZ", "3H", "3HB", 
    "3HD1", "3HD2", "3HE", "3HG1", "3HG2", "3HZ"
    };

  for( AtomTypeCnt=0; AtomTypeCnt<AtomTypeNumber; AtomTypeCnt++ )
    if( !strcmp(At,Atom[AtomTypeCnt]) ) 
      return(SUCCESS);

  return(FAILURE);
}
      

