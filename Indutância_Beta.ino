int sensorPin = A2; // define o pino A2 como entrada
int ledPin = 3;    // define o pino 3 como saída
int val = 0;        // variável para armazenar o valor lido do pino A2
long time1 = 0;     // variável para armazenar o tempo inicial
long time2 = 0;     // variável para armazenar o tempo final
float elapsedTime;  // variável para armazenar o tempo decorrido em segundos
float inductance;   // variável para armazenar o valor da indutância em microhenries

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(sensorPin);  // faz a leitura do pino A2
  if (val > 3) {               // verifica se a tensão lida é maior que 3mV
    digitalWrite(ledPin, HIGH); // liga o LED
    if (time1 == 0) {           // verifica se é o primeiro pulso
      time1 = micros();         // armazena o tempo inicial
    }
  } else {
    digitalWrite(ledPin, LOW);  // desliga o LED
    if (time1 != 0) {           // verifica se é o final do pulso
      time2 = micros();         // armazena o tempo final
      elapsedTime = (time2 - time1) / 1000000.0; // calcula o tempo decorrido em segundos
      inductance = 1.0 / (2.0 * 1e-6 * pow((1/elapsedTime), 2.0) * 4.0 * 3.14159 * 3.14159); // calcula a indutância em microhenries
      Serial.print("Tempo entre os pulsos: ");
      Serial.print(elapsedTime, 6);
      Serial.print(" segundos. Indutancia: ");
      Serial.print(inductance / 1E-6, 2);
      Serial.println(" uH");
      time1 = 0; // reseta o tempo inicial
    }
  }
}
