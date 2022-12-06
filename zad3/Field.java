package zad3;

public interface Field<T> extends Comparable<Field<T>>{
  Field<T> sum(final Field<T> a) throws ArithmeticException;
  Field<T> difference(final Field<T> a) throws ArithmeticException;
  Field<T> product(final Field<T> a) throws ArithmeticException;
  Field<T> division(final Field<T> a) throws ArithmeticException;
  Field<T> zeroElem();
  Field<T> oneElem();
  Field<T> negate();
  Field<T> inverse() throws ArithmeticException;
  T getValue();
}
