from cmath import sin
import time
import numpy as np

# Kernels_0=[-28 , 12 , -7 , -107 , 44 , 94 , 46 , -69 , -1 , -53 , -68 , -16 , 9 , -3 , 9 , 11 , -56 , -56 , -69 , -11 , -43 , -8 , 0 , 9 , 59 , -26 , -18 , -50 , 12 , 7 , 31 , 19 , -7 , 30 , -3 , 20 , 28 , -5 , -31 , 25 , -30 , -58 , -43 , 8 , -10 , 16 , 8 , 17 , -4 , 31 , 28 , -40 , 72 , 22 , 22 , 12 , 81 , 12 , -62 , 43 , -31 , -49 , -89 , 42 , -33 , 61 , 77 , 21 , -22 , 19 , -26 , -15 , -16 , -18 , -7 , -3 , 65 , -3 , -55 , -25 , 40 , 71 , 63 , 62 , -118 , 55 , 56 , 79 , -119 , -116 , -72 , -116 , 74 , 95 , 50 , -121 , 84 , 97 , 99 , 51 , 111 , -54 , 42 , 124 , -60 , -73 , -5 , 125 , 88 , 74 , 59 , 33 , 40 , 51 , 33 , 39 , -1 , -49 , -102 , -5 , 36 , -4 , -19 , -6 , -94 , -128 , -31 , -58 , 70 , 53 , 22 , -10 , -15 , -121 , -71 , 77 , -78 , -88 , -128 , -108 , -76 , -88 , -128 , -128 , 90 , 29 , 51 , 60 , 57 , 84 , 49 , 22 , 25  , 25 , 43 , 20 , 74 , 38  , 81 , 83 ]

# Kernels_1=[-23 , 14 , 81 , -1 , 36 , 11 , 73 , 37 , -47 , 52 , 109 , 37 , -17 , -11 , -40 , -13 , 108 , 49 , -46 , -23 , 126 , 127 , 49 , 55 , -5 , 80 , 31 , 80 , -23 , -19 , -33 , -4 , -9 , 2 , 32 , 6 , -124 , -119 , -102 , -55 , -48 , -96 , -109 , -81 , -56 , 23 , 30 , -31 , -32 , -16 , -37 , -12 , -16 , 37 , -71 , -53 , -27 , 45 , 66 , 22 , -75 , -26 , -45 , -22 , -44 , -88 , -122 , -106 , 51 , -20 , -38 , -25 , 37 , -32 , -40 , -13 , -29 , -70 , -70 , 50 , -6 , 21 , 34 , 2 , -93 , -2 , 36 , 20 , 79 , 41 , 28 , -57 , 5 , 44 , 37 , 46 , 43 , 29 , 84 , 20 , 56 , -28 , -37 , -4 , 32 , 33 , 66 , 30 , -56 , -82 , -24 , 67 , -7 , -20 , 11 , -7 , -29 , 5 , 46 , -6 , -11 , 47 , 77 , 46 , -11 , 43 , 12 , -29 , -85 , -28 , -21 , -63 , 120 , 3 , -7 , -45 , 113 , -110 , -49 , 113 , -1 , -45 , 50 , 124 , -82 , 9 , 59 , 51 , -2 , 74 , 105 , -59 , -94  , -17 , -81 , 83 , 64 , -88  , 2 , -101 ]

# Kernels_2=[-10 , 65 , 113 , 1 , -17 , 64 , 82 , -11 , 104 , -23 , -19 , -22 , 126 , 41 , 74 , 126 , 81 , 12 , 44 , 115 , -6 , -69 , -41 , 114 , 60 , -50 , -35 , 42 , 11 , 42 , 60 , 51 , -5 , 54 , 61 , 10 , -69 , 25 , 23 , -50 , 59 , 105 , 72 , -91 , -83 , 36 , 49 , 25 , 43 , 71 , 57 , -25 , 109 , 38 , -39 , 42 , 86 , 36 , -12 , 104 , -55 , -53 , -80 , 63 , -25 , -56 , -39 , -80 , -16 , -37 , -56 , -60 , -56 , -81 , -61 , -46 , -45 , -88 , -81 , -27 , 76 , 33 , 59 , -32 , 29 , -10 , 36 , 84 , -31 , -63 , -32 , 9 , 58 , 47 , 33 , -21 , 39 , 86 , 82 , 47 , -21 , -9 , 14 , 60 , -60 , -1 , -16 , 7 , 125 , 109 , 53 , 59 , 53 , 86 , 41 , 122 , -66 , -101 , -128 , 9 , 13 , -45 , -56 , -66 , -56 , -51 , 102 , 84 , -44 , -17 , 0 , -7 , -51 , -127 , -83 , -36 , -65 , -47 , -59 , -45 , -13 , -62 , -84 , -86 , -116 , -99 , -61 , 26 , -84 , -15 , -21 , -75 , -20   , -62 , -45 , -33 , -44 , -102  , -31 , -96  ]

# Kernels_3=[-72 , -74 , -45 , -53 , 2 , -11 , -28 , -14 , -25 , -1 , 10 , 17 , -34 , -8 , -69 , -75 , -73 , -55 , -116 , -124 , -39 , -28 , -21 , -37 , 35 , 3 , -6 , -8 , -35 , 18 , 20 , 34 , -45 , -29 , -42 , -48 , 65 , -8 , -105 , 73 , 47 , 4 , -33 , 90 , 91 , 3 , 31 , 41 , -20 , -4 , 46 , 119 , -21 , 53 , 52 , -19 , -15 , 108 , 67 , -34 , -41 , 118 , 67 , -56 , -23 , -62 , -63 , -58 , 34 , -5 , -22 , -4 , 3 , -60 , -55 , -6 , -2 , -75 , -79 , -1 , 13 , -6 , 43 , 7 , -102 , -9 , 17 , -9 , -66 , -71 , -82 , -126 , 3 , 55 , 19 , -14 , 120 , 28 , 33 , -36 , 72 , -11 , 27 , 125 , -5 , -23 , -14 , 39 , -38 , -76 , -74 , -46 , 16 , 89 , 109 , -41 , -50 , -53 , -79 , -8 , -97 , -80 , -124 , -109 , 68 , 65 , -90 , -128 , 33 , 61 , 60 , 27 , 78 , -84 , -50 , -8 , 94 , 66 , 101 , 122 , 54 , 71 , 101 , 84 , 110 , 98 , 31 , 72 , 96 , 98 , 52 , 88 , -60  , 42 , 1 , 27 , 35 , -40  , 97 , 29  ]

# Kernels_4=[19 , -120 , -115 , 35 , 40 , -11 , -46 , 41 , -73 , -28 , -19 , 70 , -122 , 23 , 13 , -80 , 2 , -33 , 30 , -118 , -17 , -38 , -35 , -22 , -70 , -32 , -22 , -32 , -20 , 30 , -24 , -102 , -31 , -20 , -44 , -37 , 127 , 127 , 127 , 116 , 127 , 58 , 35 , 127 , -36 , -41 , -32 , 112 , 82 , -45 , -94 , -87 , -17 , -52 , 100 , 97 , -34 , -93 , -52 , -47 , 6 , -41 , -21 , -45 , -2 , -59 , -61 , 16 , -31 , -69 , -51 , -17 , 12 , 45 , 53 , -18 , -36 , -27 , 20 , -19 , 72 , -89 , -84 , -44 , 122 , -81 , -84 , 49 , -33 , 24 , 78 , 126 , -55 , -11 , -30 , -50 , 108 , -22 , -62 , -77 , 111 , 48 , 97 , 127 , 34 , 100 , 103 , 127 , -26 , -30 , -13 , 7 , 66 , 90 , 58 , -17 , -50 , 23 , 14 , 19 , -18 , -11 , 13 , -27 , -58 , 9 , -5 , -23 , 39 , 51 , 28 , -91 , -22 , -35 , -19 , 13 , 30 , -20 , -83 , -35 , 56 , -70 , -92 , 4 , 7 , -79 , -89 , -6 , 87 , 26 , -27 , 44 , 1  , 113 , -40 , 1 , -4 , 18  , -32 , -40  ]

# Kernels_5=[106 , 109 , -15 , 52 , 89 , 104 , 40 , 62 , 0 , -6 , -46 , 40 , -28 , 52 , 73 , 37 , 58 , 74 , 119 , 75 , 10 , -39 , -44 , 36 , -11 , -89 , -61 , 26 , 39 , -29 , -115 , -60 , 52 , -2 , 51 , 42 , 30 , 101 , 124 , -14 , -68 , -45 , -4 , -4 , -83 , -29 , -55 , -54 , 60 , -4 , -53 , -101 , -61 , -64 , 21 , 60 , -84 , -101 , -67 , -22 , 53 , -91 , -71 , -44 , 23 , 68 , 60 , 56 , -43 , -11 , -16 , 5 , -7 , 5 , 16 , -25 , 39 , 33 , 10 , 23 , 65 , -46 , -81 , 72 , 32 , -54 , -51 , 62 , 10 , -50 , -38 , 0 , -48 , -32 , -52 , -11 , -10 , -61 , -49 , -35 , 9 , 60 , 83 , 0 , -6 , 84 , 55 , -7 , 39 , 52 , 10 , -40 , 25 , 6 , 12 , 29 , -66 , -79 , -110 , 25 , -67 , -123 , -128 , -127 , 22 , 42 , -116 , -107 , 32 , 48 , 52 , -45 , 43 , -84 , -25 , -12 , 35 , 52 , 120 , 93 , 49 , 1 , 67 , 97 , 29 , 26 , 23 , 4 , 99 , 93 , 7 , -17 , -54  , 32 , -24 , 0 , -62 , -61  , -57 , -88  ]

# Kernels_6=[-9 , -10 , -54 , -60 , 13 , 33 , 8 , -15 , -26 , -27 , -3 , 12 , -71 , -15 , -56 , -47 , 127 , 127 , -96 , -74 , 127 , 127 , 90 , 126 , 8 , 4 , -1 , 75 , 100 , 18 , 7 , 40 , 126 , 94 , 127 , 127 , 6 , 56 , 60 , -20 , 68 , 64 , 38 , -12 , -39 , -7 , -15 , 22 , -20 , 71 , 45 , 36 , -11 , -45 , -57 , -46 , -26 , -42 , -90 , 4 , -33 , -14 , -49 , -41 , -9 , 61 , 74 , 12 , -45 , 30 , 61 , 22 , -52 , -57 , -43 , -75 , 58 , -30 , -35 , -45 , 76 , 4 , -55 , 39 , 72 , -39 , -105 , -39 , -36 , -53 , -96 , -78 , -25 , -27 , -18 , -36 , -61 , -47 , 30 , -11 , -57 , -12 , -48 , -38 , -7 , 7 , -33 , -61 , 120 , 65 , -23 , 15 , -35 , -23 , -25 , 71 , -14 , -6 , -3 , -6 , -12 , -15 , 29 , -12 , 39 , -13 , 29 , 1 , -15 , -26 , -19 , 33 , -11 , -32 , 17 , 4 , -23 , -8 , 20 , 7 , -6 , 32 , 12 , -16 , -128 , -114 , 10 , -80 , -103 , -44 , 10 , -128 , 72  , -64 , 44 , 13 , 45 , 90  , -111 , -46  ]

# Kernels_7=[-22 , 124 , 125 , -126 , 82 , 112 , 94 , -89 , 69 , -38 , -33 , 4 , 101 , -114 , -83 , 69 , -30 , -60 , -126 , 73 , -36 , -74 , -51 , -43 , 5 , -51 , -31 , -71 , 8 , 32 , 11 , -9 , -13 , 4 , -4 , -21 , 32 , -44 , -20 , -2 , 63 , -17 , -64 , 41 , -113 , -4 , -21 , 113 , -16 , 13 , -71 , -106 , 94 , 79 , 24 , -42 , 70 , 87 , 48 , 41 , -16 , -65 , -86 , -28 , -32 , 0 , -45 , -26 , 41 , -45 , -61 , -21 , -2 , -19 , -10 , 24 , 85 , 53 , -7 , 8 , 46 , 115 , 49 , 96 , 33 , 47 , 22 , -43 , -116 , -72 , 6 , -7 , 34 , 11 , -26 , -88 , -37 , -31 , 9 , 55 , -22 , -125 , -122 , -61 , -14 , -107 , -105 , -60 , 53 , 44 , 31 , 60 , -125 , -39 , -23 , 56 , -33 , 31 , 18 , -115 , 56 , -30 , -8 , -12 , 9 , -42 , 56 , 95 , 23 , 20 , -21 , 81 , 12 , -18 , -28 , 40 , -34 , 79 , 46 , 33 , -67 , 122 , 56 , -33 , 78 , 102 , 74 , 37 , 100 , 92 , 48 , -26 , -25  , 4 , -15 , 20 , -2 , -54  , 48 , 27  ]

# Kernels_8=[-17 , -49 , 5 , 5 , -37 , -34 , 17 , 45 , -23 , 43 , 39 , 8 , 17 , -16 , -77 , -84 , -29 , 49 , -6 , -29 , 60 , 76 , 35 , -74 , -56 , 37 , 14 , 23 , 11 , -20 , -55 , -45 , 43 , -26 , -15 , 15 , -63 , -118 , -44 , -10 , -128 , -128 , -87 , -35 , -15 , -25 , -57 , -42 , -58 , -33 , -55 , -42 , -78 , -82 , -15 , -48 , -77 , -95 , -77 , -36 , 88 , -69 , -66 , -38 , 103 , 16 , 47 , 127 , -44 , 30 , 82 , 123 , 127 , 127 , 121 , -16 , 87 , 127 , 127 , 31 , -17 , -38 , -39 , 57 , -45 , -2 , 9 , -12 , 126 , 68 , 10 , -17 , -79 , -72 , -59 , 83 , -89 , -30 , -58 , -49 , -42 , -21 , -5 , -74 , 23 , -10 , 61 , -14 , -58 , -14 , -11 , 3 , -41 , -62 , -60 , -64 , 81 , 86 , 113 , -35 , 28 , 86 , 123 , 103 , -15 , 13 , 50 , 64 , -9 , 4 , 10 , -16 , -98 , 120 , 123 , -9 , -62 , -9 , -78 , -127 , 34 , -16 , -71 , -95 , 32 , 25 , 24 , 73 , -70 , -90 , -39 , 10 , 72  , -25 , 65 , 63 , 123 , 125  , 82 , 120  ]

# Kernels_9=[-54 , -56 , -12 , -14 , -42 , -35 , 13 , -42 , 115 , -20 , -48 , -29 , 78 , -34 , 1 , 94 , -16 , -93 , -32 , 23 , -100 , -126 , -63 , -25 , 1 , -64 , -32 , -44 , -61 , -30 , -72 , -44 , -104 , -6 , -6 , -48 , 54 , 29 , 5 , 48 , 50 , 34 , 68 , 45 , -3 , 111 , 49 , 41 , -62 , -15 , -11 , 16 , -40 , 25 , 15 , -71 , 47 , -17 , -43 , -33 , 58 , 4 , -18 , 84 , 63 , 88 , 118 , 101 , 29 , 124 , 127 , 124 , 75 , -30 , -83 , -7 , 49 , 29 , 3 , 67 , -71 , 5 , 1 , 62 , -87 , -19 , -35 , -68 , -2 , -19 , 8 , -85 , 33 , 74 , 52 , -13 , 75 , -26 , -8 , 0 , 67 , -16 , 56 , 102 , -53 , -24 , 43 , 84 , -25 , -5 , 5 , -34 , 14 , 57 , 39 , -7 , -37 , -23 , -50 , 1 , -60 , -79 , -85 , -38 , 17 , 35 , -38 , 24 , 33 , 47 , 63 , -2 , 61 , -50 , -58 , 22 , 78 , -13 , 21 , 63 , 66 , 2 , 32 , 60 , -55 , -30 , -35 , -64 , -46 , 45 , 30 , -77 , -70  , -37 , -45 , -8 , -63 , -113  , -105 , -71 ]

# Kernels_10=[-57 , -36 , -38 , -58 , 6 , 5 , -9 , -48 , 10 , -10 , 9 , 0 , -45 , -33 , -42 , 2 , 89 , 36 , -57 , -23 , 46 , 15 , -39 , 39 , -29 , 20 , 6 , 23 , -17 , 71 , 70 , 6 , -27 , -8 , -5 , -6 , 96 , 93 , 51 , -21 , 126 , 83 , 19 , 69 , -19 , 80 , 69 , 123 , 23 , 69 , 86 , -4 , -38 , -8 , 16 , -4 , 13 , 18 , 12 , -12 , -32 , 39 , 15 , 46 , -7 , -91 , -102 , -76 , 18 , -39 , -63 , -26 , 100 , 41 , 12 , -32 , -31 , -56 , 10 , 68 , 118 , -52 , -38 , -4 , 104 , -69 , -59 , 19 , 8 , 62 , -84 , 30 , -33 , -12 , -34 , -2 , -32 , 0 , 62 , -22 , 16 , -37 , -87 , -53 , 47 , -17 , -13 , 2 , 47 , 40 , -16 , 93 , -58 , -50 , -35 , -3 , -31 , 72 , 70 , -5 , -12 , 67 , 82 , 31 , -86 , -51 , 127 , 114 , -70 , -88 , -47 , -45 , 4 , 29 , 41 , -42 , 57 , -65 , -52 , -19 , 16 , -40 , -4 , 33 , -115 , -112 , -88 , -32 , -10 , -47 , -31 , -77 , -26  , -15 , -61 , 23 , 42 , 26  , -59 , -77  ]

# Kernels_11=[1 , 32 , -34 , -45 , 9 , 60 , 4 , -28 , -14 , 13 , 18 , -23 , -42 , -47 , -63 , -13 , 41 , -48 , -50 , -28 , 21 , -36 , -41 , 43 , -6 , -35 , -38 , 28 , -15 , 8 , 62 , 39 , -62 , 49 , 15 , -43 , -60 , -127 , -93 , -38 , 21 , -34 , -99 , -60 , 48 , 113 , 80 , -60 , -85 , 116 , 126 , 86 , 103 , 121 , -60 , -122 , 61 , 122 , 107 , 43 , -57 , 68 , 64 , 51 , -80 , -38 , -69 , -80 , 80 , -36 , -56 , -91 , 32 , -28 , -43 , -48 , 11 , -20 , -50 , 5 , 24 , 41 , 84 , 39 , -78 , -65 , -59 , -36 , -31 , -101 , -127 , -128 , 108 , 101 , 48 , 22 , 5 , 107 , 49 , 62 , 46 , 11 , -76 , -40 , -23 , 25 , -26 , -5 , 40 , 122 , 87 , 53 , -103 , -30 , 3 , 41 , 0 , -9 , 10 , -26 , 64 , -19 , 11 , -6 , -33 , 5 , 43 , 92 , -42 , 44 , 35 , -15 , 86 , -41 , -34 , -42 , 100 , -69 , -117 , 26 , 71 , -25 , -71 , 12 , 22 , -6 , -34 , -37 , -29 , 55 , 48 , -13 , -26  , -49 , -15 , 28 , 86 , 16  , 49 , 32 ]

# Kernel_tot=[-28, 12, -7, -107, 44, 94, 46, -69, -1, -53, -68, -16, 9, -3, 9, 11, -56, -56, -69, -11, -43, -8, 0, 9, 59, -26, -18, -50, 12, 7, 31, 19, -7, 30, -3, 20, 28, -5, -31, 25, -30, -58, -43, 8, -10, 16, 8, 17, -4, 31, 28, -40, 72, 22, 22, 12, 81, 12, -62, 43, -31, -49, -89, 42, -33, 61, 77, 21, -22, 19, -26, -15, -16, -18, -7, -3, 65, -3, -55, -25, 40, 71, 63, 62, -118, 55, 56, 79, -119, -116, -72, -116, 74, 95, 50, -121, 84, 97, 99, 51, 111, -54, 42, 124, -60, -73, -5, 125, 88, 74, 59, 33, 40, 51, 33, 39, -1, -49, -102, -5, 36, -4, -19, -6, -94, -128, -31, -58, 70, 53, 22, -10, -15, -121, -71, 77, -78, -88, -128, -108, -76, -88, -128, -128, 90, 29, 51, 60, 57, 84, 49, 22, 25, 25, 43, 20, 74, 38, 81, 83, -23, 14, 81, -1, 36, 11, 73, 37, -47, 52, 109, 37, -17, -11, -40, -13, 108, 49, -46, -23, 126, 127, 49, 55, -5, 80, 31, 80, -23, -19, -33, -4, -9, 2, 32, 6, -124, -119, -102, -55, -48, -96, -109, -81, -56, 23, 30, -31, -32, -16, -37, -12, -16, 37, -71, -53, -27, 45, 66, 22, -75, -26, -45, -22, -44, -88, -122, -106, 51, -20, -38, -25, 37, -32, -40, -13, -29, -70, -70, 50, -6, 21, 34, 2, -93, -2, 36, 20, 79, 41, 28, -57, 5, 44, 37, 46, 43, 29, 84, 20, 56, -28, -37, -4, 32, 33, 66, 30, -56, -82, -24, 67, -7, -20, 11, -7, -29, 5, 46, -6, -11, 47, 77, 46, -11, 43, 12, -29, -85, -28, -21, -63, 120, 3, -7, -45, 113, -110, -49, 113, -1, -45, 50, 124, -82, 9, 59, 51, -2, 74, 105, -59, -94, -17, -81, 83, 64, -88, 2, -101, -10, 65, 113, 1, -17, 64, 82, -11, 104, -23, -19, -22, 126, 41, 74, 126, 81, 12, 44, 115, -6, -69, -41, 114, 60, -50, -35, 42, 11, 42, 60, 51, -5, 54, 61, 10, -69, 25, 23, -50, 59, 105, 72, -91, -83, 36, 49, 25, 43, 71, 57, -25, 109, 38, -39, 42, 86, 36, -12, 104, -55, -53, -80, 63, -25, -56, -39, -80, -16, -37, -56, -60, -56, -81, -61, -46, -45, -88, -81, -27, 76, 33, 59, -32, 29, -10, 36, 84, -31, -63, -32, 9, 58, 47, 33, -21, 39, 86, 82, 47, -21, -9, 14, 60, -60, -1, -16, 7, 125, 109, 53, 59, 53, 86, 41, 122, -66, -101, -128, 9, 13, -45, -56, -66, -56, -51, 102, 84, -44, -17, 0, -7, -51, -127, -83, -36, -65, -47, -59, -45, -13, -62, -84, -86, -116, -99, -61, 26, -84, -15, -21, -75, -20, -62, -45, -33, -44, -102, -31, -96, -72, -74, -45, -53, 2, -11, -28, -14, -25, -1, 10, 17, -34, -8, -69, -75, -73, -55, -116, -124, -39, -28, -21, -37, 35, 3, -6, -8, -35, 18, 20, 34, -45, -29, -42, -48, 65, -8, -105, 73, 47, 4, -33, 90, 91, 3, 31, 41, -20, -4, 46, 119, -21, 53, 52, -19, -15, 108, 67, -34, -41, 118, 67, -56, -23, -62, -63, -58, 34, -5, -22, -4, 3, -60, -55, -6, -2, -75, -79, -1, 13, -6, 43, 7, -102, -9, 17, -9, -66, -71, -82, -126, 3, 55, 19, -14, 120, 28, 33, -36, 72, -11, 27, 125, -5, -23, -14, 39, -38, -76, -74, -46, 16, 89, 109, -41, -50, -53, -79, -8, -97, -80, -124, -109, 68, 65, -90, -128, 33, 61, 60, 27, 78, -84, -50, -8, 94, 66, 101, 122, 54, 71, 101, 84, 110, 98, 31, 72, 96, 98, 52, 88, -60, 42, 1, 27, 35, -40, 97, 29, 19, -120, -115, 35, 40, -11, -46, 41, -73, -28, -19, 70, -122, 23, 13, -80, 2, -33, 30, -118, -17, -38, -35, -22, -70, -32, -22, -32, -20, 30, -24, -102, -31, -20, -44, -37, 127, 127, 127, 116, 127, 58, 35, 127, -36, -41, -32, 112, 82, -45, -94, -87, -17, -52, 100, 97, -34, -93, -52, -47, 6, -41, -21, -45, -2, -59, -61, 16, -31, -69, -51, -17, 12, 45, 53, -18, -36, -27, 20, -19, 72, -89, -84, -44, 122, -81, -84, 49, -33, 24, 78, 126, -55, -11, -30, -50, 108, -22, -62, -77, 111, 48, 97, 127, 34, 100, 103, 127, -26, -30, -13, 7, 66, 90, 58, -17, -50, 23, 14, 19, -18, -11, 13, -27, -58, 9, -5, -23, 39, 51, 28, -91, -22, -35, -19, 13, 30, -20, -83, -35, 56, -70, -92, 4, 7, -79, -89, -6, 87, 26, -27, 44, 1, 113, -40, 1, -4, 18, -32, -40, 106, 109, -15, 52, 89, 104, 40, 62, 0, -6, -46, 40, -28, 52, 73, 37, 58, 74, 119, 75, 10, -39, -44, 36, -11, -89, -61, 26, 39, -29, -115, -60, 52, -2, 51, 42, 30, 101, 124, -14, -68, -45, -4, -4, -83, -29, -55, -54, 60, -4, -53, -101, -61, -64, 21, 60, -84, -101, -67, -22, 53, -91, -71, -44, 23, 68, 60, 56, -43, -11, -16, 5, -7, 5, 16, -25, 39, 33, 10, 23, 65, -46, -81, 72, 32, -54, -51, 62, 10, -50, -38, 0, -48, -32, -52, -11, -10, -61, -49, -35, 9, 60, 83, 0, -6, 84, 55, -7, 39, 52, 10, -40, 25, 6, 12, 29, -66, -79, -110, 25, -67, -123, -128, -127, 22, 42, -116, -107, 32, 48, 52, -45, 43, -84, -25, -12, 35, 52, 120, 93, 49, 1, 67, 97, 29, 26, 23, 4, 99, 93, 7, -17, -54, 32, -24, 0, -62, -61, -57, -88, -9, -10, -54, -60, 13, 33, 8, -15, -26, -27, -3, 12, -71, -15, -56, -47, 127, 127, -96, -74, 127, 127, 90, 126, 8, 4, -1, 75, 100, 18, 7, 40, 126, 94, 127, 127, 6, 56, 60, -20, 68, 64, 38, -12, -39, -7, -15, 22, -20, 71, 45, 36, -11, -45, -57, -46, -26, -42, -90, 4, -33, -14, -49, -41, -9, 61, 74, 12, -45, 30, 61, 22, -52, -57, -43, -75, 58, -30, -35, -45, 76, 4, -55, 39, 72, -39, -105, -39, -36, -53, -96, -78, -25, -27, -18, -36, -61, -47, 30, -11, -57, -12, -48, -38, -7, 7, -33, -61, 120, 65, -23, 15, -35, -23, -25, 71, -14, -6, -3, -6, -12, -15, 29, -12, 39, -13, 29, 1, -15, -26, -19, 33, -11, -32, 17, 4, -23, -8, 20, 7, -6, 32, 12, -16, -128, -114, 10, -80, -103, -44, 10, -128, 72, -64, 44, 13, 45, 90, -111, -46, -22, 124, 125, -126, 82, 112, 94, -89, 69, -38, -33, 4, 101, -114, -83, 69, -30, -60, -126, 73, -36, -74, -51, -43, 5, -51, -31, -71, 8, 32, 11, -9, -13, 4, -4, -21, 32, -44, -20, -2, 63, -17, -64, 41, -113, -4, -21, 113, -16, 13, -71, -106, 94, 79, 24, -42, 70, 87, 48, 41, -16, -65, -86, -28, -32, 0, -45, -26, 41, -45, -61, -21, -2, -19, -10, 24, 85, 53, -7, 8, 46, 115, 49, 96, 33, 47, 22, -43, -116, -72, 6, -7, 34, 11, -26, -88, -37, -31, 9, 55, -22, -125, -122, -61, -14, -107, -105, -60, 53, 44, 31, 60, -125, -39, -23, 56, -33, 31, 18, -115, 56, -30, -8, -12, 9, -42, 56, 95, 23, 20, -21, 81, 12, -18, -28, 40, -34, 79, 46, 33, -67, 122, 56, -33, 78, 102, 74, 37, 100, 92, 48, -26, -25, 4, -15, 20, -2, -54, 48, 27, -17, -49, 5, 5, -37, -34, 17, 45, -23, 43, 39, 8, 17, -16, -77, -84, -29, 49, -6, -29, 60, 76, 35, -74, -56, 37, 14, 23, 11, -20, -55, -45, 43, -26, -15, 15, -63, -118, -44, -10, -128, -128, -87, -35, -15, -25, -57, -42, -58, -33, -55, -42, -78, -82, -15, -48, -77, -95, -77, -36, 88, -69, -66, -38, 103, 16, 47, 127, -44, 30, 82, 123, 127, 127, 121, -16, 87, 127, 127, 31, -17, -38, -39, 57, -45, -2, 9, -12, 126, 68, 10, -17, -79, -72, -59, 83, -89, -30, -58, -49, -42, -21, -5, -74, 23, -10, 61, -14, -58, -14, -11, 3, -41, -62, -60, -64, 81, 86, 113, -35, 28, 86, 123, 103, -15, 13, 50, 64, -9, 4, 10, -16, -98, 120, 123, -9, -62, -9, -78, -127, 34, -16, -71, -95, 32, 25, 24, 73, -70, -90, -39, 10, 72, -25, 65, 63, 123, 125, 82, 120, -54, -56, -12, -14, -42, -35, 13, -42, 115, -20, -48, -29, 78, -34, 1, 94, -16, -93, -32, 23, -100, -126, -63, -25, 1, -64, -32, -44, -61, -30, -72, -44, -104, -6, -6, -48, 54, 29, 5, 48, 50, 34, 68, 45, -3, 111, 49, 41, -62, -15, -11, 16, -40, 25, 15, -71, 47, -17, -43, -33, 58, 4, -18, 84, 63, 88, 118, 101, 29, 124, 127, 124, 75, -30, -83, -7, 49, 29, 3, 67, -71, 5, 1, 62, -87, -19, -35, -68, -2, -19, 8, -85, 33, 74, 52, -13, 75, -26, -8, 0, 67, -16, 56, 102, -53, -24, 43, 84, -25, -5, 5, -34, 14, 57, 39, -7, -37, -23, -50, 1, -60, -79, -85, -38, 17, 35, -38, 24, 33, 47, 63, -2, 61, -50, -58, 22, 78, -13, 21, 63, 66, 2, 32, 60, -55, -30, -35, -64, -46, 45, 30, -77, -70, -37, -45, -8, -63, -113, -105, -71, -57, -36, -38, -58, 6, 5, -9, -48, 10, -10, 9, 0, -45, -33, -42, 2, 89, 36, -57, -23, 46, 15, -39, 39, -29, 20, 6, 23, -17, 71, 70, 6, -27, -8, -5, -6, 96, 93, 51, -21, 126, 83, 19, 69, -19, 80, 69, 123, 23, 69, 86, -4, -38, -8, 16, -4, 13, 18, 12, -12, -32, 39, 15, 46, -7, -91, -102, -76, 18, -39, -63, -26, 100, 41, 12, -32, -31, -56, 10, 68, 118, -52, -38, -4, 104, -69, -59, 19, 8, 62, -84, 30, -33, -12, -34, -2, -32, 0, 62, -22, 16, -37, -87, -53, 47, -17, -13, 2, 47, 40, -16, 93, -58, -50, -35, -3, -31, 72, 70, -5, -12, 67, 82, 31, -86, -51, 127, 114, -70, -88, -47, -45, 4, 29, 41, -42, 57, -65, -52, -19, 16, -40, -4, 33, -115, -112, -88, -32, -10, -47, -31, -77, -26, -15, -61, 23, 42, 26, -59, -77, 1, 32, -34, -45, 9, 60, 4, -28, -14, 13, 18, -23, -42, -47, -63, -13, 41, -48, -50, -28, 21, -36, -41, 43, -6, -35, -38, 28, -15, 8, 62, 39, -62, 49, 15, -43, -60, -127, -93, -38, 21, -34, -99, -60, 48, 113, 80, -60, -85, 116, 126, 86, 103, 121, -60, -122, 61, 122, 107, 43, -57, 68, 64, 51, -80, -38, -69, -80, 80, -36, -56, -91, 32, -28, -43, -48, 11, -20, -50, 5, 24, 41, 84, 39, -78, -65, -59, -36, -31, -101, -127, -128, 108, 101, 48, 22, 5, 107, 49, 62, 46, 11, -76, -40, -23, 25, -26, -5, 40, 122, 87, 53, -103, -30, 3, 41, 0, -9, 10, -26, 64, -19, 11, -6, -33, 5, 43, 92, -42, 44, 35, -15, 86, -41, -34, -42, 100, -69, -117, 26, 71, -25, -71, 12, 22, -6, -34, -37, -29, 55, 48, -13, -26, -49, -15, 28, 86, 16, 49, 32]

# Kernel_final_9 = [-70,-88,-47,-45,4,29,41,-42,57,-65,-52,-19,16,-40,-4,33,-115,-112,-88,-32,-10,-47,-31,-77,-26,-15,-61,23,42,26,-59,-77,1,32,-34,-45,9,60,4,-28,-14,13,18,-23,-42,-47,-63,-13,41,-48,-50,-28,21,-36,-41,43,-6,-35,-38,28,-15,8,62,39,-62,49,15,-43,-60,-127,-93,-38,21,-34,-99,-60,48,113,80,-60,-85,116,126,86,103,121,-60,-122,61,122,107,43,-57,68,64,51,-80,-38,-69,-80,80,-36,-56,-91,32,-28,-43,-48,11,-20,-50,5,24,41,84,39,-78,-65,-59,-36,-31,-101,-127,-128,108,101,48,22,5,107,49,62,46,11,-76,-40,-23,25,-26,-5,40,122,87,53,-103,-30,3,41,0,-9,10,-26,64,-19,11,-6,-33,5,43,92,-42,44,35,-15,86,-41,-34,-42,100,-69,-117,26,71,-25,-71,12,22,-6,-34,-37,-29,55,48,-13,-26,-49,-15,28,86,16,49,32]

# Kernel_final_8=[75,-26,-8,0,67,-16,56,102,-53,-24,43,84,-25,-5,5,-34,14,57,39,-7,-37,-23,-50,1,-60,-79,-85,-38,17,35,-38,24,33,47,63,-2,61,-50,-58,22,78,-13,21,63,66,2,32,60,-55,-30,-35,-64,-46,45,30,-77,-70,-37,-45,-8,-63,-113,-105,-71,-57,-36,-38,-58,6,5,-9,-48,10,-10,9,0,-45,-33,-42,2,89,36,-57,-23,46,15,-39,39,-29,20,6,23,-17,71,70,6,-27,-8,-5,-6,96,93,51,-21,126,83,19,69,-19,80,69,123,23,69,86,-4,-38,-8,16,-4,13,18,12,-12,-32,39,15,46,-7,-91,-102,-76,18,-39,-63,-26,100,41,12,-32,-31,-56,10,68,118,-52,-38,-4,104,-69,-59,19,8,62,-84,30,-33,-12,-34,-2,-32,0,62,-22,16,-37,-87,-53,47,-17,-13,2,47,40,-16,93,-58,-50,-35,-3,-31,72,70,-5,-12,67,82,31,-86,-51,127,114]

# Kernel_final_7=[103,16,47,127,-44,30,82,123,127,127,121,-16,87,127,127,31,-17,-38,-39,57,-45,-2,9,-12,126,68,10,-17,-79,-72,-59,83,-89,-30,-58,-49,-42,-21,-5,-74,23,-10,61,-14,-58,-14,-11,3,-41,-62,-60,-64,81,86,113,-35,28,86,123,103,-15,13,50,64,-9,4,10,-16,-98,120,123,-9,-62,-9,-78,-127,34,-16,-71,-95,32,25,24,73,-70,-90,-39,10,72,-25,65,63,123,125,82,120,-54,-56,-12,-14,-42,-35,13,-42,115,-20,-48,-29,78,-34,1,94,-16,-93,-32,23,-100,-126,-63,-25,1,-64,-32,-44,-61,-30,-72,-44,-104,-6,-6,-48,54,29,5,48,50,34,68,45,-3,111,49,41,-62,-15,-11,16,-40,25,15,-71,47,-17,-43,-33,58,4,-18,84,63,88,118,101,29,124,127,124,75,-30,-83,-7,49,29,3,67,-71,5,1,62,-87,-19,-35,-68,-2,-19,8,-85,33,74,52,-13]

# Kernel_final_6=[-13,4,-4,-21,32,-44,-20,-2,63,-17,-64,41,-113,-4,-21,113,-16,13,-71,-106,94,79,24,-42,70,87,48,41,-16,-65,-86,-28,-32,0,-45,-26,41,-45,-61,-21,-2,-19,-10,24,85,53,-7,8,46,115,49,96,33,47,22,-43,-116,-72,6,-7,34,11,-26,-88,-37,-31,9,55,-22,-125,-122,-61,-14,-107,-105,-60,53,44,31,60,-125,-39,-23,56,-33,31,18,-115,56,-30,-8,-12,9,-42,56,95,23,20,-21,81,12,-18,-28,40,-34,79,46,33,-67,122,56,-33,78,102,74,37,100,92,48,-26,-25,4,-15,20,-2,-54,48,27,-17,-49,5,5,-37,-34,17,45,-23,43,39,8,17,-16,-77,-84,-29,49,-6,-29,60,76,35,-74,-56,37,14,23,11,-20,-55,-45,43,-26,-15,15,-63,-118,-44,-10,-128,-128,-87,-35,-15,-25,-57,-42,-58,-33,-55,-42,-78,-82,-15,-48,-77,-95,-77,-36,88,-69,-66,-38]

# Kernel_final_5=[-9,-10,-54,-60,13,33,8,-15,-26,-27,-3,12,-71,-15,-56,-47,127,127,-96,-74,127,127,90,126,8,4,-1,75,100,18,7,40,126,94,127,127,6,56,60,-20,68,64,38,-12,-39,-7,-15,22,-20,71,45,36,-11,-45,-57,-46,-26,-42,-90,4,-33,-14,-49,-41,-9,61,74,12,-45,30,61,22,-52,-57,-43,-75,58,-30,-35,-45,76,4,-55,39,72,-39,-105,-39,-36,-53,-96,-78,-25,-27,-18,-36,-61,-47,30,-11,-57,-12,-48,-38,-7,7,-33,-61,120,65,-23,15,-35,-23,-25,71,-14,-6,-3,-6,-12,-15,29,-12,39,-13,29,1,-15,-26,-19,33,-11,-32,17,4,-23,-8,20,7,-6,32,12,-16,-128,-114,10,-80,-103,-44,10,-128,72,-64,44,13,45,90,-111,-46,-22,124,125,-126,82,112,94,-89,69,-38,-33,4,101,-114,-83,69,-30,-60,-126,73,-36,-74,-51,-43,5,-51,-31,-71,8,32,11,-9]

# Kernel_final_4=[39,51,28,-91,-22,-35,-19,13,30,-20,-83,-35,56,-70,-92,4,7,-79,-89,-6,87,26,-27,44,1,113,-40,1,-4,18,-32,-40,106,109,-15,52,89,104,40,62,0,-6,-46,40,-28,52,73,37,58,74,119,75,10,-39,-44,36,-11,-89,-61,26,39,-29,-115,-60,52,-2,51,42,30,101,124,-14,-68,-45,-4,-4,-83,-29,-55,-54,60,-4,-53,-101,-61,-64,21,60,-84,-101,-67,-22,53,-91,-71,-44,23,68,60,56,-43,-11,-16,5,-7,5,16,-25,39,33,10,23,65,-46,-81,72,32,-54,-51,62,10,-50,-38,0,-48,-32,-52,-11,-10,-61,-49,-35,9,60,83,0,-6,84,55,-7,39,52,10,-40,25,6,12,29,-66,-79,-110,25,-67,-123,-128,-127,22,42,-116,-107,32,48,52,-45,43,-84,-25,-12,35,52,120,93,49,1,67,97,29,26,23,4,99,93,7,-17,-54,32,-24,0,-62,-61,-57,-88]

# Kernel_final_3=[120,28,33,-36,72,-11,27,125,-5,-23,-14,39,-38,-76,-74,-46,16,89,109,-41,-50,-53,-79,-8,-97,-80,-124,-109,68,65,-90,-128,33,61,60,27,78,-84,-50,-8,94,66,101,122,54,71,101,84,110,98,31,72,96,98,52,88,-60,42,1,27,35,-40,97,29,19,-120,-115,35,40,-11,-46,41,-73,-28,-19,70,-122,23,13,-80,2,-33,30,-118,-17,-38,-35,-22,-70,-32,-22,-32,-20,30,-24,-102,-31,-20,-44,-37,127,127,127,116,127,58,35,127,-36,-41,-32,112,82,-45,-94,-87,-17,-52,100,97,-34,-93,-52,-47,6,-41,-21,-45,-2,-59,-61,16,-31,-69,-51,-17,12,45,53,-18,-36,-27,20,-19,72,-89,-84,-44,122,-81,-84,49,-33,24,78,126,-55,-11,-30,-50,108,-22,-62,-77,111,48,97,127,34,100,103,127,-26,-30,-13,7,66,90,58,-17,-50,23,14,19,-18,-11,13,-27,-58,9,-5,-23]

# Kernel_final_2=[-25,-56,-39,-80,-16,-37,-56,-60,-56,-81,-61,-46,-45,-88,-81,-27,76,33,59,-32,29,-10,36,84,-31,-63,-32,9,58,47,33,-21,39,86,82,47,-21,-9,14,60,-60,-1,-16,7,125,109,53,59,53,86,41,122,-66,-101,-128,9,13,-45,-56,-66,-56,-51,102,84,-44,-17,0,-7,-51,-127,-83,-36,-65,-47,-59,-45,-13,-62,-84,-86,-116,-99,-61,26,-84,-15,-21,-75,-20,-62,-45,-33,-44,-102,-31,-96,-72,-74,-45,-53,2,-11,-28,-14,-25,-1,10,17,-34,-8,-69,-75,-73,-55,-116,-124,-39,-28,-21,-37,35,3,-6,-8,-35,18,20,34,-45,-29,-42,-48,65,-8,-105,73,47,4,-33,90,91,3,31,41,-20,-4,46,119,-21,53,52,-19,-15,108,67,-34,-41,118,67,-56,-23,-62,-63,-58,34,-5,-22,-4,3,-60,-55,-6,-2,-75,-79,-1,13,-6,43,7,-102,-9,17,-9,-66,-71,-82,-126,3,55,19,-14]

# Kernel_final_1=[-9,2,32,6,-124,-119,-102,-55,-48,-96,-109,-81,-56,23,30,-31,-32,-16,-37,-12,-16,37,-71,-53,-27,45,66,22,-75,-26,-45,-22,-44,-88,-122,-106,51,-20,-38,-25,37,-32,-40,-13,-29,-70,-70,50,-6,21,34,2,-93,-2,36,20,79,41,28,-57,5,44,37,46,43,29,84,20,56,-28,-37,-4,32,33,66,30,-56,-82,-24,67,-7,-20,11,-7,-29,5,46,-6,-11,47,77,46,-11,43,12,-29,-85,-28,-21,-63,120,3,-7,-45,113,-110,-49,113,-1,-45,50,124,-82,9,59,51,-2,74,105,-59,-94,-17,-81,83,64,-88,2,-101,-10,65,113,1,-17,64,82,-11,104,-23,-19,-22,126,41,74,126,81,12,44,115,-6,-69,-41,114,60,-50,-35,42,11,42,60,51,-5,54,61,10,-69,25,23,-50,59,105,72,-91,-83,36,49,25,43,71,57,-25,109,38,-39,42,86,36,-12,104,-55,-53,-80,63]

# Kernel_final_0=[-28,12,-7,-107,44,94,46,-69,-1,-53,-68,-16,9,-3,9,11,-56,-56,-69,-11,-43,-8,0,9,59,-26,-18,-50,12,7,31,19,-7,30,-3,20,28,-5,-31,25,-30,-58,-43,8,-10,16,8,17,-4,31,28,-40,72,22,22,12,81,12,-62,43,-31,-49,-89,42,-33,61,77,21,-22,19,-26,-15,-16,-18,-7,-3,65,-3,-55,-25,40,71,63,62,-118,55,56,79,-119,-116,-72,-116,74,95,50,-121,84,97,99,51,111,-54,42,124,-60,-73,-5,125,88,74,59,33,40,51,33,39,-1,-49,-102,-5,36,-4,-19,-6,-94,-128,-31,-58,70,53,22,-10,-15,-121,-71,77,-78,-88,-128,-108,-76,-88,-128,-128,90,29,51,60,57,84,49,22,25,25,43,20,74,38,81,83,-23,14,81,-1,36,11,73,37,-47,52,109,37,-17,-11,-40,-13,108,49,-46,-23,126,127,49,55,-5,80,31,80,-23,-19,-33,-4]

flatten = [127,127,127,68,127,127,127,127,62,24,11,0,0,0,0,0,11,8,25,58,94,105,52,98,99,127,38,43,60,127,36,0,127,127,127,110,113,107,86,59,0,0,0,34,0,0,0,29,0,15,3,36,0,0,0,61,0,0,0,0,0,0,0,0,0,0,0,42,17,0,0,0,59,91,0,0,49,45,0,0,52,15,33,57,0,0,22,0,0,9,0,0,46,2,0,24,127,127,109,0,127,127,127,0,89,64,46,52,56,73,127,115,127,127,93,66,127,127,105,10,127,81,0,0,56,0,12,51,0,0,32,0,0,0,0,0,44,127,109,127,48,127,127,127,0,34,47,35,0,0,0,53,52,0,0,0,0,0,0,0,82,100,126,101,104,127,127,20,127,127,127,59,86,127,127,29,61,127,127,127,111,127,127,127,127,127,74,0,113,86,2,0]

# output_channel_9 = [25,57,84,49,22,90,29,51,60,81,83,43,20,74,38,25,-17,-2,74,105,-59,-82,9,59,51,2,-101,-81,83,64,-88,-94,-62,-84,-15,-21,-75,-116,-99,-61,26,-31,-96,-45,-33,-44,-102,-20,42,96,98,52,88,110,98,31,72,97,29,1,27,35,-40,-60,113,87,26,-27,44,7,-79,-89,-6,-32,-40,-40,1,-4,18,1,32,99,93,7,-17,29,26,23,4,-57,-88,-24,0,-62,-61,-54,-64,-103,-44,10,-128,-128,-114,10,-80,-111,-46,44,13,45,90,72,4,100,92,48,-26,78,102,74,37,48,27,-15,20,-2,-54,-25,-25,-70,-90,-39,10,32,25,24,73,82,120,65,63,123,125,72,-37,-46,45,30,-77,-55,-30,-35,-64,-105,-71,-45,-8,-63,-113,-70,-15,-10,-47,-31,-77,-115,-112,-88,-32,-59,-77,-61,23,42,26,-26,-49,-29,55,48,-13,22,-6,-34,-37,49,32,-15,28,86,16,-26]

# output_channel_8=[77,70,53,22,-10,-94,-128,-76,-88,-128,-128,-78,-88,-128,-108,-15,-45,-85,-28,-21,-63,-11,43,-1,-45,50,124,113,-110,-49,113,120,-36,-44,-17,0,-7,-56,-51,-13,-62,-84,-86,-65,-47,-59,-45,-51,-8,33,61,60,27,68,65,54,71,101,84,94,66,101,122,78,13,39,51,28,-91,-58,9,56,-70,-92,4,30,-20,-83,-35,-22,-12,32,48,52,-45,22,42,49,1,67,97,35,52,120,93,43,4,-15,-26,-19,33,39,-13,-6,32,12,-16,-23,-8,20,7,-11,40,23,20,-21,81,9,-42,-67,122,56,-33,-34,79,46,33,12,-9,-9,4,10,-16,-15,13,34,-16,-71,-95,-62,-9,-78,-127,-98,22,33,47,63,-2,17,35,66,2,32,60,78,-13,21,63,61,-42,-70,-88,-47,-45,-86,-51,16,-40,-4,33,57,-65,-52,-19,4,-42,-42,44,35,-15,-33,5,71,-25,-71,12,100,-69,-117,26,86]

# output_channel_7=[39,88,74,59,33,-31,-58,36,-4,-19,-6,-1,-49,-102,-121,-71,-7,-56,-82,-24,67,12,-29,-11,47,77,46,-29,5,46,3,-7,122,125,109,53,59,102,84,13,-45,-56,-66,-66,-101,-128,-127,-83,-41,-38,-76,-74,-46,-90,-128,-97,-80,-124,-109,-50,-53,-79,-84,-50,-17,-26,-30,-13,7,-5,-23,-18,-11,13,-27,-50,23,14,-35,-19,29,39,52,10,-40,-116,-107,-67,-123,-128,-127,-66,-79,-110,-84,-25,71,120,65,-23,15,29,1,-12,-15,29,-12,-14,-6,-3,-32,17,56,53,44,31,60,56,95,56,-30,-8,-12,-33,31,18,-18,-28,-64,-58,-14,-11,3,50,64,28,86,123,103,81,86,113,120,123,-7,-25,-5,5,-34,-38,24,-60,-79,-85,-38,-37,-23,-50,-50,-58,-3,47,40,-16,93,127,114,-12,67,82,31,-31,72,70,29,41,41,40,122,87,53,43,92,64,-19,11,-6,0,-9,10,-41,-34]

# output_channel_6=[-121,-119,-116,-60,-73,-5,125,111,-54,42,124,84,-5,40,51,33,46,79,41,32,33,66,30,56,-28,-37,-4,43,-6,-7,-20,11,-21,-31,-63,-60,-1,-16,7,-21,-9,14,60,39,9,53,86,41,-14,-66,-71,-5,-23,-14,39,72,-11,27,125,120,-8,16,89,109,-50,-33,24,34,100,103,127,111,48,97,127,108,19,66,90,58,-11,10,-50,-6,84,55,-7,9,60,83,0,-10,25,25,6,12,-36,-36,-53,-7,7,-33,-61,-57,-12,-48,-38,-61,-6,-35,-23,-25,-88,-116,-72,-14,-107,-105,-60,-22,-125,-122,-61,-37,-115,-125,-39,-23,83,126,68,23,-10,61,-14,-42,-21,-5,-74,-89,-35,-41,-62,-60,-13,-2,-19,-53,-24,43,84,67,-16,56,102,75,1,14,57,39,-2,8,62,47,-17,-13,2,16,-37,-87,-53,-32,-5,-58,-50,-35,22,-31,-101,-23,25,-26,-5,46,11,-76,-40,5,-26,-103,-30,3]

# output_channel_5=[-3,-72,-116,-118,55,56,79,40,71,63,97,99,51,74,95,50,-13,28,-57,-93,-2,36,20,-6,21,34,29,84,20,5,44,37,-46,-32,9,29,-10,36,84,76,33,59,86,82,47,58,47,33,-6,-82,-126,-102,-9,17,-9,13,-6,43,28,33,-36,3,55,19,-18,78,126,122,-81,-84,49,72,-89,-84,-22,-62,-77,-55,-11,-30,-25,-38,0,32,-54,-51,62,65,-46,-81,-61,-49,-35,-48,-32,-52,-75,-96,-78,72,-39,-105,-39,76,4,-55,-47,30,-11,-25,-27,-18,24,6,-7,33,47,22,-43,46,115,49,-31,9,55,34,11,-26,-16,10,-17,-45,-2,9,-12,-17,-38,-39,-30,-58,-49,-79,-72,-59,-7,8,-85,-87,-19,-35,-68,-71,5,1,-26,-8,0,33,74,52,-32,-84,30,104,-69,-59,19,118,-52,-38,0,62,-22,-33,-12,-34,-48,-127,-128,-78,-65,-59,-36,24,41,84,107,49,62,108,101,48]

# output_channel_4=[19,-26,-15,-33,61,77,21,-31,62,65,-3,-55,-25,-16,-18,-7,-20,-38,-25,-44,-88,-122,-106,-75,2,-29,-70,-70,50,37,-32,-40,-37,-56,-60,-25,-56,-39,-80,-55,-32,-45,-88,-81,-27,-56,-81,-61,-5,-22,-4,-23,-62,-63,-58,-41,7,-2,-75,-79,-1,3,-60,-55,-69,-51,-17,-2,-59,-61,16,6,-44,-36,-27,20,-19,12,45,53,-11,-16,5,23,68,60,56,53,72,39,33,10,23,-7,5,16,30,61,22,-9,61,74,12,-33,39,58,-30,-35,-45,-52,-57,-43,-45,-61,-21,-32,0,-45,-26,-16,96,85,53,-7,8,-2,-19,-10,30,82,123,103,16,47,127,88,57,87,127,127,31,127,127,121,124,127,124,63,88,118,101,58,62,49,29,3,67,75,-30,-83,-39,-63,-26,-7,-91,-102,-76,-32,-4,-31,-56,10,68,100,41,12,-36,-56,-91,-80,-38,-69,-80,-57,39,11,-20,-50,5,32,-28,-43]

# output_channel_3=[31,28,-40,-10,16,8,-49,-89,42,81,12,-62,43,72,22,-22,-16,-37,-12,-56,23,30,-26,-45,-22,-27,45,66,22,-16,37,51,71,57,-25,-83,36,49,-53,-80,63,86,36,-12,104,109,38,-16,-4,46,119,91,3,31,118,67,-56,-15,108,67,-34,-21,53,34,-45,-94,-87,-36,-41,-32,-41,-21,-45,-34,-93,-52,-47,-17,-52,-31,-4,-53,-101,-83,-29,-55,-91,-71,-44,-84,-101,-67,-22,-61,-64,-43,71,45,36,-39,-7,-15,-14,-49,-41,-26,-42,-90,4,-11,-45,-45,13,-71,-106,-113,-4,-21,-65,-86,-28,70,87,48,41,94,79,41,-33,-55,-42,-15,-25,-57,-69,-66,-38,-77,-95,-77,-36,-78,-82,-44,-15,-11,16,-3,111,49,4,-18,84,47,-17,-43,-33,-40,25,29,69,86,-4,-19,80,69,39,15,46,13,18,12,-12,-38,-8,18,116,126,86,48,113,80,68,64,51,61,122,107,43,103,121,80]

# output_channel_2=[7,31,19,59,17,-30,-58,-43,8,28,-5,-31,25,22,12,-4,-19,-33,-4,-5,-31,-48,-96,-109,-81,-124,-119,-102,-55,-71,-53,-32,42,60,51,60,25,59,105,72,-91,-69,25,23,-50,-39,42,43,18,20,34,35,41,47,4,-33,90,65,-8,-105,73,52,-19,-20,30,-24,-102,-70,112,127,58,35,127,127,127,127,116,100,97,82,-29,-115,-60,-11,-54,-68,-45,-4,-4,30,101,124,-14,21,60,60,18,7,40,8,22,68,64,38,-12,6,56,60,-20,-57,-46,-20,32,11,-9,5,113,63,-17,-64,41,32,-44,-20,-2,24,-42,-16,-20,-55,-45,-56,-42,-128,-128,-87,-35,-63,-118,-44,-10,-15,-48,-58,-30,-72,-44,1,41,50,34,68,45,54,29,5,48,15,-71,-62,71,70,6,-29,123,126,83,19,69,96,93,51,-21,16,-4,23,8,62,39,-6,-60,21,-34,-99,-60,-60,-127,-93,-38,-60,-122,-85]

# output_channel_1=[-53,-68,-26,-18,-50,-43,-8,0,9,-56,-56,-7,30,-3,20,12,52,109,80,31,80,126,127,49,55,108,49,-9,2,32,6,-23,-23,-19,-50,-35,42,-6,-69,-41,114,81,12,-5,54,61,10,11,-1,10,3,-6,-8,-39,-28,-21,-37,-73,-55,-45,-29,-42,-48,-35,-28,-19,-32,-22,-32,-17,-38,-35,-22,2,-33,-31,-20,-44,-37,-20,-6,-46,-89,-61,26,10,-39,-44,36,58,74,52,-2,51,42,39,-27,-3,4,-1,75,127,127,90,126,127,127,126,94,127,127,100,-38,-33,-51,-31,-71,-36,-74,-51,-43,-30,-60,-13,4,-4,-21,8,43,39,37,14,23,60,76,35,-74,-29,49,43,-26,-15,15,11,-20,-48,-64,-32,-44,-100,-126,-63,-25,-16,-93,-104,-6,-6,-48,-61,-10,9,20,6,23,46,15,-39,39,89,36,-27,-8,-5,-6,-17,13,18,-35,-38,28,21,-36,-41,43,41,-48,-62,49,15,-43,-15]

# output_channel_0=[-16,44,94,46,-69,-28,12,-7,-107,-69,-11,9,-3,9,11,-1,37,36,11,73,37,-23,14,81,-1,-46,-23,-17,-11,-40,-13,-47,-22,-17,64,82,-11,-10,65,113,1,44,115,126,41,74,126,104,17,2,-11,-28,-14,-72,-74,-45,-53,-116,-124,-34,-8,-69,-75,-25,70,40,-11,-46,41,19,-120,-115,35,30,-118,-122,23,13,-80,-73,40,89,104,40,62,106,109,-15,52,119,75,-28,52,73,37,0,12,13,33,8,-15,-9,-10,-54,-60,-96,-74,-71,-15,-56,-47,-26,4,82,112,94,-89,-22,124,125,-126,-126,73,101,-114,-83,69,69,8,-37,-34,17,45,-17,-49,5,5,-6,-29,17,-16,-77,-84,-23,-29,-42,-35,13,-42,-54,-56,-12,-14,-32,23,78,-34,1,94,115,0,6,5,-9,-48,-57,-36,-38,-58,-57,-23,-45,-33,-42,2,10,-23,9,60,4,-28,1,32,-34,-45,-50,-28,-42,-47,-63,-13,-14]

bias=[ 22 , 28, -28 ,-35 , 19 , -9 ,-32 ,-10 , 31 ,  8]

kernels_layer4_firstLine=[0xf0,0x2c,0x5e,0x2e,0xbb,0xe4,0x0c,0xf9,0x95,0xbb,0xf5,0x09,0xfd,0x09,0x0b,0xff,0x25,0x24,0x0b,0x49,0x25,0xe9,0x0e,0x51,0xff,0xd2,0xe9,0xef,0xf5,0xd8,0xf3,0xd1,0xea,0xef,0x40,0x52,0xf5,0xf6,0x41,0x71,0x01,0x2c,0x73,0x7e,0x29,0x4a,0x7e,0x68,0x11,0x02,0xf5,0xe4,0xf2,0xb8,0xb6,0xd3,0xcb,0x8c,0x84,0xde,0xf8,0xbb,0xb5,0xe7,0x46,0x28,0xf5,0xd2,0x29,0x13,0x88,0x8d,0x23,0x1e,0x8a,0x86,0x17,0x0d,0xb0,0xb7,0x28,0x59,0x68,0x28,0x3e,0x6a,0x6d,0xf1,0x34,0x77,0x4b,0xe4,0x34,0x49,0x25,0x00,0x0c,0x0d,0x21,0x08,0xf1,0xf7,0xf6,0xca,0xc4,0xa0,0xb6,0xb9,0xf1,0xc8,0xd1,0xe6,0x04,0x52,0x70,0x5e,0xa7,0xea,0x7c,0x7d,0x82,0x82,0x49,0x65,0x8e,0xad,0x45,0x45,0x08,0xdb,0xde,0x11,0x2d,0xef,0xcf,0x05,0x05,0xfa,0xe3,0x11,0xf0,0xb3,0xac,0xe9,0xe3,0xd6,0xdd,0x0d,0xd6,0xca,0xc8,0xf4,0xf2,0xe0,0x17,0x4e,0xde,0x01,0x5e,0x73,0x00,0x06,0x05,0xf7,0xd0,0xc7,0xdc,0xda,0xc6,0xc7,0xe9,0xd3,0xdf,0xd6,0x02,0x0a,0xe9,0x09,0x3c,0x04,0xe4,0x01,0x20,0xde,0xd3,0xce,0xe4,0xd6,0xd1,0xc1,0xf3,0xf2]

Kernels_layer4_0_mod2=[-16,44,94,46,-69,-28,12,-7,-107,-69,-11,9,-3,9,11,-1,37,36,11,73,37,-23,14,81,-1,-46,-23,-17,-11,-40,-13,-47,-22,-17,64,82,-11,-10,65,113,1,44,115,126,41,74,126,104,17,2,-11,-28,-14,-72,-74,-45,-53,-116,-124,-34,-8,-69,-75,-25,70,40,-11,-46,41,19,-120,-115,35,30,-118,-122,23,13,-80,-73,40,89,104,40,62,106,109,-15,52,119,75,-28,52,73,37,0,12,13,33,8,-15,-9,-10,-54,-60,-96,-74,-71,-15,-56,-47,-26,4,82,112,94,-89,-22,124,125,-126,-126,73,101,-114,-83,69,69,8,-37,-34,17,45,-17,-49,5,5,-6,-29,17,-16,-77,-84,-23,-29,-42,-35,13,-42,-54,-56,-12,-14,-32,23,78,-34,1,94,115,0,6,5,-9,-48,-57,-36,-38,-58,-57,-23,-45,-33,-42,2,10,-23,9,60,4,-28,1,32,-34,-45,-50,-28,-42,-47,-63,-13,-14]

print(np.multiply(flatten,Kernels_layer4_0_mod2))
# count=0
# lista=[]
# ****
# Concatenate every kernels
# ****
# for list in [Kernels_0,Kernels_1,Kernels_2,Kernels_3,Kernels_4,Kernels_5,Kernels_6,Kernels_7,Kernels_8,Kernels_9,Kernels_10,Kernels_11]:
#   lista += list

# ****
# Subdivide all weights in 10 chuncks 192 weights each
# ****
# for x in range(len(Kernel_tot)):
#   if(x%192==0):
#     print("]\n")
#   print(Kernel_tot[x],end=',')
  
# *****
# Multiply flatten with every final kernels
# *****
# count=0
# for list in [Kernel_final_0,Kernel_final_1,Kernel_final_2,Kernel_final_3,Kernel_final_4,Kernel_final_5,Kernel_final_6,Kernel_final_7,Kernel_final_8,Kernel_final_9]:
#   print("kernel_"+str(count),end='=')
#   print(np.multiply(flatten,list))
#   print("\n")
#   count+=1

# *****
# Multiply flatten with every output channels
# *****
# count=0
# print("Output of multiplication: [",end='')
# for list in [output_channel_0,output_channel_1,output_channel_2,output_channel_3,output_channel_4,output_channel_5,output_channel_6,output_channel_7,output_channel_8,output_channel_9]:
#   print(sum(np.multiply(flatten,list))+bias[count],end=',')
#   count+=1
# print("]")

# **** 
# Maxim's multiplication
# ****
# def mod2(val):
#   return -((val >> 7) & 0b1)*2**7 + ((val >> 6) & 0b1)*2**6 + ((val >> 5) & 0b1)*2**5 + ((val >> 4) & 0b1)*2**4 + ((val >> 3) & 0b1)*2**3 + ((val >> 2) & 0b1)*2**2 + ((val >> 1) & 0b1)*2**1 + ((val >> 0) & 0b1)*2**0

# def maxim_mult(a,b):
#   sign=np.sign(a)*np.sign(b)
#   mult= int((abs(a)/128 * abs(b)/128)) >>7
#   # print(mult)
#   # time.sleep(2)
#   floored_number = np.floor(0.5 + mult)
#   return floored_number * sign

# print("output_channel_0",end='=[')
# for h in range(len(flatten)):
#   print(maxim_mult(flatten[h],Kernel_final_7[h]),end=',')
# print("]")