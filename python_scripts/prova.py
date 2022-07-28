import numpy as np

lista=np.array([[6,2],[3,4],[5,6]])
# print(lista[0,:])

lista1 = [1,2,3,4,5]
print(lista[2,:].reshape(1,lista.shape[1]))
print(lista)
#print(lista[:-1])