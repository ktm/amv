#!/bin/bash -eux

apt-get install chrpath

cd /tmp

git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
export PATH=`pwd`/depot_tools:"$PATH"

fetch v8
cd v8

make native library=shared -j8

chrpath -r '$ORIGIN' out/native/lib.target/libv8.so

sudo mkdir -p /tmp/v8-install/lib /tmp/v8-install/include
sudo cp out/native/lib.target/lib*.so /tmp/v8-install/lib/
sudo cp -R include/* /tmp/v8-install/include
echo -e "create /tmp/v8-install/lib/libv8_libplatform.a\naddlib out/native/obj.target/tools/gyp/libv8_libplatform.a\nsave\nend" | sudo ar -M


