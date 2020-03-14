# !/bin/sh

# Cette fonction donne pour chaque fichier, les adresses des listes de blocks dans BLOCKS pour reconstruire le fichier
# (Seul 6 fichiers sont teste pour l'exemple ici)

for i in $(seq 043560 1 043565 )
do
	echo "Pour le fichier $i"
	cat recovery.dat | grep "$i *">fichiertemp 
	noctet=$(cat fichiertemp | cut -d " " -f2)
	cat fichiertemp | cut -d " " -f3 | while read A
	do
		nomfichier=$(echo $A)
		nomdossier=$(echo $A | grep -o '.\{2\}$')
		adresse=$(echo BLOCKS/$nomdossier/$nomfichier)
		echo $adresse
	done > $i.txt
done

