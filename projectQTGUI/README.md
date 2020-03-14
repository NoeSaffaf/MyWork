
- exemples_input : contient les fichiers d'exemples avec les mots clées disponibles.
- maquette.jpeg: exemple de ce que j'attends. Vous êtes libre d'adapter.

Il faut que ce soit adaptatif. Par exemple le mot clef "Problème" peut avoir trois valeurs "Mechanical", "Phase_Field" ou "Mechanical_Linear_PolyOpti_C". 
En fonction de ça, les sous mots clefs de cette catégorie changent, et "material_properties aussi".

Une explication sur matérial properties. Prenez exemple sur "eshelby_mixed_bc". 
Quand on fait un calcul mécanique avec plusieurs phases, les propriété mécanique de chaque phases sont définies dans "material_properties". 
Ces phases sont déclarées et associées aux éléments dans "voxels.type" et "voxels.vsets_properties".
Le comportement mécaniquede chaque phase est aussi déclaré dans "behaviors".
Il faut que l'ensemble soit cohérent, et qu'on puisse ajouter autant de phases que l'on veut.
Il se peut que ce ne soit pas très clair, mais ce n'est pas grace : faites comme vous pouvez, et on ajustera après, quand je vous expliquerai ce que le code fait.
