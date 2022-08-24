#!/bin/bash

# 
# Generate sample inputs with maxim syntethizer
#
# Copyright 2022 Giovanni Lunardi
#


current_directory=$PWD

#choose number of iterations
ITERATIONS=1000

# GLOBAL variables
PATH_TO_CHECKPOINT=../ai8x-training/logs/2022.08.13-211904/qat_checkpoint.pth.tar # path to checkpoint.tar weights
PATH_TO_CONFIG=mnist-chw.yaml #path to network configuration
PATH_TO_SAMPLE_NPY="tests/sample_" # path where .npy samples are
PREFIX="sample_" # prefix of output folders
LABEL=1
NUM_CONVERT=30000
PATH_IMAGES=$current_directory/dataset/emnist-letters-train-images-idx3-ubyte
PATH_LABELS=$current_directory/dataset/emnist-letters-train-labels-idx1-ubyte
PATH_TO_SAVE="$(dirname "$(find $HOME -name ai8x-synthesis)")"/ai8x-synthesis

python3 sample_generator.py $ITERATIONS $LABEL $NUM_CONVERT $PATH_IMAGES $PATH_LABELS $PATH_TO_SAVE/tests

#change directory
cd $PATH_TO_SAVE

# if pyenv
source venv/bin/activate

for (( count=0; count<=$ITERATIONS; count++ ))
do
    python3 ai8xize.py --rtl --verbose --autogen rtlsim --test-dir rtlsim --prefix  $PREFIX$count --checkpoint-file $PATH_TO_CHECKPOINT --config-file $PATH_TO_CONFIG --device MAX78000 --sample-input $PATH_TO_SAMPLE_NPY$count".npy"
    cp rtlsim/sample_$count-1x28x28b_0x0s1p1m60_relu-60x28x28l_max2x2s2p2m60_relu-60x16x16l_max2x2s2p1m56_relu-56x8x8l_avg2x2s2p1m12_relu/sampledata.h $PWD/sample_data_emnist/sampledata_$count.h
done

cd $current_directory
