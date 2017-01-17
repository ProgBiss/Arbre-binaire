########################################################
# Script de compilation de la librairie de Arbre Binaire
# Auteur: Nicolas Bisson
# Date: 2015-12-28
# License: MIT
########################################################

all:debug release

obj/Debug/arbre_binaire.o:arbre_binaire.h arbre_binaire.c
	mkdir -p obj/Debug
	gcc -Wall -g -fpic -c arbre_binaire.c -o $@

bin/Debug/libarbre_binaire.a:obj/Debug/arbre_binaire.o
	rm -f $@
	mkdir -p bin/Debug/
	ar -r -s $@ $^

bin/Debug/libarbre_binaire.so:obj/Debug/arbre_binaire.o
	mkdir -p bin/Debug/
	gcc -shared $^ -o $@

obj/Release/arbre_binaire.o:arbre_binaire.h arbre_binaire.c
	mkdir -p obj/Release
	gcc -O2 -Wall -fpic  -c arbre_binaire.c -o $@

bin/Release/libarbre_binaire.a:obj/Release/arbre_binaire.o
	rm -f $@
	mkdir -p bin/Release/
	ar -r -s $@ $^

bin/Release/libarbre_binaire.so:obj/Release/arbre_binaire.o
	mkdir -p bin/Release/
	gcc -shared $^ -o $@

debug_static:bin/Debug/libarbre_binaire.a

debug_dynamic:bin/Debug/libarbre_binaire.so

debug:debug_static debug_dynamic

release_static:bin/Release/libarbre_binaire.a

release_dynamic:bin/Release/libarbre_binaire.so

release:release_static release_dynamic

static: debug_static release_static

dynamic: debug_dynamic release_dynamic

clean:
	rm -rf obj
	rm -rf bin

.PHONY: all debug_static debug_dynamic debug release_static release_dynamic release static dynamic clean
