##########################################################################
# Script de compilation du programme de test de la librairie Arbre Binaire
# Auteur: Nicolas Bisson
# Date: 2015-11-28
# License: MIT
##########################################################################

UNAME=$(shell uname)

SUFIX=.exe
ifeq ($(UNAME), Linux)
SUFIX=
endif
ifeq ($(UNAME), Solaris)
SUFIX=
endif
ifeq ($(UNAME), Darwin)
SUFIX=
endif

all:debug release

obj/Debug/main.o:main.c ../arbre_binaire/arbre_binaire.h
	mkdir -p obj/Debug
	gcc -Wall -g -I../arbre_binaire -c main.c -o $@

bin/Debug/arbre_binaire_test$(SUFIX):obj/Debug/main.o ../arbre_binaire/bin/Debug/libarbre_binaire.a
	mkdir -p bin/Debug/
	gcc  -o $@ $^

obj/Release/main.o:main.c ../arbre_binaire/arbre_binaire.h
	mkdir -p obj/Release
	gcc -Wall -O2 -I../arbre_binaire  -c main.c -o $@

bin/Release/arbre_binaire_test$(SUFIX):obj/Release/main.o ../arbre_binaire/bin/Release/libarbre_binaire.a
	mkdir -p bin/Release/
	gcc -s -o $@ $^

debug: bin/Debug/arbre_binaire_test$(SUFIX)

release: bin/Release/arbre_binaire_test$(SUFIX)

clean:
	rm -rf obj
	rm -rf bin

.PHONY: all debug release clean
