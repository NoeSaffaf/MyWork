# !/bin/sh

# Une valeureuse (mais pas tres intelligente) tentative de recreer la commande file, inutile au devoir, mais vous pouvez
# y jeter un coup d'oeil par curiosite

for i in $(seq 043560 1 043700 )
do
	
	echo "Pour le fichier $i"
	test1=$(cat RecoveredFile/$i | head -n 1 | cut -c 1-14)	
	html="<!DOCTYPE HTML"
	if [ "$test" = "$html" ]
	then
		echo "its a html file!"
	        cp RecoveredFile/$i RecoveredFile/$i.html
	fi

	test2=$(cat RecoveredFile/$i | head -n 1 | cut -c 1-7) 
	png="<89>PNG"
	echo $test2
	if [ "$test2" = "$png" ]
	then
		echo "its a png file!"
		cp RecoveredFile/$i RecoveredFile/$i.png
	fi


done


