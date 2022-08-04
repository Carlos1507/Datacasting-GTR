#Programa para convertir tramas TS hex a binario
from cmath import inf

with open('as1.txt', 'r') as f:# con el archivo abierto en lectura has
    lines = f.readlines() #leer todas las lineas
    #inicio una variable que almacenara la lista de lineas dentro del texto
    lineas = []
    for line in lines:
        lineas.append(line.split('   ')[1])#obtengo los valores exadecimales en la linea y separo el id de esta
    #una vez obtenido los valores en exadecimal se realiza la conversion a paralelo
    hexnumbers = []#creo una lista con valores exadecimales
    for info in lineas:
        for i in range(len(info.split(' '))):#recorro en el tamaño de cada informacion de cada linea
            hexnumbers.append(info.split(' ')[i])#almaceno cada valor hexadecimal
    #ahora convertimos de exadecimal a binarios 
    hexnumbers = []#creo una lista con valores exadecimales
    for info in lineas:
        for i in range(len(info.split(' '))):#recorro en el tamaño de cada informacion de cada linea
            hexnumbers.append(info.split(' ')[i])#almaceno cada valor hexadecimal
    #ahora convertimos de exadecimal a binarios 
    scale = 16#escala en la que se trabaja
    num_of_bits = 8 # numero de bits
    binarynumbers = [] #lista que almacena los numeros binarios en escala de 8 bits (max 255)
    for hexnumber in hexnumbers:   #recorro los numeros hexadecimales
        try:
            binarynumbers.append(bin(int(hexnumber, scale))[2:].zfill(num_of_bits))#los exadecimales validos los alm>
        except:
            pass
    fout = open('bits.txt','w')    #se crea un archivo de salida con los bits
    binarystr = ""                 #string para almacenar los bits
    for bit in binarynumbers:
        binarystr+=bit
    fout.write(binarystr)          #escribo los bits como string
    fout.close                     #cierro el archivo de salida .txt
    f.close                        #cierro el archivo de entrada .txt
  
