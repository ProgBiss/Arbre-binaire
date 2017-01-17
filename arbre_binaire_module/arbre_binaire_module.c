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
 *  \file arbre_binaire_module.c
 *
 *  Fichier d'implémentation du module Python permettant d'interfacer
 *  avec la librairie "arbre_binaire".
 *
 */

#include <Python.h>
#include "arbre_binaire.h"

/**
 * \brief "Wrapper" pour les erreurs du module
 */
static PyObject *arbre_binaire_erreur;

/**
 * \brief "Wrapper" pour la fonction 'creer_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'adresse de l'arbre créé
 */
static PyObject *arbre_binaire_creer(PyObject *sefl, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    int valeur;
    if (!PyArg_ParseTuple(args, "i", &valeur)) {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        arbre = creer_arbre_binaire(valeur);
        if (arbre) {
            resultat = Py_BuildValue("i", arbre);
        } else {
            PyErr_SetString(arbre_binaire_erreur, "Ne peut pas créer d'arbre binaire");
            resultat = NULL;
        }
    }
    return resultat;
}

/**
 * \brief "Wrapper" pour la fonction 'charger_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'adresse de l'arbre binaire créé
 */
static PyObject *arbre_binaire_charger(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    char *nom_fichier;
    if (!PyArg_ParseTuple(args, "s", &nom_fichier)) {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        arbre = charger_arbre_binaire(nom_fichier);
        if (arbre) {
            if (a_erreur_arbre_binaire(arbre)) {
                contient_erreur = true;
                PyErr_SetString(arbre_binaire_erreur, erreur_arbre_binaire(arbre));
                detruire_arbre_binaire(arbre);
                resultat = NULL;
            } else {
                resultat = Py_BuildValue("i", arbre);
            }
        } else {
            PyErr_SetString(arbre_binaire_erreur, "Ne peut pas créer d'arbre binaire.");
            resultat = NULL;
        }
    }
    return resultat;
}

/**
 * \brief "Wrapper" pour la fonction 'detruire_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject *arbre_binaire_detruire(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    if (PyArg_ParseTuple(args, "i", &arbre)) {
        if (arbre) {
            detruire_arbre_binaire(arbre);
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        Py_INCREF(Py_None);
        resultat = Py_None;
    }
    return resultat;
}

/**
 * \brief "Wrapper" pour la fonction 'sauvegarder_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject *arbre_binaire_sauvegarder(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    char *nom_fichier;
    if (PyArg_ParseTuple(args, "is", &arbre, &nom_fichier)) {
        if (arbre) {
            sauvegarder_arbre_binaire(arbre, nom_fichier);
            if (a_erreur_arbre_binaire(arbre)) {
                contient_erreur = true;
                PyErr_SetString(arbre_binaire_erreur, erreur_arbre_binaire(arbre));
            }
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        Py_INCREF(Py_None);
        resultat = Py_None;
    }
    return resultat;
}

/**
 * \brief "Wrapper" pour la fonction 'nombre_elements_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'élément reçu
 */
static PyObject *arbre_binaire_nombre_elements(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    int nombre_element = 0;
    if (PyArg_ParseTuple(args, "i", &arbre)) {
        if (arbre) {
            nombre_element = nombre_elements_arbre_binaire(arbre);
            if (a_erreur_arbre_binaire(arbre)) {
                contient_erreur = true;
                PyErr_SetString(arbre_binaire_erreur, erreur_arbre_binaire(arbre));
            }
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        resultat = Py_BuildValue("i", nombre_element);
    }
    return resultat
}

/**
 * \brief "Wrapper" pour la fonction 'nombre_feuilles_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'élément reçu
 */
static PyObject *arbre_binaire_nombre_feuilles(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    int nombre_feuille = 0;
    if (PyArg_ParseTuple(args, "i", &arbre)) {
        if (arbre) {
            nombre_feuille = nombre_feuilles_arbre_binaire(arbre);
            if (a_erreur_arbre_binaire(arbre)) {
                contient_erreur = true;
                PyErr_SetString(arbre_binaire_erreur, erreur_arbre_binaire(arbre));
            }
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        resultat = Py_BuildValue("i", nombre_feuille);
    }
    return resultat
}

/**
 * \brief "Wrapper" pour la fonction 'hauteur_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'élément reçu
 */
static PyObject *arbre_binaire_hauteur(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    int hauteur = 0;
    if (PyArg_ParseTuple(args, "i", &arbre)) {
        if (arbre) {
            hauteur = hauteur_arbre_binaire(arbre);
            if (a_erreur_arbre_binaire(arbre)) {
                contient_erreur = true;
                PyErr_SetString(arbre_binaire_erreur, erreur_arbre_binaire(arbre));
            }
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        resultat = Py_BuildValue("i", hauteur);
    }
    return resultat
}

/**
 * \brief "Wrapper" pour la fonction 'element_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'élément reçu
 */
static PyObject *arbre_binaire_element(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    int element = 0;
    if (PyArg_ParseTuple(args, "i", &arbre)) {
        if (arbre) {
            element = element_arbre_binaire(arbre);
            if (a_erreur_arbre_binaire(arbre)) {
                contient_erreur = true;
                PyErr_SetString(arbre_binaire_erreur, erreur_arbre_binaire(arbre));
            }
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        resultat = Py_BuildValue("i", element);
    }
    return resultat
}

/**
 * \brief "Wrapper" pour la fonction 'modifier_element_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject *arbre_binaire_modifier_element(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    int valeur;
    if (PyArg_ParseTuple(args, "ii", &arbre, &valeur)) {
        if (arbre) {
            modifier_element_arbre_binaire(arbre, valeur);
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        Py_INCREF(Py_None);
        resultat = Py_None;
    }
    return resultat;
}

/**
 * \brief "Wrapper" pour la fonction 'contient_element_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'élément reçu
 */
static PyObject *arbre_binaire_element(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    bool contient_element;
    int valeur;
    if (PyArg_ParseTuple(args, "ii", &arbre, &valeur)) {
        if (arbre) {
            contient_element = contient_element_arbre_binaire(arbre, valeur);
            if (a_erreur_arbre_binaire(arbre)) {
                contient_erreur = true;
                PyErr_SetString(arbre_binaire_erreur, erreur_arbre_binaire(arbre));
            }
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        resultat = Py_BuildValue("i", contient_element);
    }
    return resultat
}

/**
 * \brief "Wrapper" pour la fonction 'premier_enfant_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'élément reçu
 */
static PyObject *arbre_binaire_premier_enfant(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    bool premier_enfant;
    if (PyArg_ParseTuple(args, "i", &arbre)) {
        if (arbre) {
            premier_enfant = premier_enfant_arbre_binaire(arbre);
            if (a_erreur_arbre_binaire(arbre)) {
                contient_erreur = true;
                PyErr_SetString(arbre_binaire_erreur, erreur_arbre_binaire(arbre));
            }
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        resultat = Py_BuildValue("i", premier_enfant);
    }
    if (resultat == NULL) {
        resultat = Py_None;
    }
    return resultat
}

/**
 * \brief "Wrapper" pour la fonction 'creer_premier_enfant_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject *arbre_binaire_creer_premier_enfant(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    int valeur;
    if (PyArg_ParseTuple(args, "ii", &arbre, &valeur)) {
        if (arbre) {
            creer_premier_enfant_arbre_binaire(arbre, valeur);
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        Py_INCREF(Py_None);
        resultat = Py_None;
    }
    return resultat;
}

/**
 * \brief "Wrapper" pour la fonction 'retirer_premier_enfant_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject *arbre_binaire_retirer_premier_enfant(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    if (PyArg_ParseTuple(args, "i", &arbre)) {
        if (arbre) {
            retirer_premier_enfant_arbre_binaire(arbre);
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        Py_INCREF(Py_None);
        resultat = Py_None;
    }
    return resultat;
}

/**
 * \brief "Wrapper" pour la fonction 'second_enfant_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'élément reçu
 */
static PyObject *arbre_binaire_second_enfant(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    bool second_enfant;
    if (PyArg_ParseTuple(args, "i", &arbre)) {
        if (arbre) {
            second_enfant = second_enfant_arbre_binaire(arbre);
            if (a_erreur_arbre_binaire(arbre)) {
                contient_erreur = true;
                PyErr_SetString(arbre_binaire_erreur, erreur_arbre_binaire(arbre));
            }
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        resultat = Py_BuildValue("i", second_enfant);
    }
    if (resultat == NULL) {
        resultat = Py_None;
    }
    return resultat
}

/**
 * \brief "Wrapper" pour la fonction 'creer_second_enfant_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject *arbre_binaire_creer_second_enfant(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    int valeur;
    if (PyArg_ParseTuple(args, "ii", &arbre, &valeur)) {
        if (arbre) {
            creer_second_enfant_arbre_binaire(arbre, valeur);
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        Py_INCREF(Py_None);
        resultat = Py_None;
    }
    return resultat;
}

/**
 * \brief "Wrapper" pour la fonction 'retirer_second_enfant_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject *arbre_binaire_retirer_second_enfant(PyObject *self, PyObject *args)
{
    bool contient_erreur = false;
    void* arbre = NULL;
    PyObject * resultat;
    if (PyArg_ParseTuple(args, "i", &arbre)) {
        if (arbre) {
            retirer_second_enfant_arbre_binaire(arbre);
        } else {
            contient_erreur = true;
        }
    } else {
        contient_erreur = true;
    }
    if (contient_erreur) {
        resultat = NULL;
    } else {
        Py_INCREF(Py_None);
        resultat = Py_None;
    }
    return resultat;
}

/**
 * \brief Liste toutes les fonctions du module
 */
static PyMethodDef liste_liee_methods[] = {
    {"creer",  arbre_binaire_creer, METH_VARARGS,
     "Créer un arbre binaire"},
    {"charger",  arbre_binaire_charger, METH_VARARGS,
     "Charger un arbre binaire à partir du contenue d'un fichier"},
    {"detruire",  arbre_binaire_detruire, METH_VARARGS,
     "Désalloue l'arbre binaire"},
    {"sauvegarder",  arbre_binaire_sauvegarder, METH_VARARGS,
     "Sauvegarder le contenue de l'arbre binaire dans un fichier"},
    {"nombre_elements", arbre_binaire_nombre_elements, METH_VARARGS,
     "Indique le nombre d'éléments dans l'arbre"},
    {"nombre_feuilles", arbre_binaire_nombre_feuilles, METH_VARARGS,
     "Indique le nombre de feuilles dans l'arbre"},
    {"hauteur", arbre_binaire_hauteur, METH_VARARGS,
     "Indique la hauteur de l'arbre"},
    {"element", arbre_binaire_element, METH_VARARGS,
     "Indique l'élément à la racine"},
    {"modifier_element", arbre_binaire_modifier_element, METH_VARARGS,
     "Modifie la valeur de la racine"},
    {"contient_element", arbre_binaire_contient_element, METH_VARARGS,
     "Indique si la valeur se trouve dans l'arbre"},
    {"premier_enfant", arbre_binaire_premier_enfant, METH_VARARGS,
     "Renvoie le premier_enfant"},
    {"creer_premier_enfant", arbre_binaire_creer_premier_enfant, METH_VARARGS,
     "Creer le premier_enfant"},
    {"retirer_premier_enfant", arbre_binaire_retirer_premier_enfant, METH_VARARGS,
     "Supprime le premier_enfant"},
     {"second_enfant", arbre_binaire_second_enfant, METH_VARARGS,
     "Renvoie le second_enfant"},
    {"creer_second_enfant", arbre_binaire_second_premier_enfant, METH_VARARGS,
     "Creer le second_enfant"},
    {"retirer_second_enfant", arbre_binaire_second_premier_enfant, METH_VARARGS,
     "Supprime le second_enfant"}
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

/**
 * \brief Information sur le module
 */
static struct PyModuleDef arbre_binaire_module = {
   PyModuleDef_HEAD_INIT,
   "arbre_binaire_externe",   /* nom du module */
   NULL, /* documentation du module, NULL si aucun */
   -1,       /*  Taille de l'état "per-interpreter" du module,
                ou -1 si le module ce situe en variable globale. */
   arbre_binaire_methods /* La liste des fonctions du module */
};

/**
 * \brief Initialization du module
 */
PyMODINIT_FUNC PyInit_arbre_binaire_externe(void)
{
	PyObject *l_module;
	l_module = PyModule_Create(&arbre_binaire_module); /* Créer le module */
	if (l_module) {
		/* Ajouter un gestionnaire d'exception dans le module */
		arbre_binaire_erreur = PyErr_NewException("arbre_binaire_externe.erreur", NULL, NULL);
		Py_INCREF(arbre_binaire_erreur);
		PyModule_AddObject(l_module, "erreur", arbre_binaire_erreur);
	}
    return l_module;
}
