# !/bin/sh

# Cette fonction fait une boucle des numeros des fichier attribue et affiche les blocs d'octets qui peuvent servir à la reconstruction

# (Seul 6 fichiers sont teste pour l'exemple ici)

for i in $(seq 043560 1 043565 )
do
	echo "Pour le fichier $i"
	cat recovery.dat | grep "$i *"
done

