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


void InitChain(CHAIN **Chain)
{
  
  *Chain = (CHAIN *)ckalloc(sizeof(CHAIN));

  (*Chain)->NRes                = 0;
  (*Chain)->NHetRes             = 0;
  (*Chain)->NonStandRes         = 0;
  (*Chain)->NHet                = 0;
  (*Chain)->NonStandAtom        = 0;
  (*Chain)->NHelix              = 0;
  (*Chain)->NSheet              = -1;
  (*Chain)->NTurn               = 0;
  (*Chain)->NAssignedTurn       = 0;
  (*Chain)->NBond               = 0;
  (*Chain)->NHydrBond           = 0;
  (*Chain)->NHydrBondTotal      = 0;
  (*Chain)->NHydrBondInterchain = 0;
  (*Chain)->Method              = XRay;
  (*Chain)->Ter                 = 0;
  (*Chain)->Resolution          = 0.0;

  (*Chain)->File                = (char           *)ckalloc(BUFSZ*sizeof(char));
  (*Chain)->Rsd                 = (RESIDUE       **)ckalloc(MAX_RES*sizeof(RESIDUE *));
  (*Chain)->HetRsd              = (HETERORESIDUE **)ckalloc(MAX_HETRES*sizeof(HETERORESIDUE *));
  (*Chain)->Het                 = (HET           **)ckalloc(MAX_HET*sizeof(HET *));
  (*Chain)->Helix               = (HELIX         **)ckalloc(MAX_HELIX*sizeof(HELIX *));
  (*Chain)->Sheet               = (SHEET         **)ckalloc(MAX_SHEET*sizeof(SHEET *));
  (*Chain)->Turn                = (TURN          **)ckalloc(MAX_TURN*sizeof(TURN *));
  (*Chain)->AssignedTurn        = (TURN          **)ckalloc(MAX_TURN*sizeof(TURN *));
  (*Chain)->SSbond              = (SSBOND        **)ckalloc(MAX_BOND*sizeof(SSBOND *));
  (*Chain)->Info                = (char          **)ckalloc(MAX_INFO*sizeof(char *));

  (*Chain)->Valid               = YES;
}

