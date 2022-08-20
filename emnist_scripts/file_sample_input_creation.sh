#!/bin/bash

count=0
ITERATIONS=1000
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