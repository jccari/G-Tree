import sys
import random

def generate(filename, entries, dimensions):
	file = open(filename, 'wb')	
	for i in range(0,entries,1):
		line = " "
		for x in range(0,dimensions,1):
			num = random.uniform(2,10)
			#print num," " ,str(num)
			line = line + str(num) +","
		line = line[1:len(line)-1]
		line += "\n"
		file.write(line)

	file.close()



filename = str(sys.argv[1])
ents = int(sys.argv[2])
dims = int(sys.argv[3])

if __name__ == '__main__':
	print "hola"
	generate(filename, ents, dims)
