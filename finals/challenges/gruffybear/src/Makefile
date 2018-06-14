all: gruffybear.c
	gcc -Wl,-z,relro,-z,now -D_FORTIFY_SOURCE=2 -O2 -o gruffybear -fpic -pie gruffybear.c
