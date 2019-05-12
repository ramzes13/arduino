ADC_MODE(ADC_VCC);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  int vcc = ESP.getVcc();
  Serial.println(vcc);
  delay(1000);
}
