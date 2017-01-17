/*

    Copyright (c) 2015 Nicolas Bisson

    L'autorisation est accordée, gracieusement, à toute personne acquérant une
    copie de cette bibliothèque et des fichiers de documentation associés
    (la "Bibliothèque"), de commercialiser la Bibliothèque sans restriction,
    notamment les droits d'utiliser, de copier, de modifier, de fusionner, de
    publier, de distribuer, de sous-licencier et / ou de vendre des copies de
    la Bibliothèque, ainsi que d'autoriser les personnes auxquelles la
    Bibliothèque est fournie à le faire, sous réserve des conditions suivantes:

    La déclaration de copyright ci-dessus et la présente autorisation doivent
    être incluses dans toutes copies ou parties substantielles de la
    Bibliothèque.

    LA BIBLIOTHÈQUE EST FOURNIE "TELLE QUELLE", SANS GARANTIE D'AUCUNE SORTE,
    EXPLICITE OU IMPLICITE, NOTAMMENT SANS GARANTIE DE QUALITÉ MARCHANDE,
    D’ADÉQUATION À UN USAGE PARTICULIER ET D'ABSENCE DE CONTREFAÇON. EN AUCUN
    CAS, LES AUTEURS OU TITULAIRES DU DROIT D'AUTEUR NE SERONT RESPONSABLES DE
    TOUT DOMMAGE, RÉCLAMATION OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS LE
    CADRE D'UN CONTRAT, D'UN DÉLIT OU AUTRE, EN PROVENANCE DE, CONSÉCUTIF À OU
    EN RELATION AVEC LA BIBLIOTHÈQUE OU SON UTILISATION, OU AVEC D'AUTRES
    ÉLÉMENTS DE LA BIBLIOTHÈQUE.

*/

/**
 *  \file main.c
 *
 *  Effectue les tests de l'arbre binaire.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "arbre_binaire.h"

/**
 * \brief Test de l'arbre binaire.
 */
int main()
{
    arbre_binaire* arbre1;
    arbre_binaire* arbre2;
    arbre1 = creer_arbre_binaire(1);

    if (arbre1)
    {
        printf("Arbre binaire creee.\n");
        printf("Valeur de la racine: %d \n", element_arbre_binaire(arbre1));
        modifier_element_arbre_binaire(arbre1, 2);
        if (element_arbre_binaire(arbre1) == 2) {
            printf("Modification de la valeur reussi.\n");
        } else {
            printf("Modification de la valeur non reussi.\n");
        }
        creer_premier_enfant_arbre_binaire(arbre1, 3);
        creer_second_enfant_arbre_binaire(arbre1, 4);
        arbre_binaire* premier_enfant = premier_enfant_arbre_binaire(arbre1);
        creer_premier_enfant_arbre_binaire(premier_enfant, 5);
        if (a_erreur_arbre_binaire(arbre1)) {
            printf("Ne peut creer un enfant: %s\n", erreur_arbre_binaire(arbre1));
        }
        sauvegarder_arbre_binaire(arbre1, "arbre_binaire_test.bin");
        detruire_arbre_binaire(arbre1);
        arbre2 = charger_arbre_binaire("arbre_binaire_test.bin");
        sauvegarder_arbre_binaire(arbre2, "arbrebinaire2.bin");
        if (arbre2) {
             if (a_erreur_arbre_binaire(arbre2)) {
                printf("Ne peut charger le fichier 'arbre_binaire_test.bin':\
                            %s\n", erreur_arbre_binaire(arbre2));
            } else {
                if (a_erreur_arbre_binaire(arbre2)) {
                    printf("Erreur lors de la sauvegarde de la liste: %s\n",
                                                erreur_arbre_binaire(arbre2));
                }
                if (contient_element_arbre_binaire(arbre2, 4) == true) {
                    printf("L'element '4' est dans l'arbre.\n");
                } else {
                    printf("Une erreur s'est produite\n");
                }
                if (hauteur_arbre_binaire(arbre2) == 3) {
                    printf("L'arbre a 3 etages.\n");
                } else {
                    printf("Une erreur s'est produite\n");
                }
                if (nombre_feuilles_arbre_binaire(arbre2) == 2) {
                    printf("Il y a 2 feuilles.\n");
                } else {
                    printf("Une erreur s'est produite\n");
                }
                if (nombre_elements_arbre_binaire(arbre2) == 4) {
                    printf("Il y a 4 elements.\n");
                } else {
                    printf("Une erreur s'est produite\n");
                }
                retirer_premier_enfant_arbre_binaire(arbre2);
                retirer_second_enfant_arbre_binaire(arbre2);
                if (nombre_elements_arbre_binaire(arbre2) == 1) {
                    printf("Les elements ont ete supprimes.\n");
                } else {
                    printf("Une erreur s'est produite\n");
                }
            }
            detruire_arbre_binaire(arbre2);
        } else {
            printf("Une erreur s'est produite\n");
        }
    } else {
        printf("Une erreur s'est produite\n");
    }
    printf("Tous les tests ont ete executes.\n");

    return 0;
}
