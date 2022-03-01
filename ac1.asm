ORG 100h
.MODEL SMALL 
.DATA
NUM_1 DB 0F2H
NUM_2 DB 4H
.CODE   
MOV BH, NUM_2     ;Load numerator in BH  
MOV AL, NUM_1     ;Load denominator in AL
DIV BH            ;Divide BH by AL
RET
end