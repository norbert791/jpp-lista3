package zad3;

public class FiniteModField implements Field<Long> {
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

  @Override
  public final FiniteModField sum(final Field<Long> num) throws ArithmeticException{
    return new FiniteModField((value + num.getValue()) % base, base);
  }

  @Override
  public final FiniteModField difference(final Field<Long> num) throws ArithmeticException {
    return sum(num.negate());
  }

  @Override
  public final FiniteModField product(final Field<Long> num) throws ArithmeticException {
    return new FiniteModField((value * num.getValue()) % base, base);
  }

  @Override
  public final FiniteModField division(final Field<Long> num) throws ArithmeticException {
    return this.product(num.inverse());
  }

  @Override
  public final FiniteModField inverse() throws ArithmeticException {
    long y1 = 0;
    long y2 = 1;
    long a = value;
    long P = base;

    while (a != 1) {
      long q = P / a;
      long newA = P - ((q * a) % P);
      long newP = a;
      long newY2 = y1;
      
      y1 = y2 % P > q ? (y2 % P) - q : P - (q - (y2 % P));
      P = newP;
      y2 = newY2;
      a = newA;
    }

    return new FiniteModField(y1, base);
  }

  @Override
  public final FiniteModField negate() {
    return new FiniteModField(base - value, base);
  }

  @Override
  public final Long getValue() {return value;}
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

  @Override
  public FiniteModField zeroElem() {
    return new FiniteModField(0, this.base);
  }

  @Override
  public FiniteModField oneElem() {
    return new FiniteModField(1, this.base);
  }

  @Override
  public int compareTo(Field<Long> o) {
    return Long.valueOf(this.value).compareTo(o.getValue());
  }

}