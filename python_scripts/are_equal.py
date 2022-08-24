"""
Sample script used to compare different kernels while finding the disposition of weights
in the memory

Returns:
    _type_: _description_
"""

def areEqual(arr1,arr2,n,m):
    # If lengths of array are not
    # equal, it means arrays are not equal
    if (n != m):
        return False
 
    # Sort both arrays
    arr1.sort()
    arr2.sort()
    
    print(arr1)
    print(arr2)
 
    # Linearly compare elements
    for i in range(0, n):
        if (arr1[i] != arr2[i]):
            return False
 
    # If all elements are the same.
    return True
        
n = len(prova)
m = len(flatten)

if (areEqual(prova, flatten, n, m)):
    print("Yes")
else:
    print("No")

