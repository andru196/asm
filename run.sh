rm -f champs/*/*.cor
for i in $(find champs -name *.s); 
 do 
	
	./asm $i;
	f="$(basename -s .s $i)"
	echo "$f"

	chmod 777 champs/$f.cor 
	#./school-asm $i
	#mv champs/*.cor corFiles/school
	mv champs/*.cor corFiles/our
	#diff corFiles/our/$f corFiles/school/$f >> result
 done
