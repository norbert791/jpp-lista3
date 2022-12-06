package zad3;

public interface Field<T> extends Comparable<T>{
  T sum(final T a) throws ArithmeticException;
  T difference(final T a) throws ArithmeticException;
  T product(final T a) throws ArithmeticException;
  T division(final T a) throws ArithmeticException;
  T zeroElem();
  T oneElem();
  T negate();
  T inverse() throws ArithmeticException;
}
