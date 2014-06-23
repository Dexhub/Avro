#!/bin/bash
#gcc -g quickstop.c  -I /home/dexter/Syncsort/avro-apache-git/lang/c/src -L /home/dexter/Syncsort/avro-apache-git/lang/c/build/avrolib/lib/static/ -lavro -o quickstop
#gcc -g sample.c  -I /home/dexter/Syncsort/dmx/file-util/src -L /home/dexter/Syncsort/dmx/file-util/build/avrolib/lib/static/ -lavro -o sample 

echo "## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## "
echo "\n#### Testing Avro API wrapper #####"
echo "\n# Compiling..."
gcc -g example.c avro-lib.c  -I /home/dexter/Syncsort/dmx/file-util/src -L /home/dexter/Syncsort/dmx/file-util/build/avrolib/lib/static/ -lavro -o example
echo "\n# Running example... Check: avro.data"
./example
echo "\n\n# Testing the output... "
./example 1> avro.data
java -jar ./avro-tools-1.7.6.jar tojson avro.data


echo "\n## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## "

echo "\n#### Testing Avro Utility #####"
echo "\n# Compiling..."
gcc -g sample.c ggets.c -I home/dexter/Syncsort/avro/lang/c/src -L /home/dexter/Syncsort/dmx/file-util/build/avrolib/lib/static/ -lavro -o sample
echo "## Writing Data to avro.data file"
#./sample data.avsc -O avro.data
echo "## Converting the data from the Avro file into json"
java -jar ./avro-tools-1.7.6.jar tojson avro.data

echo "## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## "
