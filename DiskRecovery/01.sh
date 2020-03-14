# !/bin/sh

# Premiere fonction qui prend en argument un fichier particulier dun bloc, qui sert a la creation dun fichier complet,
# Cela permet d'introduire la fonction dd

dd if=BLOCKS/d5/029965d5 of=result01 bs=1 count=1380
