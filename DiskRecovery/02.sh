# !/bin/sh

# Cette fonction reprend le premier cas, saud que ici on souhaite concatener plusieurs blocs, j'utilise donc la fonction# cat qui concate plusieurs fichiers, puis ensuite coupe pour ne garder que les octets necessaires

cat BLOCKS/d5/01894cd5 BLOCKS/c1/02768dc1 BLOCKS/c2/027feac2 BLOCKS/67/02c50367 | dd of=result02 bs=1 count=16173
