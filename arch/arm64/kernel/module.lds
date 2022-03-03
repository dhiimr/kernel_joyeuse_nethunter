SECTIONS {
<<<<<<< HEAD
	.plt : { BYTE(0) }
	.init.plt : { BYTE(0) }
	.text.ftrace_trampoline : { BYTE(0) }
=======
	.plt 0 (NOLOAD) : { BYTE(0) }
	.init.plt 0 (NOLOAD) : { BYTE(0) }
	.text.ftrace_trampoline 0 (NOLOAD) : { BYTE(0) }
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}
