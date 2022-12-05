
class FiniteModField:
  def __init__(self, value : int, base : int):
    if not self.__isPrime(base):
      raise ArithmeticError("Base is not prime")
    if type(value) is not int or type(base) is not int:
      raise ArithmeticError("Base or value are not ints")
    self.__value = self.__absMod(value, base)
    self.__base = base

  def getBase(self) -> int:
    return self.__base

  def getValue(self) -> int:
    return self.__value

  def __add__(self, number):
    self.__verifyNumber(number)
    return FiniteModField((self.__value + number.getValue()) % self.__base, self.__base)

  def __neg__(self):
    return FiniteModField(self.__base - self.__value, self.__base)

  def __sub__(self, number):
    self.__verifyNumber(number)
    temp = -number
    return self + temp

  def __mul__(self, number):
    self.__verifyNumber(number)
    return FiniteModField(self.__value + self, self.__base)

  def __truediv__(self, number):
    self.__verifyNumber(number)
    temp = number.inverse()
    return self * temp

  def __isPrime(number: int) -> bool:
    if number < 2:
      return False
    i = 2
    while i * i <= number:
      if number % i == 0:
        return False
      i += 1
    return True

  def __absMod(self, val : int, base : int) -> int:
    if val < 0:
      val = (-val) % base
      val = base - val
    else:
      val %= base
    return val
  
  def __verifyNumber(self, number) -> None:
    if number.getBase() != self.__base:
      raise ArithmeticError("Operation of two numbers of different bases is illegal")
  
  def inverse(self, number):
    m = self.__base
    m0 = m
    a = self.__value
    y = 0
    x = 1

    while (a > 1):
      q = a / m
      t = m
      m = a % m
      a = t
      t = y

      y = x - q * y
      x = t
    

    if (x < 0):
      x += m0
    

    return FiniteModField(x, self.__base)