from random import randint
# Write/Paste your MIPS code at the bottom of this script
# Modify as you may
 
def convertAndPrint(instructions):
  def generateDontCare(decision):
    if decision == 1:
      dontCares = '00000'
    else:
      dontCares = ''
      for _ in range(5):
        dontCares += str(randint(0,1))
    return dontCares

    

  def negateBinary(binString): # '000101' outputs '111011' (2C negative)
      binString = ['0' if i == '1' else '1' for i in binString]
      index = len(binString) - 1
      carry = '1'
      while index >= 0:
          if (binString[index] + carry).count('1') == 2:
              binString[index] = '0'
              carry = '1'
          elif (binString[index] + carry).count('1') == 1:
              binString[index] = '1'
              carry = '0'
          elif (binString[index] + carry).count('1') == 0:
              binString[index] = '0'
              carry = '0'
          index -= 1
      return ''.join(binString)
  def offsetToImmediate(offset): # -5 outputs '1111111111111011'
    binary = bin(offset)
    if (binary[0] == '-'):
      binary = binary[3:]
      binary = '0' * (16 - len(binary)) + binary
      return negateBinary(binary)
    else:
      binary = binary[2:]
      return '0' * (16 - len(binary)) + binary
  def getJumpAddress(labelI): # 2 outputs '00000000000000000000000010' 
    binary = bin(labelI)[2:]
    return '0' * (26 - len(binary)) + binary
  def registerToBinary(registerName): # 8 outputs '01000', or t2 outputs '01010'
    try:
      number = int(registerName)
    except:
      number = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra'].index(registerName)
    binary = bin(number)[2:]
    return '0' * (5 - len(binary)) + binary
  def immediateToBinary(immediateString): # '-3' outputs '1111111111111101', or '0xff' outputs '0000000011111111'
    immediateString = immediateString.lower()
    if ('0x' in immediateString):
      binary = bin(int(immediateString, 16))[2:]
      return '0' * (16 - len(binary)) + binary
    else:
      binary = bin(int(immediateString))
      if (binary[0] == '-'):
        binary = binary[3:]
        binary = '0' * (16 - len(binary)) + binary
        return negateBinary(binary)
      else:
        binary = binary[2:]
        return '0' * (16 - len(binary)) + binary
  def removeComments(ins): # 'j myLabel #comment' outputs 'j mylabel'
    try:
      return ins[:ins.index('#')]
    except:
      return ins
  instructions = [i.strip() for i in instructions.split('\n') if len(i.strip()) != 0]
  instructions = [removeComments(i) for i in instructions if len(removeComments(i)) > 0]
  labelIndices = {}
  actualInstructionIndex = 0
 
  decision = int(input("Dont Cares Set to 0? YES = 1; NO=0; : "))
  

  for i in range(len(instructions)):
    if (instructions[i][-1] == ':'):
      labelIndices[instructions[i][:-1]] = actualInstructionIndex
    else:
      actualInstructionIndex += 1
  actualInstructionIndex = 0
  for instruction in instructions:
    originstruction = instruction
    if (instruction[-1] == ':'):
      continue
    binary = ''
    tryJ = instruction.split(' ')
    if (len(tryJ) == 2 and tryJ[0] == 'j'):      
      splitted = tryJ
    else:
      instruction = instruction.replace(' ','')
      instruction = instruction.replace(',','$')
      instruction = instruction.replace('(','$')
      instruction = instruction.replace(')','$')
      splitted = [i for i in instruction.split('$') if i != '']
    name = splitted[0].lower()

    dontCares = generateDontCare(decision)

    if (name == 'add'):
      binary = '000000' + registerToBinary(splitted[2]) + registerToBinary(splitted[3]) + registerToBinary(splitted[1]) + '00000' + '100000'
    elif (name == 'sub'):
      binary = '000000' + registerToBinary(splitted[2]) + registerToBinary(splitted[3]) + registerToBinary(splitted[1]) + '00000' + '100010'
    elif (name == 'and'):
      binary = '000000' + registerToBinary(splitted[2]) + registerToBinary(splitted[3]) + registerToBinary(splitted[1]) + '00000' + '100100'
    elif (name == 'or'):
      binary = '000000' + registerToBinary(splitted[2]) + registerToBinary(splitted[3]) + registerToBinary(splitted[1]) + '00000' + '100101'
    elif (name == 'slt'):
      binary = '000000' + registerToBinary(splitted[2]) + registerToBinary(splitted[3]) + registerToBinary(splitted[1]) + '00000' + '101010'
    elif (name == 'addi'):
      binary = '001000' + registerToBinary(splitted[2]) + registerToBinary(splitted[1]) + immediateToBinary(splitted[3])
    elif (name == 'beq'):
      binary = '000100' + registerToBinary(splitted[1]) + registerToBinary(splitted[2]) + offsetToImmediate(labelIndices[splitted[3]] - actualInstructionIndex - 1)
    elif (name == 'sw'):
      binary = '101011' + registerToBinary(splitted[3]) + registerToBinary(splitted[1]) + immediateToBinary(splitted[2])
    elif (name == 'lw'):
      binary = '100011' + registerToBinary(splitted[3]) + registerToBinary(splitted[1]) + immediateToBinary(splitted[2])
    elif (name == 'j'):
      binary = '000010' + getJumpAddress(labelIndices[splitted[1]])
    elif (name == 'nor'):
      binary = '000000' + registerToBinary(splitted[2]) + registerToBinary(splitted[3]) + registerToBinary(splitted[1]) + dontCares + '100111'
      print("{} with dontCare = {}".format(binary, dontCares))
    elif (name == 'lui'):
      binary = '001111' + dontCares + registerToBinary(splitted[1]) + immediateToBinary(splitted[2])
      print("{} with dontCare = {}".format(binary, dontCares))
    elif (name == 'sll'):
      binary = '000000' + dontCares + registerToBinary(splitted[2]) + registerToBinary(splitted[1]) + registerToBinary(splitted[3]) + '000000'
    elif (name == 'blt'):
      binary = '011111' + registerToBinary(splitted[1]) + registerToBinary(splitted[2]) + offsetToImmediate(labelIndices[splitted[3]] - actualInstructionIndex - 1)
      print("{} with dontCare = {}".format(binary, dontCares))    
    elif (name == 'li'):
      binary = '010001' + dontCares + registerToBinary(splitted[1]) + immediateToBinary(splitted[2])
     #print("{} with dontCare = {}".format(binary, dontCares))
    elif (name == 'mix'):
      binary = '000000' + registerToBinary(splitted[2]) + registerToBinary(splitted[3]) + registerToBinary(splitted[1]) + dontCares + '110011'
      print("{} with dontCare = {}".format(binary, dontCares))
    else:
      raise Exception("Unsupported instruction: "+ originstruction)
    if (len(binary) != 0):
      decimal_representation = int(binary, 2)
      _hex = hex(decimal_representation)[2:]
      _hex = '0' * (8 - len(_hex)) + _hex
      print(_hex)
    actualInstructionIndex += 1
 
# Supports the 10 instructions in Lab Exercise 12, + the 6 instructions in the CS 21 Project like mix or blt
# Supports comments, labels, multiple register names ($t0, and $8), multiple immediate declarations (0xf or 15)
 
convertAndPrint('''
 
# Sample input
addi $1, $0, 0xBABE
lui $1, 0xC0DE
''')