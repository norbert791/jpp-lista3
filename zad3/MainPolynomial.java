package zad3;

import java.util.ArrayList;
import java.util.List;

public class MainPolynomial {
  public static void main(String[] args) {
    List<FloatField> pol1List = new ArrayList<>();
    List<FloatField> pol2List = new ArrayList<>();
    
    pol1List.add(new FloatField(1.0f));
    pol1List.add(new FloatField(2.0f));
    pol1List.add(new FloatField(3.0f));

    pol2List.add(new FloatField(4.0f));
    pol2List.add(new FloatField(3.0f));
    pol2List.add(new FloatField(2.0f));
    pol2List.add(new FloatField(5.0f));
  
    Polynomial<FloatField> pol1 = new Polynomial<FloatField>(pol1List);
    Polynomial<FloatField> pol2 = new Polynomial<FloatField>(pol2List);

    System.out.println(pol1.sum(pol2));
    System.out.println(pol2.diff(pol1));
    System.out.println(pol1.product(pol2));
    System.out.println(pol2.div(pol1));
    System.out.println(pol2.rem(pol1));
    System.out.println(pol2.div(pol2));
    System.out.println(pol2.rem(pol2));

  }
}
