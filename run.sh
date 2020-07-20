rm -rf corFiles/*/*.cor
date="$(date)"
for i in $(find champs -name *.s); 
 do 
	
	./asm $i >> corFiles/our/run$date.log
	f="$(basename -s .s $i)"
	echo "$f"

	chmod 777 champs/$f.cor 
	#./school-asm $i >> corFiles/school/run$date.log
	#mv champs/*.cor corFiles/school
	mv champs/*.cor corFiles/our
	#diff corFiles/our/$f corFiles/school/$f >> result
 done
