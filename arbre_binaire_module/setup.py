# coding=UTF-8

# =============================================================================
# titre           :setup.py
# description     :Script de compilation du module 'arbre_binaire_externe'
# author          :Nicolas Bisson
# date            :2015/12/07
# version         :1.0
# usage           :python setup.py build
# notes           :
# license         :MIT
# python_version  :3.4.0
# =============================================================================

from distutils.core import setup, Extension

arbre_binaire_externe = Extension('arbre_binaire_externe',
                    include_dirs = ['../arbre_binaire/'],
                    libraries = ['arbre_binaire'],
                    library_dirs = ['../arbre_binaire/bin/Release/'],
                    sources = ['arbre_binaire_module.c'])

setup (name = 'arbre_binaire_externe',
       version = '1.0',
       description = "Un arbre binaire est une liste hiérarchique de données qui ont au plus 2 'enfants'.",
       ext_modules = [arbre_binaire_externe])
