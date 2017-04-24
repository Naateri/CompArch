
mspfx: 

addi $v0, $zero, 0 #inicializa longitud en $v0 a 0

addi $v1, $zero, 0 #inicializa max sum en $v1 a 0

addi $t0, $zero, 0 #inicializa indice i en $t0 a 0

addi $t1, $zero, 0 #incializa suma que corre en $t1 a 0

loop:

add $t2, $t0, $t0 #fija 2i en $t2

add $t2, $t2, $t2 #fija 4i en $t2 (offset?)

addi $t3,$t2,$a0 # fija 4i+A (dirección de A[i]) en $t3

lw $t4,0($t3) # carga A[i] de mem[($t3)] en $t4

add $t1,$t1,$t4 # suma A[i] a suma que corre en $t1

slt $t5,$v1,$t1 # fija $t5 en 1 si máx sum < new sum

bne $t5,$zero,mdfy # si máx sum es menor, modificar

resultados

j test # ¿hecho?

mdfy: addi $v0,$t0,1 # nuevo prefijo máx-sum tiene longitud i+1

addi $v1,$t1,0 # nueva suma máx es la suma que corre

test: addi $t0,$t0,1 # avanza el índice i

slt $t5,$t0,$a1 # fija $t5 en 1 si i < n

bne $t5,$zero,loop # repetir si i < n

done: jr $ra # regresar length=($v0), máx sum=($v1)
