from array import array
import struct
with open("/Users/gio/Desktop/samples_emnist/emnist-letters-train-images-idx3-ubyte", "rb") as binary_file:
    images = []
    emnistRotate = True
    magic, size, rows, cols = struct.unpack(">IIII", binary_file.read(16))
    if magic != 2051:
        raise ValueError('Magic number mismatch, expected 2051,''got {}'.format(magic))
    for i in range(size):
        images.append([0] * rows * cols)
    image_data = array("B", binary_file.read())
    for i in range(size):
        images[i][:] = image_data[i * rows * cols:(i + 1) * rows * cols]

        # for some reason EMNIST is mirrored and rotated
        if emnistRotate:
            x = image_data[i * rows * cols:(i + 1) * rows * cols]

            subs = []
            for r in range(rows):
                subs.append(x[(rows - r) * cols - cols:(rows - r)*cols])

            l = list(zip(*reversed(subs)))
            fixed = [item for sublist in l for item in sublist]
            images[i][:] = fixed
    print(images)