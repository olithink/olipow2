OliPow, Version 2.2.2, (c) 1997 Oliver Brausch, Oliver.Brausch@uni-bayreuth.de
        C (Ansi) 

Options: 
         -p       : Show Principle Variant
         -t sec   : Default time seconds/move
         -c #     : 1 for create book, 2 for extended creation
         -d       : Display ASCII Board
         -x       : Check for legality
         -n       : Don't use opening book
         -r       : Let Olipow resign automatically
         -a       : Atomic chess
         -s       : Suicide chess
         -l       : Losers chess

Files: readme.txt :
       main.c     : ansi-C source code
       main.h     : constants & external variables
       suic.c     : Suicide Extension
       atom.c     : Atomic Extension
       Makefile   : compilerrules
       white.bin  : openbib for white (1200) /* Thanks to Leonid */
       black.bin  : openbib for black (800)
       whites.bin : openbib for suicide white (21)
       blacks.bin : openbib for suicide blacks (9)
       whitel.bin : openbib for losers white (0)
       blackl.bin : openbib for losers blacks (0)
       whitea.bin : openbib for atomic white (0)
       blacka.bin : openbib for atomic blacks (0)

OliPow is a mostly 'Bruce Force' Chess Programm using AlphaBetaSearch.
The eval is kind of simple, the programm is optimized on speed.
All types of chess (standard, suicide, losers and atomic) were
originally in one engine/file, but are now separated in favor
to speed and transparancy of the code.

Strength:  Comparable to a FIDE ELO of about 2000 on a Pentium233.
           In Suicide Chess strong.

You can compile it with every standard C-Compiler.
# gtar -xvzf olipow.tgz (or just tar on Linux)
# make

You can find compiled version for DOS/Windows and Linux, as well
a complex compiled ICS Package for Linux on

http://btp2x5.phy.uni-bayreuth.de/anabel/

Timecontrol: OliPow control time each 'NODEC' nodes. You don't have to adapt
it to fast or slow machines. If you want to let it play faster, then you can
or increase NMATCH and NEND or decrease ZUGMAX (max. Searchdepth, e.g. 4)  

Option creatbook (-c) to create an own book. Recommended only for matches
against Computer or players, who don't commit blunders.
By "-c 1", it will update white?.bin and create whitec.book
in case of a win. If it is set to 2, it will also upate the opposites
books in case of lose. Be careful, the *.bin will be changed ! 
If you use it on an ICS server, the ratings will be considered.

Interface: Xboard 3.6.1 (or Autochess or RoboFICS 1.4b)
           xboard -fcp olipow -xreuse
           xboard -fcp "olipow [options]" -xreuse

           Important: Configure Xboard with the options:
	   --enable-zippy (zippy for ICS)

           to run on ICS :
           xboard -zp -fcp olipow -xreuse -getMoveList false -ics.....
	   
Syntax in ASCII Mode: 
         Moves like e.g. d2d4, d4e5, b1c3
         Castle e1g1, etc.
         un for undo 1 halfmoves
         go for make AI move;

   kilflag: P: 23, Px: 0      Force Moves: all with kilflag<22
            N: 24, Nx: 1
            B: 25, Bx: 2
            R: 26, Rx: 3
            Q: 27: Qx: 4
            K: 28: Kx: 5
            P enpassant: 11
            P promotes to N: 12 (=10+2) capture: 13 (=10+3)
            P promotes to B: 14 (=10+4) c:15
            P promotes to R: 16 (=10+6) c:17
            P promotes to Q: 18 (=10+8) c:19
            P promotes to K: 20 (=10+10) c:21
            big black castle: 30, small black castle: 31
            big white castle: 32, small white castle: 33 */

