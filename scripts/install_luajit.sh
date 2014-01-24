#!/bin/bash

#need absolute path for proper jit installation
CUR_DIR=$(pwd)
JIT_DEST=../libs/luajit
INSTALL_DIR=$CUR_DIR/$JIT_DEST

#download jitlua
git clone http://luajit.org/git/luajit-2.0.git

# Create folder for installation files
mkdir -p $JIT_DEST


### BUILD LuaJIT-2.0 #################
cd luajit-2.0
# Build a 32-bit binary even if native machine is 64 bit, OF is 32.
make CC="gcc -m32"

### INSTALL LuaJIT-2.0 ###############
make install PREFIX=$INSTALL_DIR
mv COPYRIGHT $INSTALL_DIR/.
mv README $INSTALL_DIR/.

### Clean build files ##############
cd ../
rm -R luajit-2.0

### Clean install files ##############
rm -R $JIT_DEST/bin
