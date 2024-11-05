const int pin_led = 5;     
const int pin_pir = 4;   
const int pin_trig = 2;     
const int pin_echo = 3;     
const int pin_buzzer = 6;  

int contagemPessoas = 0;   
bool movimentoDetectado = false;

void setup() {
    Serial.begin(9600);          
    Serial1.begin(9600);         
    pinMode(pin_pir, INPUT); 
    pinMode(pin_trig, OUTPUT); 
    pinMode(pin_echo, INPUT); 
    pinMode(pin_led, OUTPUT);
    pinMode(pin_buzzer, OUTPUT); 
}

void loop() {
    int VerificacaoPir = digitalRead(pin_pir);

    if (VerificacaoPir == HIGH && !movimentoDetectado) {   
        movimentoDetectado = true;

        long duracao, distancia;
        
        
        digitalWrite(pin_trig, LOW);
        delayMicroseconds(2);
        digitalWrite(pin_trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(pin_trig, LOW);
        
        duracao = pulseIn(pin_echo, HIGH);
        distancia = duracao * 0.034 / 2; 

        if (distancia < 50) {  
            contagemPessoas++; 
            
            
            Serial.print("Registro de movimento: ");
            Serial.println(contagemPessoas);

            Serial1.print("Registro de movimento: ");  
            Serial1.println(contagemPessoas);
            
            
            digitalWrite(pin_buzzer, HIGH); 
            delay(500); 
            digitalWrite(pin_buzzer, LOW); 
            
            digitalWrite(pin_led, HIGH); 
            delay(1000); 
            digitalWrite(pin_led, LOW); 
        }
    } else if (VerificacaoPir == LOW) {
        movimentoDetectado = false;  
    }

    delay(200); 
}
