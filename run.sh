#!/bin/bash
#gcc -g quickstop.c  -I /home/dexter/Syncsort/avro-apache-git/lang/c/src -L /home/dexter/Syncsort/avro-apache-git/lang/c/build/avrolib/lib/static/ -lavro -o quickstop
gcc -g sample.c  -I /home/dexter/Syncsort/avro-apache-git/lang/c/src -L /home/dexter/Syncsort/avro-apache-git/lang/c/build/avrolib/lib/static/ -lavro -o sample

#gcc -g sample.c ggets.c -I home/dexter/Syncsort/dmx/file-util/src -L /home/dexter/Syncsort/dmx/file-util/build/avrolib/lib/static/ -lavro -o sample
#gdb ./sample
