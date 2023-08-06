;*******************************
;                              *
; MACROS                       *
;                              *
; AUTHOR:  BILL CHATFIELD      *
; LICENSE: GPL2                *
;                              *
;*******************************

PUSHY    .MACRO
         TYA
         PHA
         .ENDM

POPY     .MACRO
         PLA
         TAY
         .ENDM

PUSHXY   .MACRO
         TXA
         PHA
         TYA
         PHA
         .ENDM

POPXY    .MACRO
         PLA
         TAY
         PLA
         TAX
         .ENDM

;*******************************
;                              *
; PUTS .MACRORO - OUTPUTS STRING  *
; ]1 = ADDRESS OF NULL-        *
;      TERMINATED STRING       *
;                              *
;*******************************

PUTS     .MACRO
         PUSHY
         LDY   #0         ; PREPARE LOOP INDEX
NEXT     LDA   \0,Y       ; LOAD A CHARACTER
         CMP   #0         ; CHECK FOR END OF STRING
         BEQ   DONE
         ORA   #%10000000 ; SET HIGH BIT FOR OUTPUT
         JSR   COUT
         INY
         JMP   NEXT
DONE     POPY
         .ENDM

;*******************************
;                              *
; PUTF -                       *
; PRINTS FLOATING POINT NUMBER *
; IN FAC. DESTROYS VALUE IN    *
; FAC. DON'T KNOW WHY.         *
;                              *
; ]1 - ABS ADDR FOR STRING     *
;                              *
;*******************************

PUTF	.MACRO
	JSR	FOUT       ;CONVERT FAC TO STRING
	STA	\0         ;STORE LOW BYTE OF STRING
	STY	\0+1       ;STORE HIGH BYTE OF STRING
	PUTS	(\0)       ;PRINT STRING
	.ENDM

; Overwrites A and Y
HLIN	.MACRO	x1,x2,y1
	ldy	x1			;Leftmost X coordinate
	lda	x2
	sta	H2			;Rightmost X coordinate
	lda	y1			;Y coordinate
	jsr	HLINE
	.ENDM

