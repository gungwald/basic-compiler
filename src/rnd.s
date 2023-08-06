;**************************
;
; Random dungeon generator
;
;**************************

        .code

	.include    "symbols.s"
	.include    "macros.s"

main
	jsr	seedRandomNumGenerator
	jsr	initLoResFullScreen
	jsr	setRandomColor		;Set the color
	jsr	drawHallway
	jsr	drawRoom
	jsr	waitForKeypress
	sta	TEXTON
	rts

waitForKeypress
	rts
	
drawHallway
	lda	#16
	jsr	generateRandomInt
	sta	x2			;Rightmost X coordinate
	HLIN	#0,x2,#10
	rts

drawRoom
	rts
	
initLoResFullScreen
	sta	TEXTOFF			;Enable graphics
	sta	HIRESOFF		;Enable Lo-res
	sta	MIXEDOFF		;Full screen
	jsr	CLRSCR			;Clear the screen
	rts

; Add A to FAC leaving result in FAC
addAccumToFac
	pha
	jsr	MOVAF			;Move FAC to ARG
	pla
	jsr	FLOAT			;Convert A to floating point in FAC
	lda	FACEXP			;Required for FADDT
	jsr	FADDT			;Add ARG to FAC putting result in FAC
	rts				;Return with result in FAC

; Multiply FAC by A leaving result in FAC
multFacByAccum
	pha				;Save A on stack
	jsr	MOVAF			;Move FAC to ARG
	pla				;Get original value back in A
	jsr	FLOAT			;Convert value in A to floating point in FAC
	lda	FACEXP			;Required for FMULTT
	jsr	FMULTT			;Multiply ARG by FAC putting result in FAC
	rts				;Return with result in FAC
	
; Seed RND function by calling it with a variable negative number.
seedRandomNumGenerator	
	lda	RNDL			;RNDL is a good seed value, because it changes
	ora	#$80			;Make it negative so RND will interpret it as a seed
	jsr	FLOAT			;Convert it to floating point
	jsr	RND			;Seed the random number generator
	rts

; Generate a floating point random number in the range [0,1) with result in FAC
generateRandomFloat
	lda	#1			;A 1 arg to RND says to give the next random num
	jsr	FLOAT			;Convert to floating point as required by RND
	jsr	RND			;Generate the random number
	rts				;Return with result in FAC

; Generate an integer random number in the range [0,A) with result in A
generateRandomInt
	pha				;Save parameter in A to stack
	jsr	generateRandomFloat	;Generate random number [0,1) in FAC
	pla				;Load multiplier into accumulator
	jsr	multFacByAccum		;Multiply FAC by A
	jsr	CONINT			;Convert FAC to 1-byte int in X
	txa				;Put the result in A
	rts				;Return with result A

; Generate an integer random number in the range [1,A] inclusive 
; with result in A
generateRandomPositive
	jsr	generateRandomInt	;Get an integer between [0,A) in A
	clc				;Change the range to [1,A]
        adc     #1
	rts

; Set the color to a random non-black value.
setRandomColor
	lda	#15			;Max color number
	jsr	generateRandomPositive
	jsr	SETCOLR			;Set the color
	rts

        .data

x2	.byte	0

