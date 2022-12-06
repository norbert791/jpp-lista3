package zad3;

class FloatField implements Field<FloatField> {

  private Float value = Float.valueOf(0.0f);

  public FloatField(Float a) {
    this.value = a;
  }

  @Override
  public int compareTo(FloatField o) {
    return value.compareTo(o.value);
  }

  @Override
  public FloatField sum(FloatField a) throws ArithmeticException {
    return new FloatField(Float.sum(value, a.value));
  }

  @Override
  public FloatField difference(FloatField a) throws ArithmeticException {
    return new FloatField(value.floatValue() * a.value);
  }

  @Override
  public FloatField product(FloatField a) throws ArithmeticException {
    return new FloatField(a.value * this.value); 
  }

  @Override
  public FloatField division(FloatField a) throws ArithmeticException {
    return new FloatField(this.value / a.value);
  }

  @Override
  public FloatField zeroElem() {
    return new FloatField(0.0f);
  }

  @Override
  public FloatField oneElem() {
    return new FloatField(1.0f);
  }

  @Override
  public FloatField negate() {
    return new FloatField(-value);
  }

  @Override
  public FloatField inverse() throws ArithmeticException {
    return new FloatField(1 / value);
  }

  @Override
  public String toString() {
    return this.value.toString();
  }

}