package zad3;

class FloatField implements Field<Float> {

  private Float value = Float.valueOf(0.0f);

  public FloatField(Float a) {
    this.value = a;
  }

  @Override
  public int compareTo(Field<Float> o) {
    return value.compareTo(o.getValue());
  }

  @Override
  public Field<Float> sum(Field<Float> a) throws ArithmeticException {
    return new FloatField(Float.sum(value, a.getValue()));
  }

  @Override
  public Field<Float> difference(Field<Float> a) throws ArithmeticException {
    return new FloatField(value.floatValue() * a.getValue());
  }

  @Override
  public Field<Float> product(Field<Float> a) throws ArithmeticException {
    return new FloatField(a.getValue() * this.value); 
  }

  @Override
  public Field<Float> division(Field<Float> a) throws ArithmeticException {
    return new FloatField(a.getValue() * this.value);
  }

  @Override
  public Field<Float> zeroElem() {
    return new FloatField(0.0f);
  }

  @Override
  public Field<Float> oneElem() {
    return new FloatField(1.0f);
  }

  @Override
  public Field<Float> negate() {
    return new FloatField(-value);
  }

  @Override
  public Field<Float> inverse() throws ArithmeticException {
    return new FloatField(1 / value);
  }

  @Override
  public Float getValue() {
    return this.value;
  }

  @Override
  public String toString() {
    return this.value.toString();
  }

}