# SignallersCipher
This is a light weight encryption algorithm. This is particularly useful for IoT devices. 

The Cipher has 16 rounds.

One round of Cipher has essentially three stages:
# • Confusion Layer. 
Confusion is provided by using 8 identical S Boxes in a layer . Each S Box is 4 x 4 straight type which maps 4 bit input to 4 bit output bits as shown below. The mapping of 32 bit block to output is based on four non linear functions. 

____________________________________________________________________________________________
0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |  11  | 12 | 13 | 14 | 15 |
--------------------------------------------------------------------------------------------
0  |  8  |  9  |  15 | 12  | 11  | 10  |  3  |  6  |  4  |  1   |  13  | 7  | 14 | 5   | 2 |
--------------------------------------------------------------------------------------------

#• Diffusion Layer. 
It is a linear permutation of 32 bits to meet the avalanche criteria. The permutation is carried out as shown below:


#• Add Round Key.
The round key of minimum 32 bits shall be added to provide encryption. It is a simple bit wise XOR operation carried out on state bits and key bits.

Number of rounds. The number of rounds have been decided to make the cipher resilient to linear and diﬀerential cryptanalysis.
Differential Analysis. The diﬀerential characteristics are based on number of active Sboxes which have been found to be 10 over a 5 round observation. Extending this over 15 rounds would require 30 active Sboxes. Since for 4 x 4 bijective Sbox the maximal diﬀerential bound is p = 1/4(2−2). Over 15 rounds we obtain a differential probability of 2−60, which is worst than brute force attack over 32/40/48 bit key.For 64 bit key the same needs to be extended over minimum of 20 rounds.

Sbox size and Type. The SPN system is based on a straight 4 x 4 Sbox. A 4 x 4 system has been chosen to have a optimised hardware implementation with bit level permutation as against the AES standard which uses byte as the smallest integral unit. Also, other similar proven light weight crypto systems have been found to have most optimised design in tems of power consumption and VLSI chip area.


