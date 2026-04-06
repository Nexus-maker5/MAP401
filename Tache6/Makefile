#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2024/2025
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond à toutes les dépendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .
# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_geom2d test_simplification


#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

image.o : image.c image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

# Ajout des dépendances vers liste.h et geom2d.h car inclus dans contour.c
contour.o : contour.c contour.h image.h liste.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

# Nouveau module nécessaire pour la Tâche 3
liste.o : liste.c liste.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module liste"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

# Nouveau module nécessaire pour les calculs de points
geom2d.o : geom2d.c geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_geom2d.o : test_geom2d.c geom2d.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

# simplification des contours
simplification.o : simplification.c simplification.h geom2d.h contour.h liste.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_simplification.o : test_simplification.c simplification.h geom2d.h contour.h liste.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_simplification"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


########################################################
# regles explicites de creation des executables

# L'exécutable doit lier TOUS les objets utilisés
test_geom2d : test_geom2d.o geom2d.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_simplification : test_simplification.o simplification.o geom2d.o contour.o liste.o image.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
	
# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) *.o