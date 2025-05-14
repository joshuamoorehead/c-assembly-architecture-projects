.text #telling assembler everything beyond is code

#a = 10, b = 5, c = a + b
#s0,s1,s2 using

addi $s0, $zero, 10
#easier way: li $s0, 10
addi $s1, $zero, 5
add $s2, $s0, $s1

#printing using syscall stuff

addi $v0, $zero, 1 #need one to print int
move $a0, $s2
syscall 




