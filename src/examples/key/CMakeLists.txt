px4_add_module(
	MODULE examples__key
	MAIN key
	STACK_MAIN 2000
	SRCS
		key.c
	DEPENDS
)
