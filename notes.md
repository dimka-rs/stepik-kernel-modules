# GCC
Use gcc-5, gcc-7 gives some warngins
https://lore.kernel.org/patchwork/patch/744701/

# cc1: error: code model kernel does not support PIC mode
Add -fno-pie to KBUILD_CFLAGS in Makefile

# undefined reference to `____ilog2_NaN'
Use patch
https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/diff/?id=474c90156c8dcc2fa815e6716cc9394d7930cb9c

# create node
sudo mknod /dev/chrdev c 700 0
sudo chmod a+rw /dev/chrdev
