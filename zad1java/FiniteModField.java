package zad1java;

import java.io.Serializable;

public class FiniteModField implements Serializable{
  private long value;
  private final long base;

  public FiniteModField(long value, long base) throws ArithmeticException{
    if (!isPrime(base)) {throw new ArithmeticException("Base must be prime");}
    long temp = base * base;
    temp /= base;
    if (base != temp) {
        throw new ArithmeticException(
            "The base must be less or equal to sqrt(max long)");
    }
    this.value = value;
    this.base = base;
    if (value < 0) {
      this.value = -value;
      this.value %= this.base;
      this.value = this.negate().value;
    }
  }  

  public final FiniteModField increment() {
    value++;
    return this;
  }

  public final FiniteModField decrement() {
    if (value == 0) {value = base - 1;}
    else {return this;}
    return this;
  }
  
  public final FiniteModField sum(final FiniteModField num) throws ArithmeticException{
    verifyBases(num);
    return new FiniteModField((value + num.value) % base, base);
  }

  public final FiniteModField difference(final FiniteModField num) throws ArithmeticException {
    verifyBases(num);
    return sum(num.negate());
  }

  public final FiniteModField product(final FiniteModField num) throws ArithmeticException {
    verifyBases(num);
    return new FiniteModField((value * num.value) % base, base);
  }

  public final FiniteModField division(final FiniteModField num) throws ArithmeticException {
    verifyBases(num);
    return this.product(num.inverse());
  }

  public final FiniteModField inverse() {
    long m = this.base;
    long m0 = m;
    long a = this.value;
    long y = 0;
    long x = 1;

    while (a > 1) {
      long q = a / m;
      long t = m;
      m = a % m; 
      a = t;
      t = y;

      y = x - q * y;
      x = t;
    }

    if (x < 0) {
      x += m0;
    }

    return new FiniteModField(x, base);
  }

  public final FiniteModField negate() {
    return new FiniteModField(base - value, base);
  }

  public final long getValue() {return value;}
  public final long getBase() {return base;}

  private boolean isPrime(long number) {
    if (number < 2) {return false;}
    
    for (long i = 2; i * i <= number; i++) {
      if (number % i == 0) {return false;}
    }

    return true;
  }

  @Override
  public final String toString() {
    return String.format("%d mod %d", value, base);
  }

  private void verifyBases(final FiniteModField num) throws ArithmeticException{
    if (base != num.base) {throw new ArithmeticException("Bases are not compatible");}
  }
}