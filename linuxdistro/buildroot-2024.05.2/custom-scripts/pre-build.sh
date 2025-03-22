#!/bin/sh

HOST=`hostname -I | awk '{print $1}'`
cat $BASE_DIR/../custom-scripts/network-config | sed 's/\[IP-DO-HOST\]/'"$HOST"'/g' > $BASE_DIR/../custom-scripts/S41network-config
cp $BASE_DIR/../custom-scripts/S41network-config $BASE_DIR/target/etc/init.d
chmod +x $BASE_DIR/target/etc/init.d/S41network-config
