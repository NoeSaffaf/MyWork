# !/bin/sh

# C'est la premiere fonction principale de mon programme, elle recree les fichiers dans RECOVEREDFILE
# Il n'y a pas de distingtion de cas particulier, les fichiers sont reconstruit si possible, meme incomplet
# (Les fichiers dont le nom est entre 043560 et 043600  sont teste pour l'exemple ici)

#J'ai remarque, (par un heureux hasard) que meme les fichiers vides tel que 043580 sont crees vides, dd prend en input
#aussi les fichier vides

for i in $(seq 043560 1 043600 )
do
	echo "Pour le fichier $i"
	cat recovery.dat | grep "$i *">fichiertemp 
	noctet=$(cat fichiertemp | cut -d " " -f2 | head -n 1 )
	cat fichiertemp | cut -d " " -f3 | while read A
	do
		nomfichier=$(echo $A)
		nomdossier=$(echo $A | grep -o '.\{2\}$')
		adresse=$(echo BLOCKS/$nomdossier/$nomfichier)
		echo $adresse
	done > $i.txt
        lire=$(cat $i.txt)
	cat $lire | dd of=RecoveredFile/$i bs=1 count=$noctet
	rm $i.txt
done
rm fichiertemp

