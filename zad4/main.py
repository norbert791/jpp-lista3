from Polynomial import Polynomial

if __name__ == "__main__":
  pol1 = Polynomial([1.0, 2.0 ,3.0])
  pol2 = Polynomial([4.0, 3.0, 2.0 ,5.0])
  print(pol1 + pol2)
  print(pol2 - pol1)
  print(pol1 * pol2)
  print(pol2 / pol1)
  print(pol2 % pol1)