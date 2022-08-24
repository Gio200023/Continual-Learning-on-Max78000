
from pickletools import uint8
import numpy as np
import matplotlib.pyplot as plt
import argparse

"""
convert EMNIST binary to text file; combine pixels and labels
target format:
pixel_1 (tab) pixel_2 (tab) . . pixel_784 (tab) digit
BUT, pixels are stored in column-major form, not by rows
"""

def convert(img_file, label_file, txt_file, n_images):
    print("\nOpening binary pixels and labels files ")
    lbl_f = open(label_file, "rb")   # EMNIST has labels 1-26
    img_f = open(img_file, "rb")     # and pixel vals separate
    print("Opening destination text file ")
    txt_f = open(txt_file, "w")      # output file to write to

    print("Discarding binary pixel and label files headers ")
    img_f.read(16)   # discard header info
    lbl_f.read(8)    # discard header info

    print("\nReading binary files, writing to text file ")
    print("Format: 784 pixel vals then label val, tab delimited ")
    for i in range(n_images):   # number images requested
        lbl = ord(lbl_f.read(1))  # get label (unicode, one byte)
        for j in range(784):  # get 784 vals from the image file
            val = np.int8(ord(img_f.read(1)))
            # if it's the right label (DELETE if don't want images of just one specific label)
            if lbl == 1:
                if val == 0:
                    txt_f.write("-128" + "\t")
                else:
                    txt_f.write(str(val) + "\t")
        if lbl == 1:  # LABEL "A"
            txt_f.write(str(lbl) + "\n")
    img_f.close()
    txt_f.close()
    lbl_f.close()
    print("Done ")


# -----------------------------------------------------------
X_SHAPE = 28
Y_SHAPE = 28


def display_from_array(arr, idx, count, save):
    # assumes arr = loadtxt(. . ) has been called
    x_data = arr[:, 0:784]
    y_data = arr[:, 784]
    label = int(y_data[idx])  # 1 to 26

    # transpose images to (1,28,28)
    pixels = np.array([np.transpose(x_data[idx].reshape((X_SHAPE, Y_SHAPE)))])
    np.save(f"{save}/sample_{count}.npy", pixels,
            allow_pickle=False, fix_imports=False)

# -----------------------------------------------------------


def main():
    img_file = "emnist_train_100.txt"
    parser = argparse.ArgumentParser(
        description='Emnist traim images from binary files')
    parser.add_argument('num', help='number of images to create')
    parser.add_argument('label', help='label')
    parser.add_argument('totalimages', help='number of images to convert')
    parser.add_argument('images', help='path to ubyte images')
    parser.add_argument('labels', help='path to ubyte labels')
    parser.add_argument('save', help='path where to save .npy files')

    args = parser.parse_args()
    iterations = args.num

    convert(
        str(args.images), str(args.labels),
        "emnist_train_images.txt", int(args.totalimages))

    # show first 10 training images
    # load all images so can display several
    print("\nShowing train images: \n")
    arr = np.loadtxt(img_file, delimiter="\t",
                     usecols=range(0, 785), dtype=np.int64)
    count = 0
    for idx in range(0, int(iterations)):
        display_from_array(arr, idx, count, str(args.save))  # first 10 images
        count += 1
        print(" ")


if __name__ == "__main__":
    main()
