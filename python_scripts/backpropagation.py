import numpy as np

"""
Sample application of OL algorithm 
"""

true_output=np.array([32767])
out_softmax=np.array([3855])
learning_rate=0.001

Kernels_layer4_0_mod2=np.array([-16,44,94,46,-69,-28,12,-7,-107,-69,-11,9,-3,9,11,-1,37,36,11,73,37,-23,14,81,-1,-46,-23,-17,-11,-40,-13,-47,-22,-17,64,82,-11,-10,65,113,1,44,115,126,41,74,126,104,17,2,-11,-28,-14,-72,-74,-45,-53,-116,-124,-34,-8,-69,-75,-25,70,40,-11,-46,41,19,-120,-115,35,30,-118,-122,23,13,-80,-73,40,89,104,40,62,106,109,-15,52,119,75,-28,52,73,37,0,12,13,33,8,-15,-9,-10,-54,-60,-96,-74,-71,-15,-56,-47,-26,4,82,112,94,-89,-22,124,125,-126,-126,73,101,-114,-83,69,69,8,-37,-34,17,45,-17,-49,5,5,-6,-29,17,-16,-77,-84,-23,-29,-42,-35,13,-42,-54,-56,-12,-14,-32,23,78,-34,1,94,115,0,6,5,-9,-48,-57,-36,-38,-58,-57,-23,-45,-33,-42,2,10,-23,9,60,4,-28,1,32,-34,-45,-50,-28,-42,-47,-63,-13,-14])
print(Kernels_layer4_0_mod2.shape[0])
flatten = [127,127,127,68,127,127,127,127,62,24,11,0,0,0,0,0,11,8,25,58,94,105,52,98,99,127,38,43,60,127,36,0,127,127,127,110,113,107,86,59,0,0,0,34,0,0,0,29,0,15,3,36,0,0,0,61,0,0,0,0,0,0,0,0,0,0,0,42,17,0,0,0,59,91,0,0,49,45,0,0,52,15,33,57,0,0,22,0,0,9,0,0,46,2,0,24,127,127,109,0,127,127,127,0,89,64,46,52,56,73,127,115,127,127,93,66,127,127,105,10,127,81,0,0,56,0,12,51,0,0,32,0,0,0,0,0,44,127,109,127,48,127,127,127,0,34,47,35,0,0,0,53,52,0,0,0,0,0,0,0,82,100,126,101,104,127,127,20,127,127,127,59,86,127,127,29,61,127,127,127,111,127,127,127,127,127,74,0,113,86,2,0]

output_last_layer_0 = np.array(np.multiply(flatten,Kernels_layer4_0_mod2))

Kernels_layer4_0_mod2_2=np.array([-16,44,94,46,-69,-28,12,-7,-107,-69,-11,9,-3,9,11,-1,37,36,11,73,37,-23,14,81,-1,-46,-23,-17,-11,-40,-13,-47,-22,-17,64,82,-11,-10,65,113,1,44,115,126,41,74,126,104,17,2,-11,-28,-14,-72,-74,-45,-53,-116,-124,-34,-8,-69,-75,-25,70,40,-11,-46,41,19,-120,-115,35,30,-118,-122,23,13,-80,-73,40,89,104,40,62,106,109,-15,52,119,75,-28,52,73,37,0,12,13,33,8,-15,-9,-10,-54,-60,-96,-74,-71,-15,-56,-47,-26,4,82,112,94,-89,-22,124,125,-126,-126,73,101,-114,-83,69,69,8,-37,-34,17,45,-17,-49,5,5,-6,-29,17,-16,-77,-84,-23,-29,-42,-35,13,-42,-54,-56,-12,-14,-32,23,78,-34,1,94,115,0,6,5,-9,-48,-57,-36,-38,-58,-57,-23,-45,-33,-42,2,10,-23,9,60,4,-28,1,32,-34,-45,-50,-28,-42,-47,-63,-13,-14])

cost=[1]
print(cost)
for i in range(500):
    for i in range(0,Kernels_layer4_0_mod2.shape[0]):
        deltaW=np.multiply(cost,output_last_layer_0[i])
        # print("DeltaW= "+str(deltaW))
        dW=np.multiply(deltaW,learning_rate)
        # print("dW= "+str(dW))
        Kernels_layer4_0_mod2_2[i]=Kernels_layer4_0_mod2_2[i]-dW

print("out= "+str(output_last_layer_0))

print("pesi prima= "+str(Kernels_layer4_0_mod2))

print("pesi dopo= ",Kernels_layer4_0_mod2_2)

