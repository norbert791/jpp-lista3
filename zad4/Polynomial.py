class Polynomial:
  lst = []
  
  def __init__(self, lst):
    self.lst = lst.copy()
    Polynomial.trimList(lst)

  def degree(self):
    return len(self.lst) - 1
  
  def __add__(self, pol):
    lst1 = [x for x in self.lst]
    lst2 = [x for x in pol.lst]
    Polynomial.alignLists(lst1, lst2)
    result = [lst1[i] + lst2[i] for i in range(len(lst1))]
    Polynomial.trimList(result)
    return Polynomial(result)
  
  def __neg__(self):
    result = [-x for x in self.lst]
    return Polynomial(result)

  def __sub__(self, number):
    temp = -number
    return self + temp
  
  def __mul__(self, number):
    selfCopy = Polynomial([x for x in self.lst])
    classType = type(selfCopy.lst[0])
    result = Polynomial([classType(0)])
    Polynomial.alignLists(result.lst, selfCopy.lst)

    for i in range(len(number.lst)):
      temp = Polynomial(selfCopy.lst)
      Polynomial.scalarMult(temp.lst, number.lst[i])
      result = result + temp
      Polynomial.shiftList(selfCopy.lst)
    
    Polynomial.trimList(result.lst)
    return result

  def __truediv__(self, number):
    return Polynomial.divAlg(self, number)[0]

  def __mod__(self, number):
    return Polynomial.divAlg(self, number)[1]

  @staticmethod
  def divAlg(left, right):
    zeroElem  = type(left.lst[0])(0)
    if left.degree() == 0 and right.lst[0] == zeroElem:
      raise ArithmeticError

    remainder = Polynomial([x for x in left.lst])
    quotient = Polynomial([zeroElem])
    quotientSub = [x for x in right.lst]
    quotientSub.pop()
    quotientSub = Polynomial(quotientSub)

    while remainder.degree() > right.degree():
      temp = []
      while len(temp) < remainder.degree() + 1:
        temp.append(zeroElem)
      
      temp[remainder.degree() - right.degree()] = remainder.lst[len(remainder.lst) - 1] / right.lst[len(right.lst) - 1]
      quotient = quotient + Polynomial(temp)
      remainder.lst.pop(len(left.lst) - 1)
      Polynomial.trimList(quotient.lst)
      remainder = remainder - (quotientSub * Polynomial(temp))
    return quotient, remainder

  def __str__(self):
    counter = 0
    result = ""
    for x in self.lst:
      result += f"{x}*x^{counter}"
      counter += 1
      if counter < len(self.lst):
        result += " + "
    return result

  @staticmethod
  def trimList(lst : list):
    if lst == []:
      return
    resType = type(lst[0])
    zero = resType(0)
    
    while len(lst) > 1 and lst[-1] == zero:
      lst.pop()
  
  @staticmethod
  def alignLists(lst1 : list, lst2 : list):
    classType = type(lst1[0])
    while len(lst1) < len(lst2):
      lst1.append(classType(0))
    
    while len(lst2) < len(lst1):
      lst2.append(classType(0))
  
  @staticmethod
  def shiftList(lst : list):
    classType = type(lst[0])
    lst.insert(0, classType(0))
  
  @staticmethod
  def scalarMult(lst, scalar):
    for i in range(len(lst)):
      lst[i] *= scalar