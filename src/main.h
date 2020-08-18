#define ZUGMAX 30 	/* max Searchdepth */
#define MAXLIGHT 4 	/* max Searchdepth for lightning */
#define NODEC 5000      /* Check time all N nodes */
#define TIMEBUFFER 700  /* N/100 s less time to avoid flagging. */
#define DEFAULTIME 200  /* w/o interface: Move every N/100 sec. */ 
#define NMATCH 60       /* Supposed Number of Halfmoves of the match */
#define NEND 12         /* Minimum of Number of Halfmoves still needed */
#define DEEPER 3        /* if 1/N of time used, don't search deeper*/
#define MOBIL 2         /* mobility bonus */
#define MOBILS 20       /* mobility bonus for Suicide */
#define OPENBIB 1 	/* use opening bib */
#define ZUFALL 25 	/* randomgenerator, 0 no */
#define ZUFEND 8 	/* n moves randomgenerator after opening */
#define DOPPEL 30 	/* Don't have double pawns */
#define ISOLANI 30      /* Don't have isolated pawn */
#define PAWNS 10 	/* Pawnthreat */
#define PT6 50          /* Pawnthreat to 6. row */
#define PT7 140         /* Pawnthreat to 7. row */
#define ROCH 20 	/* castle bonus */
#define ROOKF 25        /* Rook free line bonus */
#define NDAM 20 	/* Queensknight develop bonus */
#define NKON 20         /* Kingsknight develop bonus */
#define BDAM 20 	/* Queensbishop develop bonus */
#define BKON 20 	/* Kingsbishop develop bonus */
#define PDAM 40 	/* Queenspawn develop bonus */
#define PKON 50 	/* Kingspawn develop bonus */
#define CPWN 40 	/* C-Pawn develop bonus */
#define DAM 30 		/* Don't move Queen in the beginning */
#define KNG 40 		/* Don't move King in the beginning */
#define KSAV 30 	/* Save King, no open lines ! */
#define CHECKIT 0       /* check oponents moves  */
#define STARTDEPTH 1    /* start the iterative search at Depth N */
#define WIND 90         /* Alpha Beta Window */
#define DRAW -50        /* Value for Drawn position */
#define DRAWS -500      /* Value for Drawn position in Suicide*/
#define DRAWL -5000     /* Value for Drawn position in Losers*/
#define NUMOPENB 1500   /* max openings black  */
#define NUMOPENW 1500   /* max openings white  */
#define ROCHEDIT 1      /* 0 to allow castle after editing */ 
#define ONEDEBUG 1      /* 1 when dont eval with 1 legal Move (0 if yes) */
#define STELL 1         /* 1 to eval position */
#define XDEB 1 		/* 1 if you use Xboard or any interface */
#define RESIGN 0        /* 1 if you want it to resign */
#define ABSMATT 900     /* Endgame with material less than N */
#define WP  100         /* Here the values of the Figures */
#define WR  500
#define WB  320
#define WN  300
#define WQ  970
#define WK  999
#define BK -WK
#define BQ -WQ
#define BN -WN
#define BB -WB
#define BR -WR
#define BP -WP
#define ATOMICDIS 0     /* 1 if you want to play Atomic with xboard */
#define SWK  90         /* Value for Suicide Chess */
#define SWQ 130
#define SWN 190
#define SWB 150
#define SWR 100
#define SWP 200
#define SBK -SWK
#define SBQ -SWQ
#define SBN -SWN
#define SBB -SWB
#define SBR -SWR
#define SBP -SWP
#define LWK 999          /* Value for Losers Chess */
#define LWQ 80
#define LWN 150
#define LWB 90
#define LWR 70
#define LWP 700
#define LBK -LWK
#define LBQ -LWQ
#define LBN -LWN
#define LBB -LWB
#define LBR -LWR
#define LBP -LWP

#define SUICWEIT 7      /* deeper for Suicide */
#define LOSERSWEIT 3    /* deeper for Losers */
#define ATOMWEIT 4      /* deeper for Atomic */
#define OPS 1           /* Opening for Suicide */
#define OPL 0           /* Opening for Losers */
#define OPA 1           /* Opening for Atomic */
#define OPJ 0           /* Opening for Janus */
#define TYPEN 0         /* Normal Chess  */
#define TYPES 1         /* Suicide Chess */
#define TYPEL 2         /* Losers Chess  */
#define TYPEA 3         /* Atomic Chess  */
#define TYPEDEF TYPEN   /* Default Chess Type */

                        /* EXTRA PAR FOR ICC LOSERS CHESS */
#define BPIEC 4000      /* Hold pieces before the pawns go */
#define BLOCKED 3000    /* NO blocked pawn */
#define LISOLANI 3000   /* negativ Isolani in Losers */
#define LDOPPEL 50      /* negativ Doublep in Losers */
#define LPT7 400        /* Pawnthreat to 7.rank in Losers */
#define LPT6 220        /* Pawnthreat to 6.rank in Losers */

                        /* GENERAL CONSTANTS */
#define FP 0  
#define FN 1
#define FB 2
#define FR 3
#define FQ 4
#define FK 5
#define LEER 0         
#define RAND 111       
#define BDIM 120
#define BEND 99
#define BANF 21
#define WECHSEL (-1)
#define MAXHALF 500
#define SCHLECHT -30000
#define MATT 30000
#define GUT 30000
#define MAXTIEF 80
#define MAXMGL 160
#define COLOR -1 	/* 1 comp white, -1 comp black */

#define HAUPT0 /* Hier debugging tools switch 0<->1 */
#define HAUPT1 if (showpv) { printf("%2d.%6d %5d %2d         ",zugtiefe,w,nm,Htief[0]);for (j=0;j<Htief[0];j++) {if (Hvon[0][j]!=0) printf("%c%c%c%c  ",Hvon[0][j]%10+96,Hvon[0][j]/10+47,(Hvon[0][j]+Hnach[0][j])%10+96,(Hvon[0][j]+Hnach[0][j])/10+47);} printf("\n");fflush(stdout); }

#define SHOWB1 /* */
#define SHOWB0 if (zugtiefe==4) printf(" ZUR ZEIT ZUG  %d (%d): %c%c%c%c-%d mit Wert %d und Zugspec %d\n",j,i,legals[i]%10+96,legals[i]/10+47,(legals[i]+legalz[i])%10+96,(legals[i]+legalz[i])/10+47,kil[i],w,zugspec);

#define SHOWA1 /* */
#define SHOWA0 i=bzug;printf("\nTiefe %d:Nr.%d :%c%c%c%c-%d (%d)\n",zugtiefe,bzug,legals[i]%10+96,legals[i]/10+47,(legals[i]+legalz[i])%10+96,(legals[i]+legalz[i])/10+47,kil[i],maximum);

#define SHOWC1 /* */
#define SHOWC0  if (zugtiefe==4 && ply==1) {printf("   ---- >  ZUR ZEIT ZUG  %d: %c%c%c%c-%d mit Wert %d \n",i,legals[i]%10+96,legals[i]/10+47,(legals[i]+legalz[i])%10+96,(legals[i]+legalz[i])/10+47,kil[i],w);} 

#include <stdio.h>   
#include <stdlib.h>
#include <signal.h>

#ifdef UNIX
#include <sys/time.h>
struct timeval tv;
#else
#include <sys\timeb.h>
struct timeb tv;
#endif

long int stim=0;
long int start=0;
long int ende=0;
struct timeval tv;
char wh[30]="\n";
int type=TYPEDEF;
int maxt=ZUGMAX;
int lzz=0;
int CRBOOK=0;
int timeformove=DEFAULTIME;
int restnode=NODEC;
int pawnline[10][3];
int pawnrank[10][3];
int hszug,hzug,hk,kib=1;
int NUMOPEN=NUMOPENB;
int CHECK=CHECKIT;
int showpv=0;
int resign=RESIGN;
char whitebook[4][11]={"white.bin","whites.bin","whitel.bin","whitea.bin"};
char blackbook[4][11]={"black.bin","blacks.bin","blackl.bin","blacka.bin"};
int compfarbe=COLOR,maxtiefe,rep=0,/*force=0,*/ruhe,wold=0,Skill,debug=0;
int permbrain=0,Sdepth=1,Swert,Snach[MAXTIEF],Svon[MAXTIEF];
int dran=1,zug,szug,ezug,kllz,nm,NMAX=300000,TMAX,EDFLAG=0,xboard=XDEB;
int zugtiefe,numhalbz=0,opening=OPENBIB,ner,otim=0,ratdiff=0,material=0;
int ply=0,endtiefe=0,schch,schch2,altmat,abbruch,balt,walt,prompt=1;
int endspiel=0,pawnstorm=PAWNS,oppos,zugspec,drr=0,dr50=0,smat=0;
int Board[BDIM];int StartZug[MAXHALF],SD[MAXHALF],ZD[MAXHALF];
signed char Os[61][NUMOPENW],Oz[61][NUMOPENW],Of[NUMOPENW];
int EndZug[MAXHALF],Schach[MAXHALF],reph1[MAXHALF],reph2[MAXHALF];
int SchlZug[MAXHALF][10],History[BDIM][BDIM];
int KillFlag[MAXHALF],EnPassant[MAXHALF];
int K2von[MAXTIEF],K2nach[MAXTIEF],K3von[MAXTIEF],K3nach[MAXTIEF];
int Rochade[MAXHALF],Kvon[MAXTIEF],Knach[MAXTIEF];
int Hvon[MAXTIEF][MAXTIEF],Hnach[MAXTIEF][MAXTIEF],Htief[MAXTIEF];
int rochdir[4]={-1,1,-1,1},koenig[3]={95,0,25},rochiert[3]={0,0,0};
int rochturm[4]={91,98,21,28},rochkoen[4]={95,95,25,25};
int rochchk1[4]={91,95,21,25},rochchk3[4]={93,95,23,25};
int rochchk2[4]={95,98,25,28},rochchk4[4]={95,97,25,27};
int piecec[3]={16,0,16};
int pawnc[3]={8,0,8};
const int OPENB[5]={OPENBIB,OPS,OPL,OPA,OPJ};
const int sicher[18]={9,10,11,19,20,21,29,30,31};
const int ent1[3]={92,0,22};
const int ent2[3]={97,0,27};
const int ent3[3]={93,0,23};
const int ent4[3]={96,0,24};
const int ent5[3]={84,0,34};
const int ent6[3]={85,0,35};
const int ent7[3]={83,0,33};
const int lrochfeld[4][5]={{LBR,LEER,LEER,LEER,LBK},
{LBK,LEER,LEER,LBR,0},{LWR,LEER,LEER,LEER,LWK},{LWK,LEER,LEER,LWR,0}};
const int rochfeld[4][5]={{BR,LEER,LEER,LEER,BK},
{BK,LEER,LEER,BR,0},{WR,LEER,LEER,LEER,WK},{WK,LEER,LEER,WR,0}};
const int Figur[6]={WP,WN,WB,WR,WQ,WK};
const int figur[6]={BP,BN,BB,BR,BQ,BK};
const int zweitereihe[3]={8,0,3};
const int fuenftereihe[3]={5,0,6};
const int siebtereihe[3]={3,0,8};
const int stern[8]={-1,9,10,11,1,-9,-10,-11};
const int sternfig[8]={BR,BB,BR,BB,BR,BB,BR,BB};
const int sstern[8]={SBR,SBB,SBR,SBB,SBR,SBB,SBR,SBB};
const int lstern[8]={LBR,LBB,LBR,LBB,LBR,LBB,LBR,LBB};
const char name[6]={'P','N','B','R','Q','K'};
const int ValFig[4][6]={{WP,WN,WB,WR,WQ,WK},
{SWP,SWN,SWB,SWR,SWQ,SWK},{LWP,LWN,LWB,LWR,LWQ,LWK},{WP,WN,WB,WR,WQ,WK}};
const int bewfla[6]={1,1,8,8,8,1};
const int bewanz[6]={0,8,4,4,8,8};
const int beweg[48]={
9,11,10,20,0,0,0,0,
19,21,12,-8,-19,-21,-12,8,
-9,-11,9,11,0,0,0,0,
-1,10,1,-10,0,0,0,0,
-9,-11,9,11,-1,10,1,-10,
-9,-11,9,11,-1,10,1,-10 };
const int GBoard[BDIM] =  {
RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,
RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,
RAND,WR ,WN ,WB ,WQ ,WK ,WB ,WN ,WR , RAND,
RAND,WP ,WP ,WP ,WP ,WP ,WP ,WP ,WP , RAND,
RAND,LEER,LEER,LEER,LEER,LEER,LEER,LEER,LEER,RAND,
RAND,LEER,LEER,LEER,LEER,LEER,LEER,LEER,LEER,RAND,
RAND,LEER,LEER,LEER,LEER,LEER,LEER,LEER,LEER,RAND,
RAND,LEER,LEER,LEER,LEER,LEER,LEER,LEER,LEER,RAND,
RAND,BP ,BP ,BP ,BP ,BP ,BP ,BP ,BP , RAND,
RAND,BR ,BN ,BB ,BQ ,BK ,BB ,BN ,BR , RAND,
RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,
RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND,RAND};
const int Zentrum[BDIM] = {
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
0 ,0 ,5 ,10,15,15,10,5 ,0 ,0,
0 ,5 ,20,25,30,30,25,20,5 ,0,
0 ,10,25,30,35,35,30,25,10,0,
0 ,15,30,35,40,40,35,30,15,0,
0 ,15,30,35,40,40,35,30,15,0,
0 ,10,35,30,35,35,30,25,10,0,
0 ,5 ,20,25,30,30,25,20,5 ,0,
0 ,0 ,5 ,10,15,15,10,5 ,0 ,0,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};

void initchess(int argc, char **argv);
int eingzug(int argc, char **argv);
void ausgzug(void);
void makemove(int kilflag);
void takeback(void);
void makemovesuic(int kilflag);
void makemoveloser(int kilflag);
void takebacksuic(void);
void takebackloser(void);
void makemoveatom(int kilflag);
void takebackatom(void);
void think(void);
void thinksuic(void);
void thinkloser(void);
void thinkatom(void);
void printboard(void);
void matt(int);
void controltime(int t);
void ladebuch(void);
void heintrag(int k);
void buch(void);
void editboard(void);
void clearboard(void);
void createbook(int d);
void KopPV(int a,int s,int z);
void KopPVsuic(int a,int s,int z);
void TermSearch(int sig);
void Die(int sig);
void displayexplode(char *ausgabe);
int suicmat(int s);
int losermat(int s);
int legalezuege(int *ls,int *lz,int *kil,int schach);
int schlagzuege(int *ls,int *lz,int *kil,int schach);
int captureatom(int *ls,int *lz,int *kil,int schach);
int gensuic(int *ls,int *lz,int *kil,int schach);
int genloser(int *ls,int *lz,int *kil,int schach);
int genatom(int *ls,int *lz,int *kil,int schach);
int zugbonus(int s,int e,int k,int d,int p);
int eval(int anz,int anz2);
int atomeval(void);
int suiceval(int anz,int anz2);
int losereval(int anz,int anz2);
int search(int alpha,int beta,int dist,int anz,int anz2,int kfl);
int searchsuic(int alpha,int beta,int dist,int anz,int anz2,int kfl);
int searchloser(int alpha,int beta,int dist,int anz,int anz2,int kfl);
int searchatom(int alpha,int beta,int dist,int anz,int anz2,int kfl);
int quiesce(int alpha,int beta,int anz,int anz2,int kfl);
int quiesceatom(int alpha,int beta,int anz,int anz2,int kfl);
int attacked(int feld);
int atomattacked(int feld);
int sattacked(int feld);
int istschach(int s,int z,int k);
int checkatom(int s,int z,int k);
int sistschach(int s,int z,int k);
