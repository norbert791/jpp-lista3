class Polynomial:
  lst = []
  
  def __init__(self, lst):
    if lst == list:
      self.lst = lst
    else:
      self.lst = [lst]

  def degree(self):
    return len(self.lst)
  
  def __add__(self, pol):
    larger = []
    smaller = []
    if self.degree() > pol.degree():
      larger = self.lst 
      smaller = pol.lst
    else:
      larger = pol.lst
      smaller = self.lst
    result = [0 for i in range(len(smaller))]
    for i in range(len(smaller)):
      result[i] = smaller[i] + larger[i]
    return Polynomial(result)
  
  def __neg__(self):
    result = [-x for x in self.lst]
    return Polynomial(result)

  def __sub__(self, number):
    temp = -number
    return self + temp
  
  def __mul__(self, number):
    pass

  @staticmethod
  def karatsubaMult(first : list, second : list):
    if (len(first) == 1):
      return [first[0] * second[0]]
    
    elType = type(first[0])
    first2 = first.copy()
    second2 = second.copy()

    if len(first2) % 2 == 1:
      first2.append(elType(0))


  @staticmethod
  def trimList(lst : list):
    if lst == []:
      return
    resType = type(lst[0])
    zero = resType(0)
    
    while len(lst) > 1 and lst[-1] == zero:
      lst.pop()