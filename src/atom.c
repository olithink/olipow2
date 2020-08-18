/* OliPow Version 2.2e Atomic Part */

void thinkatom(void)
{
  int stellungswert=0,absmat=-WK,legalanzahl=0,bzug=0,dfl2=0;
  int alpha=SCHLECHT,beta,maximum,drw,startd;
  int i,j,w=0,d,kp,zfall=0,re1,re2,repfl=0,atex=3,zuf=ZUFALL;
  int legals[MAXMGL],legalz[MAXMGL],kil[MAXMGL];

  nm=0;abbruch=0;ply=0;endtiefe=1;kib=1;
  restnode=NODEC;zuf*=4;
  altmat=material;balt=0;walt=wold;d=dran+1;ner++;
  start=myget();
  for (i=21;i<=91;i+=10)
    for (j=i;j<i+8;j++) 
      if (dran*Board[j]<WP) absmat-=dran*Board[j];
  if (absmat<ABSMATT) { endspiel=1;pawnstorm=3*PAWNS; }
  kp=koenig[d];
  if (ZUFALL>=1 && numhalbz<40) zfall=(int)(12347*rand());
  for (i=0;i<MAXTIEF-2;i++) 
  { Hvon[0][i]=Hvon[0][i+2]; Hnach[0][i]=Hnach[0][i+2];
    Kvon[i]=Kvon[i+2]; Knach[i]=Knach[i+2];
    K2von[i]=K2von[i+2]; K2nach[i]=K2nach[i+2];
  }
  for (i=0;i<BDIM;i++) 
    for (j=0;j<BDIM;j++) History[i][j]=0;

  for (zugtiefe=STARTDEPTH;zugtiefe<=maxt+atex;zugtiefe++)
  { 
    Htief[ply]=ply;
    if (zugtiefe==STARTDEPTH) { alpha=SCHLECHT;beta=GUT; } 
    else { beta=alpha+WIND;alpha-=WIND; }
    legalanzahl=genatom(&legals[0],&legalz[0],&kil[0],-1);

    if (legalanzahl==0) matt();
    { if (Board[koenig[dran+1]]==LEER || Board[koenig[1-dran]]==LEER) matt(); }

  if (legalanzahl>ONEDEBUG) 
  { for (i=0;i<legalanzahl;i++)
    { szug=legals[i]; 
      zug=legalz[i];
      ezug=szug+zug; drw=1;
      if (ZUFALL==0 || ner>ZUFEND) zugspec=0; 
      else zugspec=((zfall+i*i*i-6*i*i)%zuf);
      zugspec+=zugbonus(legals[i],legals[i]+legalz[i],kil[i],dran,kp);
      makemoveatom(kil[i]);
      numhalbz++; ply++;
      if (rep>5) if (kil[i]>=24 && kil[i]<=28) 
        { repfl=0;re1=0;re2=0;
          for (j=BANF;j<BEND;j++) 
          { re1-=Board[j]*j*3;
            re2+=Board[j]*(j-70)*(j-80); 
          }
          for (j=1;j<=rep;j++) 
            if (reph1[j]==re1 && reph2[j]==re2) repfl++;
          if (repfl>=1) { w=DRAW; drw=0; }
          if (repfl>=2 || rep>100) { w=DRAW; drw=0; dfl2=1; }
        }                        /* Drawn by repitition/50 moves*/
      if (drw) 
        w=-searchatom(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
SHOWB1
      if (i==0 && abbruch==0) 
       { if (w<alpha) 
         { alpha=SCHLECHT; beta=w;
           if (drw)
             w=-searchatom(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]); }
         else if (w>=beta) 
         { alpha=w; beta=GUT;
           if (drw)
             w=-searchatom(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
         }
       alpha=w; beta=alpha+1; 
       KopPV(0,legals[i],legalz[i]); bzug=i;
HAUPT1
       }
       else 
       { if (w>alpha) 
         { maximum=alpha;alpha=w;beta=GUT;
           if (drw)
             w=-searchatom(-beta,-alpha,zugtiefe-1,legalanzahl,lzz,kil[i]);
           if (w>maximum) 
           { alpha=w;beta=alpha+1;bzug=i;
             KopPV(0,legals[i],legalz[i]);
HAUPT1
             History[legals[i]][legalz[i]+legals[i]]+=zugtiefe;
           }
         }
       }
      numhalbz--; ply--; takebackatom(); 
      if (abbruch>=1) {legalanzahl=i;break;}
    }
  }
  maximum=alpha;
  if (legalanzahl<=0) {bzug=0;maximum=walt;}
SHOWA1
   stellungswert=maximum;
   if (legalanzahl==0 && zugtiefe>STARTDEPTH)
   { zug=hzug;szug=hszug;kllz=hk;
   }
   else
   { zug=legalz[bzug];
     szug=legals[bzug];
     kllz=kil[bzug];
     hszug=szug;hzug=zug;hk=kllz;
   }
   ezug=szug+zug;
   balt=bzug; walt=stellungswert;
   if (abbruch>=1) break;
   if (legalanzahl==ONEDEBUG) { kib=0;break; }
   ende=myget();
   if (ende-start>=timeformove/DEEPER) {abbruch=1;break;} 
   if (stellungswert>29000) {abbruch=1;break;}
  }
  if (abbruch==0) zugtiefe--;
  stim=stim+ende-start;
  if (i>1) wold=stellungswert;
   if (kib==1) 
   { sprintf(wh,"whisper %g (%d/%d)%c\n",1.0*wold/100,zugtiefe
     ,endtiefe+1,(abbruch==2 ? '~' : '#')); 
     if (stellungswert>29000)
       printf("kibitz Forced win in %d moves\n",(101-(stellungswert-1)%100)/2);
   }
   if (xboard!=1) 
     printf(" Stellungswert: %d %d (%d) in %ld hundsek , insgesamt: %ld hunsek\n",stellungswert,nm,endtiefe,ende-start,stim);
   if (dfl2==1 && stellungswert==DRAW) 
   { if (rep>99) dr50=1;
     else drr=1; 
     printf("draw\n"); fflush(stdout);
   }
if (kib)
{ if (resign)
  { if (otim>7500 && stellungswert<=-1350)
    { if ((stellungswert+800-ratdiff-(otim-8500)/30)<0) stellungswert=-30001; }
  }
  if (CRBOOK>0) {
   StartZug[numhalbz]=szug; EndZug[numhalbz]=ezug;
   if (stellungswert>29000 && EDFLAG==0 && (ratdiff>=0)) createbook(dran);
   if (stellungswert<-29000 && EDFLAG==0 && CRBOOK>1) createbook(dran*WECHSEL);
  }
  if (stellungswert<=-29998)
  { printf("resign\n");
    printf(compfarbe==1 ? "Black Wins!\n":"White Wins!\n");
    fflush(stdout); eingzug(0,0); }
}
}

int genatom(int *lsu,int *lzu,int *kilu,int schach)
{
  int ls[MAXMGL],lz[MAXMGL],kil[MAXMGL];
  int anz=0,dfeld,rfl,reihe,neben,tausch,ffl,FK2=FK,inc=1;
  int i,j,k,l,n,w,w2,fig,szugvar,bewpoint,kpos,janus;
  int reichw,bewbauer,diagonal,fessel[8],fesselr[8],anzfes;
  dfeld=1+dran; anz=0; anzfes=0; schach=0;
        
  for (i=BANF;i<BEND;i++) 
  { w=Board[i];
    if (w!=RAND) 
    { w*=dran;
      if (w>0) 
      {
        fig=FP;
        if (w==WN) fig=FN;
         else if (w==WB) fig=FB;
          else if (w==WR) fig=FR;
           else if (w==WQ) fig=FQ;
            else if (w==WK) fig=FK; 
        if (fig==FP)                  /* Pawns */
        { reihe=(int)(i/10);
          if (reihe==siebtereihe[dfeld]) tausch=1;
              else tausch=0;
          if (reihe==zweitereihe[dfeld]) bewbauer=2;
              else bewbauer=1; 
          if (reihe==fuenftereihe[dfeld])
            if (EnPassant[numhalbz-1]>0) 
            { neben=EndZug[numhalbz-1]-i;
              if ((neben==1) || (neben==-1))
              { ls[anz]=i,lz[anz]=10*dran+neben;kil[anz]=11;inc=1;
                if (checkatom(ls[anz],lz[anz],kil[anz])!=0) inc=0;
                anz+=inc;
              }
            }   
          for (j=0;j<2;j++)
          { diagonal=dran*beweg[j];
            szugvar=i+diagonal; 
            w2=Board[szugvar];
            if (w2!=RAND) 
            { w2*=dran;
	      if (w2<0)
	      { if (tausch==0)
	        { ls[anz]=i; lz[anz]=diagonal; kil[anz]=0; 
                  { if (schach!=0)
                      if (checkatom(ls[anz],lz[anz],kil[anz])!=0) anz--;
                  }
                  anz++; 
                }
                else
                { for (l=FN;l<FK2;l++)
                  { ls[anz]=i; lz[anz]=diagonal; kil[anz]=11+l*2;
                    { if (schach!=0)
                        if (checkatom(ls[anz],lz[anz],kil[anz])!=0) anz--;
                    }
                    anz++;  
                  }
                }
              }
            }
          }
          diagonal=dran*beweg[2];
          szugvar=i;
          for (k=0;k<bewbauer;k++)
          { szugvar=szugvar+diagonal;
            w2=Board[szugvar];
            if (w2!=RAND) 
            { if (w2!=0) break;
              else 
              { if (tausch==0)
                { ls[anz]=i;lz[anz]=diagonal*(k+1);kil[anz]=23;
                  { if (schach!=0)
                      if (checkatom(ls[anz],lz[anz],kil[anz])!=0) anz--;
                  }
                  anz++; 
                }
                else
                { for (l=FN;l<FK2;l++)
                  { ls[anz]=i;lz[anz]=diagonal*(k+1);kil[anz]=10+l*2;
                    { if (schach!=0)
                        if (checkatom(ls[anz],lz[anz],kil[anz])!=0) anz--;
                    }
                    anz++;
                  } 
                }
              }
            }
          }
        }
        else   /* other figures */
        {
        { for (j=0;j<bewanz[fig];j++)
          { szugvar=i;
            bewpoint=beweg[fig*8+j];
            reichw=bewfla[fig];
            for (k=1;k<=reichw;k++)
            { szugvar=szugvar+bewpoint; 
              w2=Board[szugvar];
              if (w2==RAND) break;
              else 
              { w2*=dran;
                if (w2>0) break;
                else 
                { ls[anz]=i;
                  lz[anz]=k*bewpoint;
                  if (w2<0) { kil[anz]=fig; k=9; } 
                  else kil[anz]=fig+23;
                  { if (schach!=0 || fig==FK)
                      if (checkatom(ls[anz],lz[anz],kil[anz])!=0) anz--;
                  }
                  anz++; 
                }
            }
          }
        }
      }
      if (fig==FK)   /* CASTLE */
      { if (rochiert[dfeld]==0)  
        { rfl=0; 
          for (j=numhalbz-2;j>2;j-=2)
            if (StartZug[j]==rochkoen[dfeld]) { rfl=1;break; }
          if (rfl==0)
             for (j=dfeld;j<dfeld+2;j++)
             { rfl=0; 
               for (n=numhalbz-2;n>2;n-=2)
                 if (StartZug[n]==rochturm[j]) { rfl=1;break; }
               if (rfl==0)
               { rfl=0; 
                 for (k=rochchk1[j];k<=rochchk2[j];k++)
                  if (Board[k]!=rochfeld[j][k-rochchk1[j]]) { rfl=1; break; }
                 if (rfl==0)
                   for (k=rochchk3[j];k<=rochchk4[j];k++)
                     if (attacked(k)>0) {rfl=1; break;} 
                 if (rfl==0)
                 { ls[anz]=rochkoen[j];
                   lz[anz]=rochdir[j]*2;
                   kil[anz]=30+j; 
                   anz++; 
                 }
               }
             }
           }
         }       
       }
     }
   }          
 }
  j=0;for (i=0;i<anz;i++)
  {
   if (ls[i]==Hvon[0][ply]) if (lz[i]==Hnach[0][ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
   { if (ls[i]==Kvon[ply]) if (lz[i]==Knach[ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
   }
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
   { if (ls[i]==K2von[ply]) if (lz[i]==K2nach[ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
   }
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]==0)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;}
  }
  for (i=0;i<anz;i++)
  { 
   if (kil[i]>=0) 
   { if (kil[i]<22)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;}
   }
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
   { if (History[ls[i]][ls[i]+lz[i]]>2)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;}
   }
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];j++;}
  }
  return anz;
}

int captureatomic(int *lsu,int *lzu,int *kilu,int schach)
{
  int ls[MAXMGL],lz[MAXMGL],kil[MAXMGL];
  int anz=0,dfeld,rfl,reihe,neben,tausch,ffl,FK2=FK,inc=1;
  int i,j,k,l,n,w,w2,fig,szugvar,bewpoint,kpos,janus;
  int reichw,bewbauer,diagonal,fessel[8],fesselr[8],anzfes;
  dfeld=1+dran; anz=0; anzfes=0;

  for (i=BANF;i<BEND;i++)
  { w=Board[i];
    if (w!=RAND)
    { w*=dran;
      if (w>0)
      {
        fig=FP;
        if (w==WN) fig=FN;
         else if (w==WB) fig=FB;
          else if (w==WR) fig=FR;
           else if (w==WQ) fig=FQ;
            else if (w==WK) fig=FK;
        if (fig==FP)                  /* Pawns */
        { reihe=(int)(i/10);
          if (reihe==siebtereihe[dfeld]) tausch=1;
              else tausch=0;
          if (reihe==fuenftereihe[dfeld])
            if (EnPassant[numhalbz-1]>0)
            { neben=EndZug[numhalbz-1]-i;
              if ((neben==1) || (neben==-1))
              { ls[anz]=i,lz[anz]=10*dran+neben;kil[anz]=11;inc=1;
                {
                  if (checkatom(ls[anz],lz[anz],kil[anz])!=0) inc=0;
                }
                anz+=inc;
              }
            }
          for (j=0;j<2;j++)
          { diagonal=dran*beweg[j];
            szugvar=i+diagonal;
            w2=Board[szugvar];
            if (w2!=RAND)
            { w2*=dran;
              if (w2<0)
              { if (tausch==0)
                { ls[anz]=i; lz[anz]=diagonal; kil[anz]=0;
                    {
                      if (checkatom(ls[anz],lz[anz],kil[anz])!=0) anz--;
                    }
                  anz++;
                }
                else
                { for (l=FN;l<FK2;l++)
                  { ls[anz]=i; lz[anz]=diagonal; kil[anz]=11+l*2;
                    {
                        if (checkatom(ls[anz],lz[anz],kil[anz])!=0) anz--;
                    }
                    anz++;
                  }
                }
              }
            }
          }
          if (tausch!=0)
          {
            { w2=Board[i+dran*10];
              if (w2==LEER)
              { for (l=FN;l<FK2;l++)
                  { ls[anz]=i;lz[anz]=dran*10;kil[anz]=10+l*2;
                    if (checkatom(ls[anz],lz[anz],kil[anz])!=0) anz--;
                    anz++;
                  }
              }
            }
          }
        }
        else   /* other figures */
        {
        { for (j=0;j<bewanz[fig];j++)
          { szugvar=i;
            bewpoint=beweg[fig*8+j];
            reichw=bewfla[fig];
            for (k=1;k<=reichw;k++)
            { szugvar=szugvar+bewpoint;
              w2=Board[szugvar];
              if (type!=TYPEA)
              { for (n=0;n<anzfes;n++)
                  if (i==fessel[n])
                    if (abs(bewpoint)!=fesselr[n]) w2=RAND;
              }
              if (w2==RAND) break;
              else
              { w2*=dran;
                if (w2>0) break;
                else
                { if (w2<0)
                  {
                  ls[anz]=i;
                  lz[anz]=k*bewpoint;
                  kil[anz]=fig; k=9;
                  {
                      if (checkatom(ls[anz],lz[anz],kil[anz])!=0) anz--;
                  }
                  anz++;
                  }
                }
              }
            }
          }
        }
      }
     }
   }
 }
  j=0;for (i=0;i<anz;i++)
  {
   if (ls[i]==Hvon[0][ply]) if (lz[i]==Hnach[0][ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
   { if (ls[i]==Kvon[ply]) if (lz[i]==Knach[ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
   }
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
   { if (ls[i]==K2von[ply]) if (lz[i]==K2nach[ply])
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;break;}
   }
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]==0)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];kil[i]=-1;j++;}
  }
  for (i=0;i<anz;i++)
  {
   if (kil[i]>=0)
     { lsu[j]=ls[i];lzu[j]=lz[i];kilu[j]=kil[i];j++;}
  }
  return anz;
}


void makemoveatom(int kilflag)
{
 KillFlag[numhalbz]=kilflag;
 if ( kilflag < 30 )
  {
   StartZug[numhalbz]=szug;
   EndZug[numhalbz]=ezug;
   SchlZug[numhalbz][0]=Board[ezug];
   if (kilflag<7)
   { material-=Board[ezug];
   }
 { if (kilflag<12 || kilflag==13 || kilflag==15 || kilflag==17 || kilflag==19)
   { int i,f;
    Board[ezug]=LEER;material-=Board[szug];
    SchlZug[numhalbz][9]=Board[szug];
    for (i=1;i<9;i++)
    { f=Board[ezug+stern[i-1]];
      SchlZug[numhalbz][i]=f;
      if (f!=RAND)
        if (abs(f)!=WP)
           { material-=f; Board[ezug+stern[i-1]]=LEER; }
    }
   }
   else
   {
     Board[ezug]=Board[szug];
   if (kilflag<22) if (kilflag>11)
     { material-=Board[ezug];
       material-=SchlZug[numhalbz][0];
       Board[ezug]=dran*Figur[(kilflag-10)/2]; 
       material+=Board[ezug];
     }
   }
 }
   if (kilflag==23)
   { if (zug==dran*20) EnPassant[numhalbz]=szug; }
   else    
     if (Board[szug]==dran*WK) { koenig[dran+1]=ezug; }
   Board[szug]=LEER;
   if (kilflag==11)
     { material-=Board[ezug-dran*10];
       Board[ezug-dran*10]=LEER; 
       SchlZug[numhalbz][0]=dran*BP; 
     }
  }
  else
  {
   StartZug[numhalbz]=szug;
   EndZug[numhalbz]=ezug;
   SchlZug[numhalbz][0]=kilflag;
   Board[ezug]=Board[szug];
   Board[szug]=LEER;
   Board[szug+rochdir[kilflag-30]]=Board[rochturm[kilflag-30]];
   Board[rochturm[kilflag-30]]=LEER;
   Rochade[numhalbz]=kilflag;
   koenig[dran+1]=ezug;
   rochiert[dran+1]=1;
  }
}

void takebackatom(void)
{ int kilflag;
  kilflag=KillFlag[numhalbz];
  if ( Rochade[numhalbz]==0 )
  {
   EnPassant[numhalbz]=0;
   szug=StartZug[numhalbz];
   ezug=EndZug[numhalbz];
 { if (kilflag<12 || kilflag==13 || kilflag==15 || kilflag==17 || kilflag==19)
   { int i,f;
    Board[szug]=SchlZug[numhalbz][9];material+=Board[szug];
    for (i=1;i<9;i++)
    { 
      f=SchlZug[numhalbz][i];
      Board[ezug+stern[i-1]]=f;
      if (f!=RAND)
        if (abs(f)!=WP)
           { material+=f; }
    }
   }
   else 
   {
     Board[szug]=Board[ezug];
   if (kilflag>11) if (kilflag<23) 
   { material-=Board[szug];
     Board[szug]=dran*WP;
     material+=Board[szug];
     material+=SchlZug[numhalbz][0];
   }
   }
 }
   if (kilflag==0 || kilflag==23 || kilflag==11)
   {
     pawnrank[szug / 10][dran+1]++;
     pawnrank[ezug / 10][dran+1]--;
   }
   if (Board[ezug]==dran*WK)
     koenig[dran+1]=szug;
   Board[ezug]=SchlZug[numhalbz][0];
   if (kilflag==11)
   { 
     Board[ezug]=LEER; 
     Board[ezug-dran*10]=dran*BP; 
     material+=dran*BP;
   } 
   if (kilflag<7)
   { material+=Board[ezug];
   }
  }
  else
  {
   rochiert[dran+1]=0;
   Rochade[numhalbz]=0;
   szug=StartZug[numhalbz];
   koenig[dran+1]=szug;
   ezug=EndZug[numhalbz];
   Board[szug]=Board[ezug];
   Board[ezug]=LEER;
   Board[rochturm[SchlZug[numhalbz][0]-30]]=Board[szug+rochdir[SchlZug[numhalbz][0]-30]];
   Board[szug+rochdir[SchlZug[numhalbz][0]-30]]=LEER; 
   }
}

int quiesceatom(int alpha,int beta,int anz,int anz2,int kfl)
{
  int i,w,schfl=-1,sfl2,zugt;
  int maximum=alpha;int legalanzahl,wert;
  int legals[MAXMGL];
  int legalz[MAXMGL];
  int kil[MAXMGL]; /* REL */
  if (nm-restnode>0)
      { ende=myget();
        restnode+=NODEC;
        if (ende-start>=timeformove && zugtiefe>STARTDEPTH) abbruch=2;
      }
  if (abbruch>0) return GUT; 
  Htief[ply]=ply;
  if (ply>endtiefe) endtiefe=ply;
  nm++;
  dran*=WECHSEL;
  {
    wert=atomeval(); 
    dran*=WECHSEL;return (wert);
   if (wert>=beta) {dran*=WECHSEL;return (wert);} 
    if (wert>alpha) alpha=wert;
    legalanzahl=schlagzuege(&legals[0],&legalz[0],&kil[0],schfl);
  }

  for (i=0;i<legalanzahl;i++)
  {
    szug=legals[i]; zug=legalz[i]; sfl2=0; ezug=szug+zug;
    makemoveatom(kil[i]); 
    if (Board[koenig[1-dran]]==LEER) w=GUT-ply;
    else {
        numhalbz+=1; ply++;
        w=-quiesceatom(-beta,-alpha,legalanzahl,anz,kil[i]);
        numhalbz-=1; ply--;
         }
        takebackatom();
    if (w>alpha) {alpha=w;KopPV(ply,legals[i],legalz[i]);
       if (w>=beta) 
       { if (i>0) 
         { 
           K2von[ply]=Kvon[ply];K2nach[ply]=Knach[ply];
           Kvon[ply]=legals[i];Knach[ply]=legalz[i];
          } 
       dran*=WECHSEL;return(w);}
       }
    
  }
  dran*=WECHSEL;
  return (alpha);  
}

int searchatom(int alpha,int beta,int dist,int anz,int anz2,int kfl)
{
  int i,w,schfl=-1,sfl2,zugt;
  int maximum=SCHLECHT;int legalanzahl=0,wert;
  int legals[MAXMGL];
  int legalz[MAXMGL];
  int kil[MAXMGL]; /* REK */
  if (nm-restnode>0)   /* Here we check each NODEC nodes for time */
      { ende=myget();
        restnode+=NODEC;
        if (ende-start>=timeformove && zugtiefe>STARTDEPTH) abbruch=2;
      }
  if (abbruch>0) return GUT; 

  if (dist<=0) 
  { 
      return(quiesceatom(alpha,beta,anz,anz2,kfl));
  }
  dran*=WECHSEL;
  nm++;
  if (ply>endtiefe) endtiefe=ply;
  Htief[ply]=ply;
  legalanzahl=genatom(&legals[0],&legalz[0],&kil[0],schfl);
  zugt=zugtiefe;


  for (i=0;i<legalanzahl;i++)
  {
    szug=legals[i]; zug=legalz[i]; ezug=szug+zug;
    makemoveatom(kil[i]); 
    if (Board[koenig[1-dran]]==LEER) w=GUT-ply;
    else {
        numhalbz++; ply++;
        w=-searchatom(-beta,-alpha,dist-1,legalanzahl,anz,kil[i]);
        numhalbz--; ply--;
         }
SHOWC1
        takebackatom();
        if (abbruch>0) {dran*=WECHSEL;return GUT;}
    if (w>maximum) {maximum=w;KopPV(ply,legals[i],legalz[i]);
       if (w>=beta) 
       { if (i>0) 
         { 
           K2von[ply]=Kvon[ply];K2nach[ply]=Knach[ply];
           Kvon[ply]=legals[i];Knach[ply]=legalz[i];
           History[legals[i]][legalz[i]+legals[i]]+=dist;} 
       dran*=WECHSEL;return (w);}
       if (w>alpha) {alpha=w;}}
    
  }
  dran*=WECHSEL;
  return maximum;  
}

#if ATOMICDIS
void displayexplode(char *ausgabe)
{  if (kllz<12 || kllz==13 || kllz==15 || kllz==17 || kllz==19)
   { int f,i;
     printf("%d. ... %s\n",(numhalbz+1)/2,ausgabe);fflush(stdout);
     printf("%d. ... %s\n",(numhalbz+1)/2,ausgabe);fflush(stdout);
    for (i=1;i<9;i++)
    { f= Board[ezug+stern[i-1]];
      if (f!=RAND && abs(f)!=WP)
    { ausgabe[2]=((ezug+stern[i-1])%10)+96;
      ausgabe[3]=((ezug+stern[i-1])/10)+47; }
     printf("%d. ... %s\n",(numhalbz+1)/2,ausgabe);fflush(stdout);
    }
    }
}
#endif

int checkatom(int s,int z,int k)
{
 int sch; numhalbz++;
 szug=s; zug=z; ezug=szug+zug;
 makemoveatom(k);
 { if (Board[koenig[dran+1]]==LEER) sch=1; else sch=0;
   Schach[numhalbz]=sch;
 }
 takebackatom();
 numhalbz--; return sch;
}

int atomeval(void)
{ return(dran*(material+zugspec)); }
