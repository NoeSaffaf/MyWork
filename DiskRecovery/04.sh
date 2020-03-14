# !/bin/sh

# Cette fonction reprend la fonction prededante mais affiche le nombre d'octet pour chaque fichier a reconstituer
# (Seul 6 fichiers sont teste pour l'exemple ici)

for i in $(seq 043560 1 043565 )
do
	echo "Pour le fichier $i"
	a=$(cat recovery.dat | grep "$i *") 
	echo $a | cut -d " " -f2
done

