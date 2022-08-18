import matplotlib.pyplot as plt
import gzip
import numpy as np
# f = gzip.open(
#     '/Users/gio/Desktop/gzip/emnist-letters-train-images-idx3-ubyte.gz', 'r')

# image_size = 28
# num_images = 5


# f = gzip.open(
#     '/Users/gio/Desktop/gzip/emnist-letters-train-labels-idx1-ubyte.gz', 'r')
# f.read(8)
# for i in range(0, 50):
#     buf = f.read(1)
#     data = np.frombuffer(buf, dtype=np.uint8).astype(np.float32)
#     data = data.reshape(num_images, image_size, image_size, 1)
#     image = np.asarray(data[2]).squeeze()
#     plt.imshow(image)
#     plt.show()
#     labels = np.frombuffer(buf, dtype=np.uint8).astype(np.int64)
#     print(labels)


# f.read(16)
# buf = f.read(image_size * image_size * num_images)
# data = np.frombuffer(buf, dtype=np.uint8).astype(np.float32)
# data = data.reshape(num_images, image_size, image_size, 1)

# image = np.asarray(data[2]).squeeze()
# plt.imshow(image)
# plt.show()

#comodo per prendere tutti gli input dalle ubyte
# import idx2numpy
# import cv2 as cv
# file = '/Users/gio/Desktop/samples_emnist/emnist-byclass-test-images-idx3-ubyte'
# arr = idx2numpy.convert_from_file(file)
# # arr is now a np.ndarray type of object of shape 20800, 28, 28

# cv.imwrite("/Users/gio/Desktop/prova.jpg", arr[50])

def get(
        filename,
        synthesize_input=None,
        synthesize_words=8,
):
    """
    Return a sample input image from the file name `filename` in channel-first format
    (i.e., CL, CHW)
    """

    # Load data saved using
    # np.save(os.path.join('tests', f'sample_{dataset}'), data,
    #         allow_pickle=False, fix_imports=False)

    data = np.load(filename)
    if data.dtype.type is not np.dtype('int64').type:
        eprint(f'The sample data array in {filename} is of type {data.dtype}, rather than '
               'int64!')

    if synthesize_input is not None:
        # Every 8 (or synthesize_words) words, add data to the
        # combined 32-bit word for up to 4 channels
        shape = data.shape
        if shape[0] < 1 or shape[0] > 4:
            eprint('`--synthesize-input` requires 1 to 4 input channels.')
        data = data.reshape(shape[0], -1)
        if data.shape[1] % synthesize_words != 0:
            eprint('`--synthesize-words` must be a divisor of the number of pixels per channel '
                   f'({data.shape[1]}).')
        if shape[0] == 3:
            mask = 0xffffff
        elif shape[0] == 2:
            mask = 0xffff
        elif shape[0] == 1:
            mask = 0xff
        else:
            mask = 0xffffffff
        for i in range(synthesize_words, data.shape[1], synthesize_words):
            for j in range(synthesize_words):
                val = 0
                for c in range(shape[0]-1, -1, -1):
                    val = val << 8 | s2u(data[c, i+j-synthesize_words])
                val += synthesize_input
                val &= mask
                for c in range(shape[0]-1, -1, -1):
                    data[c, i+j] = u2s((val >> c * 8) & 0xff)
        data = data.reshape(shape)

    return data

f= open("sample_in_c.c","a")
f.write(str(get("/Users/gio/Online-Learning-on-Max78000/emnist_sample_creation/prova.npy")))

# FUNZIA: devo fare in modo di trasformalo in C