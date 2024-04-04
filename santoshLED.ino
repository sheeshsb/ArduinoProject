int val;
int led=0; // Initialize LED state to off (LOW)
void setup() {
  pinMode(7, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
digitalWrite(7,LOW);
}

void loop() {
  val = analogRead(A0);
  Serial.println(val);

if(val<435 && led==0){

  digitalWrite(7,HIGH);
  led=1;
  delay(1000);
}

else if(val<435 && led==1){

  digitalWrite(7,LOW);
  led=0;
  delay(1000);
}





}
