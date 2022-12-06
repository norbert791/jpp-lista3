package zad3;

import java.util.ArrayList;
import java.util.List;

public class Polynomial<T extends Field<T>> {
  private List<T> coefficients = null;

  public Polynomial(List<T> coefficients) {
    this.coefficients = new ArrayList<>(coefficients);
    trimList(this.coefficients);
  }

  public Polynomial<T> sum(Polynomial<T> pol) {
    List<T> coefficientsCopy = new ArrayList<>(this.coefficients);
    List<T> polCopy = new ArrayList<>(pol.coefficients);
    List<T> result = new ArrayList<>();
    alignLists(coefficientsCopy, polCopy);

    for (int i = 0; i < polCopy.size(); i++) {
      result.add(coefficientsCopy.get(i).sum(polCopy.get(i)));
    }
    trimList(result);

    return new Polynomial<T>(result);
  }

  public Polynomial<T> negate() {
    List<T> temp = new ArrayList<>();
    for (var it : this.coefficients) {
      temp.add(it.negate());
    }

    return new Polynomial<>(temp);
  }

  public Polynomial<T> diff(Polynomial<T> pol) {
    var temp = pol.negate();
    return this.sum(temp);
  }

  public Polynomial<T> product(Polynomial<T> pol) {
    Polynomial<T> thisCopy = new Polynomial<>(new ArrayList<>(this.coefficients));
    Polynomial<T> result = new Polynomial<>(new ArrayList<>());
    result.coefficients.add(this.coefficients.get(0).zeroElem());
    alignLists(result.coefficients, thisCopy.coefficients);

    for (int i = 0; i < pol.coefficients.size(); i++) {
      var temp = new Polynomial<T>(thisCopy.coefficients);
      scalarMult(temp.coefficients, pol.coefficients.get(i));
      result = result.sum(temp);
      shift(thisCopy.coefficients);
    }

    trimList(result.coefficients);
    return result;
  }

  public Polynomial<T> div(Polynomial<T> right) throws ArithmeticException{
    return divAlgorithm(this, right).first;
  }

  public Polynomial<T> rem(Polynomial<T> right) throws ArithmeticException{
    return divAlgorithm(this, right).second;
  }

  private Pair divAlgorithm(Polynomial<T> left, Polynomial<T> right) {
    var zeroElem = left.coefficients.get(0).zeroElem();
    if (right.degree() == 0 &&
        right.coefficients.get(0).compareTo(zeroElem) == 0) {
      throw new ArithmeticException("Zero division");
    }

    Polynomial<T> remainder = new Polynomial<>(left.coefficients);
    Polynomial<T> quotient = new Polynomial<>(new ArrayList<>());
    quotient.coefficients.add(zeroElem.zeroElem());
    Polynomial<T> quotientSub = new Polynomial<>(right.coefficients);
    quotientSub.coefficients.remove(quotientSub.coefficients.size() - 1);

    while (remainder.degree() >= right.degree()) {
      List<T> temp = new ArrayList<>();
      
      while (temp.size() < remainder.degree() + 1) {
        temp.add(zeroElem.zeroElem());
      }

      temp.set(remainder.degree() - right.degree(),
              remainder.coefficients.get(remainder.coefficients.size() - 1).division(
                right.coefficients.get(right.coefficients.size() - 1)
              ));
      quotient = quotient.sum(new Polynomial<>(temp));
      remainder.coefficients.remove(remainder.coefficients.size() - 1);
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
      result += it.toString() + "*x^" + counter; 
      counter++;
      if (counter < this.coefficients.size()) {result += " + ";}
    }

    return result;
  }

  private void trimList(List<T> t) {
    while (t.size() > 1 && 
           t.get(t.size() - 1).compareTo(t.get(0).zeroElem()) == 0) {
      t.remove(t.size() - 1);
    }
  }

  private void alignLists(List<T> lst1, List<T> lst2) {
    while (lst1.size() < lst2.size()) {
      lst1.add(lst1.get(0).zeroElem());
    }

    while (lst2.size() < lst1.size()) {
      lst2.add(lst2.get(0).zeroElem());
    }
  }

  private void scalarMult(List<T> lst, T scalar) {
    for(int i = 0; i < lst.size(); i++) {
      lst.set(i, lst.get(i).product(scalar));
    }
  }

  private void shift(List<T> lst) {
    lst.add(0, lst.get(0).zeroElem());
  }

  private class Pair {
    public Polynomial<T> first;
    public Polynomial<T> second;
    Pair(Polynomial<T> f, Polynomial<T> s) {
      this.first = f;
      this.second = s;
    }
  }
}
