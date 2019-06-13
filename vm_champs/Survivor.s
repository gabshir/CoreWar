.name		"Survivor"
.comment	"Invincible"

	zjmp	%:run	111
	live	%1		11
	fork	%1
	zjmp	%:j1

f1:	ld		%5,		r2
	zjmp	%:run

j1:

run:	`xor		1r1,	r1,	r1, 22
l1:		st		r2,	1
		live	%1
		zjmp	%:l1
