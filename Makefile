include config.make

libk:
	cd libc && make 

kernel: libk
	cd kernel && make 

clean:
	cd libc && make  clean
	cd kernel && make  clean
