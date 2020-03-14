# !/bin/sh

a=$(cat 43561.txt)
cat $a | dd of=result03 bs=1 count=16173
