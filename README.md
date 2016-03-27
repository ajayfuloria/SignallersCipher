# SignallersCipher
This is a light weight encryption algorithm. This is particularly useful for IoT devices. 

The Cipher has 16 rounds.

One round of Cipher has essentially three stages:
# • Confusion Layer. 
Confusion is provided by using 8 identical S Boxes in a layer . Each S Box is 4 x 4 straight type which maps 4 bit input to 4 bit output bits as per Table 1.1. The mapping of 32 bit block to output is based on four non linear functions. 

#• Diffusion Layer. 
It is a linear permutation of 32 bits to meet the avalanche criteria. The permutation is carried out as shown below:

#• Add Round Key.
The round key of minimum 32 bits shall be added to provide encryption. It is a simple bit wise XOR operation carried out on state bits and key bits.
