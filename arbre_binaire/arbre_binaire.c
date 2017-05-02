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
 *  \file arbre_binaire.h
 *
 *  Fichier d'entête contenant la structure de données 'arbre_binaire'.
 *  Un Arbre binaire est une liste hiérarchique de données qui ont
 *  au plus 2 "enfants".
 *
 *  Certaines fonctions sont inspirées du site web :
 *  http://rperrot.developpez.com/articles/algo/structures/arbres/#LV-A
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre_binaire.h"

/**
 *  \brief Alloue un espace mémoire pour y placer l'arbre binaire et y placer
 *         l'élément racine.
 *
 *  \param valeur : La valeur de la racine de l'arbre.
 *
 *  \return L'arbre binaire avec la valeur de la racine.
 */
arbre_binaire* creer_arbre_binaire(int valeur)
{
    struct arbre_binaire_struct * noeud;
    noeud = calloc(1, sizeof(struct arbre_binaire_struct));
    noeud -> valeur = valeur;
    noeud -> premier_fils = NULL;
    noeud -> second_fils = NULL;
    noeud -> a_erreur = false;
    noeud -> erreur = calloc(ERREUR_TAILLE, sizeof(char));

    return noeud;
}

/**
 *  \brief Lire les données de l'arbre dans le fichier.
 *
 *  \param fichier      : Le fichier dans lequel lire les données.
 *
 *  \note  L'arbre ne doit pas être NULL.
 */
void lire_fichier(arbre_binaire* arbre, FILE* fichier)
{
    int contenu[2];

    retirer_erreur_arbre_binaire(arbre);
    fread(contenu, sizeof(int), 2, fichier);
    modifier_element_arbre_binaire(arbre, contenu[0]);
    if (contenu[1] == 0) {

    } else if (contenu[1] == 1) {
        creer_premier_enfant_arbre_binaire(arbre, 0);
        lire_fichier(arbre->premier_fils, fichier);
    } else if (contenu[1] == 2) {
        creer_second_enfant_arbre_binaire(arbre, 0);
        lire_fichier(arbre->second_fils, fichier);
    } else if (contenu[1] == 3) {
        creer_premier_enfant_arbre_binaire(arbre, 0);
        lire_fichier(arbre->premier_fils, fichier);
        creer_second_enfant_arbre_binaire(arbre, 0);
        lire_fichier(arbre->second_fils, fichier);
    }
}

/**
 *  \brief Récupère les données d'un fichier pour créer un arbre binaire.
 *
 *  \param nom_fichier : Le nom du fichier qui contient les données.
 *
 *  \return Un nouvel arbre binaire créé à l'aide des données d'un fichier.
 */
arbre_binaire* charger_arbre_binaire(char *nom_fichier)
{
    FILE* fichier;
    arbre_binaire* arbre;

    arbre = creer_arbre_binaire(0);
    fichier = fopen(nom_fichier, "rb");
    lire_fichier(arbre, fichier);
    fclose(fichier);

    return arbre;
}

/**
 *  \brief Libère l'espace mémoire d'un arbre binaire.
 *
 *  \param arbre : L'arbre binaire à supprimer.
 */
void detruire_arbre_binaire(arbre_binaire* arbre)
{
    retirer_erreur_arbre_binaire(arbre);
    if (arbre->premier_fils != NULL) {
        detruire_arbre_binaire(arbre->premier_fils);
    }
    if (arbre->second_fils != NULL) {
        detruire_arbre_binaire(arbre->second_fils);
    }
    free(arbre->erreur);
    free(arbre);
}

/**
 *  \brief Écrit les données de l'arbre dans le fichier.
 *
 *  \param arbre        : L'arbre à enregistrer dans le fichier.
 *  \param fichier      : Le fichier dans lequel écrire les données.
 *
 *  \note  L'arbre ne doit pas être NULL.
 */
void ecrire_fichier(arbre_binaire* arbre, FILE* fichier)
{
    int contenu[2];
    contenu[0] = arbre->valeur;

    retirer_erreur_arbre_binaire(arbre);
    if (arbre->premier_fils == NULL && arbre->second_fils == NULL) {
        contenu[1] = 0;
    } else if (arbre->premier_fils && arbre->second_fils == NULL) {
        contenu[1] = 1;
    } else if (arbre->premier_fils == NULL && arbre->second_fils) {
        contenu[1] = 2;
    } else {
        contenu[1] = 3;
    }
    fwrite(contenu, sizeof(int), 2, fichier);
    if (arbre->premier_fils) {
        ecrire_fichier(arbre->premier_fils, fichier);
    }
    if (arbre->second_fils) {
        ecrire_fichier(arbre->second_fils, fichier);
    }
}

/**
 *  \brief Sauvegarde les données d'un arbre binaire dans un fichier.
 *
 *  \param arbre        : L'arbre à enregistrer dans le fichier.
 *  \param nom_fichier  : Le fichier dans lequel sauvergarder les données.
 *
 *  \note  L'arbre ne doit pas être NULL.
 */
void sauvegarder_arbre_binaire(arbre_binaire* arbre, char * nom_fichier)
{
    retirer_erreur_arbre_binaire(arbre);
    FILE* fichier;
    fichier = fopen(nom_fichier, "wb");
    if (fichier) {
        ecrire_fichier(arbre, fichier);
        fclose(fichier);
    } else {
        inscrire_erreur_arbre_binaire(arbre, "Il est impossible d'ecrire dans \
                                      ce fichier");
    }
}

/**
 *  \brief Indique le nombre d'éléments que contient l'arbre binaire.
 *
 *  \param arbre : L'arbre à trouver son nombre d'éléments.
 *
 *  \return Le nombre d'élément qu'il y a dans l'arbre.
 */
int nombre_elements_arbre_binaire(arbre_binaire* arbre)
{
    int nombre;
    int nombre_premier = 0;
    int nombre_second = 0;

    retirer_erreur_arbre_binaire(arbre);
    if (arbre == NULL) {
        nombre = 0;
    } else {
        if (arbre->premier_fils != NULL) {
           nombre_premier = nombre_elements_arbre_binaire(arbre->premier_fils);
        }
        if (arbre->second_fils) {
            nombre_second = nombre_elements_arbre_binaire(arbre->second_fils);
        }
        nombre = 1 + nombre_premier + nombre_second;
    }

    return nombre;
}

/**
 *  \brief Indique le nombre de feuilles que contient l'arbre binaire.
 *
 *  \param arbre : L'arbre à trouver son nombre de feuilles.
 *
 *  \return Le nombre de feuilles qu'il y a dans l'arbre.
 */
int nombre_feuilles_arbre_binaire(arbre_binaire* arbre)
{
    int feuilles;
    int feuilles_premier = 0;
    int feuilles_second = 0;

    retirer_erreur_arbre_binaire(arbre);
    if (arbre == NULL) {
        feuilles = 0;
    } else if (arbre->premier_fils == NULL && arbre->second_fils == NULL) {
        feuilles = 1;
    } else {
        if (arbre->premier_fils) {
        feuilles_premier = nombre_feuilles_arbre_binaire(arbre->premier_fils);
        }
        if (arbre->second_fils) {
            feuilles_second = nombre_feuilles_arbre_binaire(arbre->second_fils);
        }
        feuilles = feuilles_premier + feuilles_second;
    }

    return feuilles;
}

/**
 *  \brief Indique la hauteur de l'arbre binaire.
 *
 *  \param arbre : L'arbre à trouver sa hauteur.
 *
 *  \return La hauteur de l'arbre binaire.
 */
int hauteur_arbre_binaire(arbre_binaire* arbre)
{
    int hauteur;
    int hauteur_premier = 0;
    int hauteur_second = 0;

    retirer_erreur_arbre_binaire(arbre);
    if (arbre == NULL) {
        hauteur = 0;
    } else {
        if (arbre->premier_fils != NULL) {
            hauteur_premier = hauteur_arbre_binaire(arbre->premier_fils);
        }
        if (arbre->second_fils) {
            hauteur_second = hauteur_arbre_binaire(arbre->second_fils);
        }
        if (hauteur_premier >= hauteur_second) {
            hauteur = hauteur_premier + 1;
        } else {
            hauteur = hauteur_second + 1;
        }
    }

    return hauteur;
}

/**
 *  \brief Indique l'élément se trouvant à la racine de l'arbre binaire.
 *
 *  \param arbre : L'arbre dans lequel trouver l'élément de la racine.
 *
 *  \return L'élément se trouvant à la racine.
 *
 *  \note  L'arbre ne doit pas être NULL.
 */
int element_arbre_binaire(arbre_binaire* arbre)
{
    retirer_erreur_arbre_binaire(arbre);
    return arbre->valeur;
}

/**
 *  \brief Modifie la valeur de la racine de l'arbre binaire.
 *
 *  \param arbre  : L'arbre dans lequel faire la modification.
 *  \param valeur : La nouvelle valeur de la racine.
 *
 *  \note  L'arbre ne doit pas être NULL.
 */
void modifier_element_arbre_binaire(arbre_binaire* arbre, int valeur)
{
    retirer_erreur_arbre_binaire(arbre);
    arbre->valeur = valeur;
}

/**
 *  \brief Indique si un élément à la même valeur que celle entrer en argument.
 *
 *  \param arbre  : L'arbre binaire dans lequel chercher la valeur.
 *  \param valeur : La valeur à chercher dans l'arbre.
 *
 *  \return Vrai si un des éléments équivaut l'argument valeur.
 */
bool contient_element_arbre_binaire(arbre_binaire* arbre, int valeur)
{
    bool presence = false;

    retirer_erreur_arbre_binaire(arbre);
    if (arbre == NULL) {
        presence = false;
    }
    if (arbre->valeur == valeur) {
        presence = true;
    }
    if (arbre->premier_fils != NULL && presence == false) {
        presence = contient_element_arbre_binaire(arbre->premier_fils, valeur);
    }
    if (arbre->second_fils != NULL && presence == false) {
        presence = contient_element_arbre_binaire(arbre->second_fils, valeur);
    }
    return presence;
}

/**
 *  \brief Renvoie le premier sous-arbre enfant de l'arbre binaire, s'l
 *         n'y a pas d'enfant retourne NULL.
 *
 *  \param arbre : L'arbre binaire dans lequel chercher le premier sous-arbre.
 *
 *  \return Le premier sous-arbre enfant de l'arbre binaire.
 *
 *  \note  L'arbre ne doit pas être NULL.
 */
arbre_binaire* premier_enfant_arbre_binaire(arbre_binaire* arbre)
{
    retirer_erreur_arbre_binaire(arbre);
    return arbre->premier_fils;
}

/**
 *  \brief Ajoute un premier enfant à l'arbre binaire, s'il y a un premier
 *         enfant ajoute une erreur.
 *
 *  \param arbre  : L'arbre binaire dans lequel créer un premier enfant.
 *  \param valeur : La valeur à placer dans le premier enfant.
 */
void creer_premier_enfant_arbre_binaire(arbre_binaire* arbre, int valeur)
{
    retirer_erreur_arbre_binaire(arbre);
    if (arbre == NULL) {
        inscrire_erreur_arbre_binaire(arbre, "L'arbre est inexistant.");
    } else if (arbre->premier_fils == NULL) {
        arbre->premier_fils = creer_arbre_binaire(valeur);
    } else {
        inscrire_erreur_arbre_binaire(arbre, "Il y a deja un premier fils.");
    }
}

/**
 *  \brief Supprime le premier enfant d'un arbre binaire.
 *
 *  \param arbre : L'arbre duquel on supprime le premier enfant.
 *
 *  \note  L'arbre ne doit pas être NULL.
 */
void retirer_premier_enfant_arbre_binaire(arbre_binaire* arbre)
{
    retirer_erreur_arbre_binaire(arbre);
    detruire_arbre_binaire(arbre->premier_fils);
    arbre->premier_fils = NULL;
}

/**
 *  \brief Renvoie le second sous-arbre enfant de l'arbre binaire, s'l
 *         n'y a pas d'enfant retourne NULL.
 *
 *  \param arbre : L'arbre binaire dans lequel chercher le second sous-arbre.
 *
 *  \return Le second sous-arbre enfant de l'arbre binaire.
 *
 *  \note  L'arbre ne doit pas être NULL.
 */
arbre_binaire* second_enfant_arbre_binaire(arbre_binaire* arbre)
{
    retirer_erreur_arbre_binaire(arbre);
    return arbre->second_fils;
}

/**
 *  \brief Ajoute un second enfant à l'arbre binaire, s'il y a un second
 *         enfant ajoute une erreur.
 *
 *  \param arbre  : L'arbre binaire dans lequel créer un second enfant.
 *  \param valeur : La valeur à placer dans le second enfant.
 */
void creer_second_enfant_arbre_binaire(arbre_binaire* arbre, int valeur)
{
    retirer_erreur_arbre_binaire(arbre);
    if (arbre == NULL) {
        inscrire_erreur_arbre_binaire(arbre, "L'arbre est inexistant.");
    } else if (arbre->second_fils == NULL) {
        arbre->second_fils = creer_arbre_binaire(valeur);
    } else {
        inscrire_erreur_arbre_binaire(arbre, "Il y a deja un second fils.");
    }
}

/**
 *  \brief Supprime le second enfant d'un arbre binaire.
 *
 *  \param arbre : L'arbre duquel on supprime le second enfant.
 *
 *  \note  L'arbre ne doit pas être NULL.
 */
void retirer_second_enfant_arbre_binaire(arbre_binaire* arbre)
{
    retirer_erreur_arbre_binaire(arbre);
    detruire_arbre_binaire(arbre->second_fils);
    arbre->second_fils = NULL;
}

/**
 *  \brief Cherche s'il y a une erreur dans l'arbre binaire et retourne
 *         la réponse (Vrai/Faux).
 *
 *  \param arbre : l'arbre binaire à vérifier.
 *
 *  \return Vrai s'il y a erreur et Faux en cas inverse.
 */
bool a_erreur_arbre_binaire(arbre_binaire* arbre)
{
    bool contient_erreur = false;

    if (arbre->a_erreur) {
        contient_erreur = true;
    } else {
        if (arbre->premier_fils) {
            contient_erreur = a_erreur_arbre_binaire(arbre->premier_fils);
        }
        if (arbre->second_fils && contient_erreur == false) {
            contient_erreur = a_erreur_arbre_binaire(arbre->second_fils);
        }
    }
    return contient_erreur;
}

/**
 *  \brief Indique le texte de l'erreur qui est dans l'arbre binaire.
 *
 *  \param arbre : L'arbre binaire à vérifier.
 *
 *  \return Le texte de l'erreur.
 */
char* erreur_arbre_binaire(arbre_binaire* arbre)
{
    char* message_erreur;

    if (arbre->a_erreur == false) {
        message_erreur = strncpy(arbre->erreur, "", ERREUR_TAILLE);
    } else {
        if (a_erreur_arbre_binaire(arbre->premier_fils)) {
            message_erreur = erreur_arbre_binaire(arbre->premier_fils);
        }
        if (a_erreur_arbre_binaire(arbre->second_fils)) {
            message_erreur = erreur_arbre_binaire(arbre->second_fils);
        }
    }
    return message_erreur;
}

/**
 *  \brief Place le message d'erreur dans l'arbre binaire et conserve
 *         celle-ci dans la librairie. Mets "a_erreur_arbre_binaire" à Vrai.
 *
 *  \param arbre : L'arbre binaire qui a été vérifié.
 *  \param erreur : La description de l'erreur.
 */
void inscrire_erreur_arbre_binaire(arbre_binaire* arbre, const char* erreur)
{
    arbre->a_erreur = true;
    strncpy(arbre->erreur, erreur, ERREUR_TAILLE);
}

/**
 *  \brief Retire l'erreur en mettant "a_erreur_arbre_binaire" à Faux.
 *
 *  \param arbre : L'arbre binaire qui a été vérifié.
 */
void retirer_erreur_arbre_binaire(arbre_binaire* arbre)
{
    arbre->a_erreur = false;
    if (arbre->premier_fils) {
        retirer_erreur_arbre_binaire(arbre);
    }
    if (arbre->second_fils) {
        retirer_erreur_arbre_binaire(arbre);
    }
}
