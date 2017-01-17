# coding=UTF-8

# =============================================================================
# titre           :arbre_binaire_externe.py
# description     :Tests pour le module arbre_binaire_externe
# author          :Nicolas Bisson
# date            :2015/012/10
# version         :1.0
# usage           :python arbre_binaire_externe.py
# notes           :
# license         :MIT
# python_version  :3.4.0
# =============================================================================

import arbre_binaire_externe

arbre1 = arbre_binaire_externe.creer(1)
arbre_binaire_externe.creer_premier_enfant(arbre1, 3)
arbre_binaire_externe.creer_second_enfant(arbre1, 4)
arbre_binaire_externe.sauvegarder(arbre1, "arbre_binaire_test.bin")
arbre_binaire_externe.detruire(arbre1)
arbre2 = arbre_binaire_externe.charger("arbre_binaire_test.bin")

try:
	arbre_binaire_externe.modifier_element(arbre2, 2)
except Exception as message:
	print("Ne peut modifier la valeur de la racine: " + str(message) + "\n")

if(arbre_binaire_externe.hauteur(arbre2) == 2):
	print("La hauteur de l'arbre est: 2 \n")
else:
	print("Une erreur est survenue \n")

if(arbre_binaire_externe.nombre_elements(arbre2) == 3):
	print("Le nombre d'element est: 3 \n")
else:
	print("Une erreur est survenue \n")
	
if(arbre_binaire_externe.nombre_feuilles(arbre2) == 2):
	print("Le nombre de feuilles est: 2 \n")
else:
	print("Une erreur est survenue \n")

if(arbre_binaire_externe(arbre2) == 2):
	print("La valeur de la racine est: 2 \n")
else:
	print("Une erreur est survenue \n")
	
if(arbre_binaire_externe.contient_element(arbre2, 4) == true):
	print("L'element '4' est present dans l'arbre \n")
else:
	print("Une erreur est survenue \n")
	
premier_enfant = arbre_binaire_externe.premier_enfant(arbre2)
arbre_binaire_externe.creer_premier_enfant(premier_enfant, 5)

if(arbre_binaire_externe.hauteur(arbre2) == 3):
	print("La hauteur de l'arbre est: 3")
else:
	print("Une erreur est survenue")

arbre_binaire_externe.retirer_premier_enfant(premier_enfant)

if(arbre_binaire_externe.hauteur(arbre2) == 2):
	print("La hauteur de l'arbre est: 2")
else:
	print("Une erreur est survenue")

	
	
	

	
	