#!/bin/bash

#
# Takes $ITERATIONS samples and write them in sample_inputs.h file
#

count=0
ITERATIONS=45
LAST=$((ITERATIONS-1))

echo "int sample_inputs_all["$ITERATIONS"][196]= { \\" >> sample_inputs.h
for (( count=0; count<$ITERATIONS; count++ ))
do
    if [[ $count == $LAST ]]; then
        echo "{ \\" >>  sample_inputs.h && (sed -n '2,26p ' < ../sample_data_emnist/sampledata_$count.h) >> sample_inputs.h && echo "} \\" >> sample_inputs.h
    else
        echo "{ \\" >>  sample_inputs.h && (sed -n '2,26p ' < ../sample_data_emnist/sampledata_$count.h) >> sample_inputs.h && echo "}, \\" >> sample_inputs.h
    fi
done
echo "};" >> sample_inputs.h