.name "Pascha_advokat"
.comment "advokaaaaat"

prestart:	sti r1, %:prelive, %1
					sti r1, %:while1, %1
					sti r1, %:while2, %1
					sti r1, %:while3, %1
					#sti r1, %:while4, %1
					sti r1, %:crforks, %4
					sti r1, %:crforks, %12
					sti r1, %:crforks, %20
					and r1, %0, r2

crforks:	fork %:start1
					live %1
					fork %:start2
					live %1
					fork %:start3
					#live %1
					#fork %:start4

prelive:	live %1
					zjmp %:prelive

#________________________________________

start1:		sti r15, %:frsp1, %0
			sti r15, %:frsp1, %4
			st r1, 13
			ld %4, r7

live1:		live %1
			ld %0, r3
			sti r8, %:while1, %392
			sti r8, %:while1, %396

while1:		live %1
			ldi %:live1, r3, r9
					sub r9, r5, r6
					zjmp %312
					add r3, r7, r3
					sti r9, %300, r3
					add r8, r8, r8
					zjmp %:while1

frsp1:		and r14, %0, r14

#________________________________________

start2:		sti r15, %:frsp2, %0
			sti r15, %:frsp2, %4
			st r1, 13
			ld %4, r7

live2:		live %1
			ld %0, r3
			sti r8, %:while2, %392
			sti r8, %:while2, %396

while2:		live %1
			ldi %:live2, r3, r9
					sub r9, r5, r6
					zjmp %312
					add r3, r7, r3
					sti r9, %300, r3
					add r8, r8, r8
					zjmp %:while2

frsp2:		and r14, %0, r14

#________________________________________

start3:		sti r15, %:frsp3, %0
			sti r15, %:frsp3, %4
			st r1, 13
			ld %4, r7

live3:		live %1
			ld %0, r3
			sti r8, %:while3, %392
			sti r8, %:while3, %396

while3:		live %1
			ldi %:live3, r3, r9
					sub r9, r5, r6
					zjmp %312
					add r3, r7, r3
					sti r9, %300, r3
					add r8, r8, r8
					zjmp %:while3

frsp3:		and r14, %0, r14

#________________________________________

