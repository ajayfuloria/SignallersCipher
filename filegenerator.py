import random
import string

def id_generator(size=1, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))
f = 'file'
for i in range (5,21):
	fileName = f+str(i)
	fileName = open("./"+fileName, "a")
	for j in range(0, pow(2,i)):
		fileName.write(id_generator())
	fileName.close()


	

