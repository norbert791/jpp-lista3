package zad3;

import java.util.ArrayList;
import java.util.List;

public class Polynomial<U, T extends Field<U>> {
  private List<Field<U>> coefficients = null;

  public Polynomial(List<T> coefficients) {
    this.coefficients = new ArrayList<>(coefficients);
    trimList(this.coefficients);
  }

  public Polynomial<U, T> sum(Polynomial<U, T> pol) {
    List<Field<U>> coefficientsCopy = new ArrayList<>(this.coefficients);
    List<Field<U>> polCopy = new ArrayList<>(pol.coefficients);
    List<Field<U>> result = new ArrayList<>();
    alignLists(coefficientsCopy, polCopy);

    for (int i = 0; i < polCopy.size(); i++) {
      result.add(coefficientsCopy.get(i).sum(polCopy.get(i)));
    }
    trimList(result);

    return new Polynomial<U, T>(result);
  }

  public Polynomial<U, T> negate() {
    List<Field<U>> temp = new ArrayList<>();
    for (var it : this.coefficients) {
      temp.add(it.negate());
    }

    return new Polynomial<>(temp);
  }

  public Polynomial<U, T> diff(Polynomial<U, T> pol) {
    var temp = pol.negate();
    return this.sum(temp);
  }

  public Polynomial<U, T> product(Polynomial<U, T> pol) {
    Polynomial<U, T> temp = new Polynomial<>(new ArrayList<>(this.coefficients));
    Polynomial<U, T> result = new Polynomial<>(new ArrayList<>());
    result.coefficients.add(this.coefficients.get(0).zeroElem());
    alignLists(result.coefficients, temp.coefficients);

    for (int i = 0; i < pol.coefficients.size(); i++) {
      scalarMult(temp.coefficients, pol.coefficients.get(i));
      result = result.sum(temp);
      shift(temp.coefficients);
    }

    trimList(result.coefficients);
    return result;
  }

  public Polynomial<U, T> div(Polynomial<U, T> left, Polynomial<U, T> right) throws ArithmeticException{
    return divAlgorithm(left, right).first;
  }

  public Polynomial<U, T> rem(Polynomial<U, T> left, Polynomial<U, T> right) throws ArithmeticException{
    return divAlgorithm(left, right).second;
  }

  private Pair divAlgorithm(Polynomial<U, T> left, Polynomial<U, T> right) {
    if (right.degree() == 0 && right.coefficients.get(0)
                      == right.coefficients.get(0).zeroElem()) {
      throw new ArithmeticException("Zero division");
    }

    Polynomial<U, T> remainder = new Polynomial<>(left.coefficients);
    Polynomial<U, T> quotient = new Polynomial<>(new ArrayList<>());
    quotient.coefficients.add(coefficients.get(0).zeroElem());
    Polynomial<U, T> quotientSub = new Polynomial<>(right.coefficients);
    quotientSub.coefficients.remove(quotientSub.coefficients.size() - 1);

    while (remainder.degree() > right.degree()) {
      List<Field<U>> temp = new ArrayList<>();
      while (temp.size() < remainder.degree() + 1) {
        temp.add(this.coefficients.get(0).zeroElem());
      }

      temp.set(remainder.degree() - right.degree(),
              remainder.coefficients.get(remainder.coefficients.size() - 1).division(
                right.coefficients.get(coefficients.size() - 1)
              ));
      quotient = quotient.sum(new Polynomial<>(temp));
      remainder.coefficients.remove(coefficients.size() - 1);
      trimList(quotient.coefficients);
      remainder = remainder.diff(quotientSub.product(new Polynomial<>(temp)));
    }

    return new Pair(quotient, remainder);
  }

  public int degree() {
    return this.coefficients.size() - 1;
  }

  @Override
  public String toString() {
    String result = "";

    int counter = 0;
    for (var it : this.coefficients) {
      result += it.toString() + "^" + counter; 
    }

    return result;
  }

  private void trimList(List<Field<U>> t) {
    while (t.size() > 1 && 
           t.get(t.size() - 1).compareTo(t.get(0).zeroElem()) == 0) {
      t.remove(t.size() - 1);
    }
  }

  private void alignLists(List<Field<U>> lst1, List<Field<U>> lst2) {
    while (lst1.size() < lst2.size()) {
      lst1.add(lst1.get(0).zeroElem());
    }

    while (lst2.size() < lst1.size()) {
      lst2.add(lst2.get(0).zeroElem());
    }
  }

  private void scalarMult(List<Field<U>> lst, Field<U> scalar) {
    for(int i = 0; i < lst.size(); i++) {
      lst.set(i, lst.get(i).product(scalar));
    }
  }

  private void shift(List<Field<U>> lst) {
    lst.add(0, lst.get(0).zeroElem());
  }

  private class Pair {
    public Polynomial<U, T> first;
    public Polynomial<U, T> second;
    Pair(Polynomial<U, T> f, Polynomial<U, T> s) {
      this.first = f;
      this.second = s;
    }
  }
}
