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
 */


#ifndef ARBRE_BINAIRE_H_INCLUDED
#define ARBRE_BINAIRE_H_INCLUDED

#include <stdbool.h>

#define ERREUR_TAILLE 255

/**
 *  \brief Une liste implémenté à l'aide d'un arbre binaire.
 */
typedef struct arbre_binaire_struct arbre_binaire;

/**
 * \brief Un arbre binaire.
 */
struct arbre_binaire_struct {
    int valeur;
    struct arbre_binaire_struct * premier_fils;
    struct arbre_binaire_struct * second_fils;
    bool a_erreur;
    char* erreur;
};


/**
 *  \brief Alloue un espace mémoire pour y placer l'arbre binaire et y placer
 *         l'élément racine.
 *
 *  \param valeur : La valeur de la racine de l'arbre.
 *
 *  \return L'arbre binaire avec la valeur de la racine.
 */
arbre_binaire* creer_arbre_binaire(int valeur);

/**
 *  \brief Récupère les données d'un fichier pour créer un arbre binaire.
 *
 *  \param nom_fichier : Le nom du fichier qui contient les données.
 *
 *  \return Un nouvel arbre binaire créé à l'aide des données d'un fichier.
 */
arbre_binaire* charger_arbre_binaire(char *nom_fichier);

/**
 *  \brief Libère l'espace mémoire d'un arbre binaire.
 *
 *  \param arbre : L'arbre binaire à supprimer.
 */
void detruire_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Sauvegarde les données d'un arbre binaire dans un fichier.
 *
 *  \param arbre        : L'arbre à enregistrer dans le fichier.
 *  \param nom_fichier  : Le fichier dans lequel sauvergarder les données.
 */
void sauvegarder_arbre_binaire(arbre_binaire* arbre, char * nom_fichier);

/**
 *  \brief Indique le nombre d'éléments que contient l'arbre binaire.
 *
 *  \param arbre : L'arbre à trouver son nombre d'éléments.
 *
 *  \return Le nombre d'élément qu'il y a dans l'arbre.
 */
int nombre_elements_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Indique le nombre de feuilles que contient l'arbre binaire.
 *
 *  \param arbre : L'arbre à trouver son nombre de feuilles.
 *
 *  \return Le nombre de feuilles qu'il y a dans l'arbre.
 */
int nombre_feuilles_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Indique la hauteur de l'arbre binaire.
 *
 *  \param arbre : L'arbre à trouver sa hauteur.
 *
 *  \return La hauteur de l'arbre binaire.
 */
int hauteur_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Indique l'élément se trouvant à la racine de l'arbre binaire.
 *
 *  \param arbre : L'arbre dans lequel trouver l'élément de la racine.
 *
 *  \return L'élément se trouvant à la racine.
 */
int element_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Modifie la valeur de la racine de l'arbre binaire.
 *
 *  \param arbre  : L'arbre dans lequel faire la modification.
 *  \param valeur : La nouvelle valeur de la racine.
 */
void modifier_element_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
 *  \brief Indique si un élément à la même valeur que celle entrer en argument.
 *
 *  \param arbre  : L'arbre binaire dans lequel chercher la valeur.
 *  \param valeur : La valeur à chercher dans l'arbre.
 *
 *  \return Vrai si un des éléments équivaut l'argument valeur.
 */
bool contient_element_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
 *  \brief Renvoie le premier sous-arbre enfant de l'arbre binaire, s'l
 *         n'y a pas d'enfant retourne NULL.
 *
 *  \param arbre : L'arbre binaire dans lequel chercher le premier sous-arbre.
 *
 *  \return Le premier sous-arbre enfant de l'arbre binaire.
 */
arbre_binaire* premier_enfant_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Ajoute un premier enfant à l'arbre binaire, s'il y a un premier
 *         enfant ajoute une erreur.
 *
 *  \param arbre  : L'arbre binaire dans lequel créer un premier enfant.
 *  \param valeur : La valeur à placer dans le premier enfant.
 */
void creer_premier_enfant_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
 *  \brief Supprime le premier enfant d'un arbre binaire.
 *
 *  \param arbre : L'arbre duquel on supprime le premier enfant.
 */
void retirer_premier_enfant_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Renvoie le second sous-arbre enfant de l'arbre binaire, s'l
 *         n'y a pas d'enfant retourne NULL.
 *
 *  \param arbre : L'arbre binaire dans lequel chercher le second sous-arbre.
 *
 *  \return Le second sous-arbre enfant de l'arbre binaire.
 */
arbre_binaire* second_enfant_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Ajoute un second enfant à l'arbre binaire, s'il y a un second
 *         enfant ajoute une erreur.
 *
 *  \param arbre  : L'arbre binaire dans lequel créer un second enfant.
 *  \param valeur : La valeur à placer dans le second enfant.
 */
void creer_second_enfant_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
 *  \brief Supprime le second enfant d'un arbre binaire.
 *
 *  \param arbre : L'arbre duquel on supprime le second enfant.
 */
void retirer_second_enfant_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Cherche s'il y a une erreur dans l'arbre binaire et retourne
 *         la réponse (Vrai/Faux).
 *
 *  \param arbre : l'arbre binaire à vérifier.
 *
 *  \return Vrai s'il y a erreur et Faux en cas inverse.
 */
bool a_erreur_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Indique le texte de l'erreur qui est dans l'arbre binaire.
 *
 *  \param arbre : L'arbre binaire à vérifier.
 *
 *  \return Le texte de l'erreur.
 */
char* erreur_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Place le message d'erreur dans l'arbre binaire et conserve
 *         celle-ci dans la librairie. Mets "a_erreur_arbre_binaire" à Vrai.
 *
 *  \param arbre : L'arbre binaire qui a été vérifié.
 *  \param erreur : La description de l'erreur.
 */
void inscrire_erreur_arbre_binaire(arbre_binaire* arbre, const char* erreur);

/**
 *  \brief Retire l'erreur en mettant "a_erreur_arbre_binaire" à Faux.
 *
 *  \param arbre : L'arbre binaire qui a été vérifié.
 */
void retirer_erreur_arbre_binaire(arbre_binaire* arbre);

#endif // ARBRE_BINAIRE_H_INCLUDED

/* vi: set ts=4 sw=4 expandtab: */
