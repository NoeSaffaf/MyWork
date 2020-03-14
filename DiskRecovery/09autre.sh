# !/bin/sh

# Elle fait une copie du fichier avec le type que la commande file a detecte

# (Les fichiers dont le nom est entre 043560 et 043700  sont teste pour l'exemple)

for i in $(seq $1 1 $2 )
do
	
	echo "Pour le fichier $i"
	type=$(file RecoveredFile/$i | cut -d " " -f 2)
	cp RecoveredFile/$i RecoveredFile/$i.$type
	#type est une variable qui prend la valeur string du tpe de fichier
done


