package zad3;

public class MainFiniteModField {
  public static void main(String[] args) {
    final long base = 7;
    final long val1 = 5;

    FiniteModField num1 = new FiniteModField(val1, base);
    FiniteModField num2 = new FiniteModField(3, base);
    FiniteModField num3 = num1.sum(num2); //
    FiniteModField num2FromNeg = new FiniteModField(-4, base);
    FiniteModField num1FromNeg = new FiniteModField(-val1, base);
    num1FromNeg = num1FromNeg.negate();

    //System.out.println(num3);
    System.out.println(num3.sum(num2));
    System.out.println(num2.difference(num1));
    System.out.println(num2.product(num1));
    System.out.println(num2.division(num1));
    System.out.println("------------------------");
    System.out.println(num3.sum(num2FromNeg));
    System.out.println(num2.difference(num1FromNeg));
    System.out.println(num2.product(num1FromNeg));
    System.out.println(num2.division(num1FromNeg));
  }
}

