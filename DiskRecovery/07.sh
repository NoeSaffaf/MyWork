# !/bin/sh

# Elle recree les fichiers dans RECOVEREDFILE
# Il n'y a pas de distingtion de cas particulier, les fichiers sont reconstruit si possible, meme incomplet

# (Les fichiers dont le nom est entre 043560 et 043700  sont teste pour l'exemple ici)

#Il y a un ajout qui pert de notifier en cas de manque de bloc pour la reconstruction d'un fichier (si le nombre d'octet attentu est superieur au nombre de bloc*4096), il ecrit aussi un fichier txt du meme nom pour indiquer un fichier incomplet

for i in $(seq 043560 1 043700 )
#On parcours l'ensemble des fichier entre les bornes de seq (que vous pouvez modifier)
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
	#on cree un fichier temporaire i.txt avec l'adresse de tous les blocs necessaires pour reformer le fichier i


        lire=$(cat $i.txt)
	compteurbloc=$(wc -l $i.txt|cut -d " " -f 1)
	cat $lire | dd of=RecoveredFile/$i bs=1 count=$noctet
	
	#lire contient la concatenation des fichiers dont l'adresse est present dans i.txt

	noctetpossible=$(echo $(($compteurbloc*4096)))

	#le nombre d'octet possible est calcule selon le nombre de bloc trouve dans BLOCKS, alors que noctet est celui
	#du fichier original
	
	if [ $noctetpossible -lt $noctet ]
	then
		echo "Ce fichier n'a pas pu etre recupere entierement, blocs manquants"
		echo "Ce fichier n'a pas pu etre recupere entierement, blocs manquants" > RecoveredFile/Bug$i.txt
	fi	
	#creation d'un petit fichier qui indique que le fichier i n'a pas pu entierement ete recupere
	rm $i.txt

done
rm fichiertemp
