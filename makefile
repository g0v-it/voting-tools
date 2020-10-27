#===============================================================================
#	Definitions of global targets
#===============================================================================

all:	MakeCommon MakeRandom MakeMajority

clean:	CleanCommon CleanRandom CleanMajority

documentation:
	cd Documentation; rm -f -r html/* latex/*; \
	doxygen Doxyfile > DoxygenErrors

MakeCommon:
	cd Common; make all

MakeRandom:
	cd Random; make all

MakeMajority:
	cd Majority; make all

CleanCommon:
	cd Common; make clean

CleanRandom:
	cd Random; make clean

CleanMajority:
	cd Majority; make clean
