// Projeto: Interpretador de Sensores Móveis.
// Gerente do Projeto: Rafael Albino Ribeiro.
// Data de Início: 20/10/2018 às 14:03:09
// Data de Fim:    15/01/2019 às 20:02:17
// Tempo aproximado de Projeto: 50 horas.
// Tempo de Teste de Hardware: + 200 horas.
// Versão 1.0
/*
 * Componentes: Visor LCD I2C - Voltagem: 5V
 *              Módulo Data DS3231 - Voltagem: 3,3 - 5V > Anos (de 2000 a 2099) > Sensor de temperatura com ± 3 °C de exatidão > Faixa de temperatura de trabalho: 0 a 40°C 
 *              Sensor DS18B20 - Voltagem: 3 a 5,5V > Mede -55 ºC e máxima de 125 ºC / precisão de 0,5 ºC na faixa de -10 ºC e +85 ºC.
 *              Sensor DHT 22 - Voltagem: 3 a 5V > Mede umidade: 0 a 100% UR > Mede temperatura: -40º a +80ºC > Precisão de ± 0,5 ºC > Tempo de resposta de 2 leituras por segundo.
*/

//____________________________________INICIO_DEFINES____________________________________

#include <Wire.h>              // Biblioteca para comunicação SDA e SCL
#include <LiquidCrystal_I2C.h> // Biblioteca do visor 16x2 com módulo I2C
#include <DS3231.h>            // Biblioteca de Data e Hora DS3231
#include <OneWire.h>           // Biblioteca do sensor DS18B20
#include <DallasTemperature.h> // Biblioteca do sensor DS18B20
#include <DHT.h>               // Biblioteca do Módulo DHT22
#include <DHT_U.h>             // Biblioteca do Módulo DHT22
#include <Adafruit_Sensor.h>   // Biblioteca do Módulo DHT22
#define pinBotao_Menu 5        // Define para o Pino botão de seleção de menu a porta digital 5
#define pinBotao_Escolha 6     // Define para o Pino botão de escolha a porta digital 6
     
//____________________________________FIM_DEFINES_______________________________________

//____________________________________INICIO_VARIÁVEIS_GLOBAIS__________________________

float temperatura;                           // Variável do sensor de temperatura DS18B20
int valor_Botao_Menu, valor_Botao_Escolha;   // Variável para receber o valor binário do Botão.
int sair = 1;                                // Variável de controle do CASE
byte Termometro[8] // Icone de Temperatura

{
B00100,
B01010,
B01010,
B01110,
B01110,
B11111,
B11111,
B01110
};
byte Gota[8] //Icone de Humidade
{
B00100,
B00100,
B01010,
B01010,
B10001,
B10001,
B10001,
B01110,
};
byte setaCima[8] // Icone de seta para cima
{
B00000,
B00100,
B01010,
B10101,
B00100,
B00100,
B00100,
B00000,
};
byte setaBaixo[8] // Icone de seta para baixo
{
B00000,
B00100,
B00100,
B00100,
B10101,
B01010,
B00100,
B00000,
};

byte Ansdles1[8]{  //Icone da Logo Ansdles
B00000, 
B00000,
B00000,
B00000,
B00001,
B00011,
B00110,
B01100,
};

byte Ansdles2[8]{  //Icone da Logo Ansdles
B00110, 
B01100,
B11000,
B10000,
B00000,
B00000,
B00000,
B00001,
}; 

byte Ansdles3[8]{  //Icone da Logo Ansdles
B01100, 
B00110,
B00011,
B00001,
B00000,
B00000,
B00000,
B00000,
};

byte Ansdles4[8]{  //Icone da Logo Ansdles
B00001, 
B00001,
B00001,
B00001,
B10001,
B11001,
B01100,
B00110,
}; 

byte Ansdles5[8]{  //Icone da Logo Ansdles
B01100, 
B00110,
B00011,
B00001,
B00000,
B00000,
B00000,
B10000,
}; 

byte Ansdles6[8]{  //Icone da Logo Ansdles
B00000, 
B00000,
B00000,
B00000,
B10000,
B11000,
B01100,
B00110,
}; 

byte Ansdles7[8]{  //Icone da Logo Ansdles
B00110, 
B01100,
B11000,
B10000,
B00000,
B00000,
B00000,
B00000,
}; 

byte Ansdles8[8]{  //Icone da Logo Ansdles
B10000, 
B10000,
B10000,
B10000,
B10001,
B10011,
B00110,
B01100,
};


//____________________________________FIM_VARIÁVEIS_GLOBAIS_____________________________

//____________________________________INICIO_DECLARAÇÕES________________________________

LiquidCrystal_I2C lcd(0x27,16,2); // Inicializa o display no endereco 0x27
DS3231  rtc(SDA, SCL); // Inicia o DS3231 usando a interface do Hardware
Time  tempo; // Inicia a Estrutura Data-hota
OneWire pino(3); //Inicia o Objeto referente ao pino
DallasTemperature barramento(&pino); // Inicia o objeto do barramento associado ao objeto Pino.
DeviceAddress sensor; // Criar um objeto para um sensor DS18B20 em si.
#define DHTPIN 4               // Define a porta 4 a entrada de informação do sensor DHT22         
#define DHTTYPE DHT22          // Reconhece na biblioteca a classe DHT22
DHT dht(DHTPIN, DHTTYPE); // Define pino e tipo do sensor DHT


//____________________________________FIM_DECLARAÇÕES___________________________________

//____________________________________INICIO_SETUP___________________________________________________________________________________________________________________________________________________________________

void setup() {

//INICIO_LCD_____________________________________________________________________________ 
  Serial.begin(9600);
  lcd.init();                 // Inicializando o LCD
  lcd.backlight();            // Ligando o BackLight do LCD
  lcd.clear();
  lcd.createChar(5,Ansdles1);  // Criar o Vetor Char
  lcd.createChar(6,Ansdles2);  // Criar o Vetor Char
  lcd.createChar(7,Ansdles3);  // Criar o Vetor Char
  lcd.createChar(8,Ansdles4);  // Criar o Vetor Char
  lcd.createChar(9,Ansdles5);  // Criar o Vetor Char 
  lcd.createChar(10,Ansdles6); // Criar o Vetor Char
  lcd.createChar(11,Ansdles7); // Criar o Vetor Char
  lcd.createChar(12,Ansdles8); // Criar o Vetor Char 
  lcd.setCursor(10,0);      
  lcd.print("V 1.1");
  
  lcd.setCursor(7,1);         // Configura o visor para X coluna e na X Linha.   (7,1) == (Coluna,Linha);
  lcd.print("<Ansdles>");     // Exibindo no LED <Ansdles>
  lcd.setCursor(1,0); 
  lcd.write(5);
  lcd.write(6);
  lcd.print("_");
  lcd.write(9);
  lcd.write(10); 
  lcd.setCursor(1,1); 
  lcd.write(7);
  lcd.write(8);
  lcd.print("-");
  lcd.write(12);
  lcd.write(11);
  delay(3000);
  lcd.clear();
//FIM_LCD_______________________________________________________________________________ 
  
//INICIO_DATA_&_HORA_____________________________________________________________________  

  rtc.begin(); // Inicializa o objeto rtc
  // As seguintes linhas podem ser usadas para configurar a data e hora desde que esteja fora de modo comentário
  //rtc.setDOW(MONDAY);      // Configura Dia da semana SÁBADO
  //rtc.setTime(06, 42, 15);     // Configura a hora 14:03:09 (24hr format)
  //rtc.setDate(04, 11, 2019);   // Configura a data para 23 de outubro 2018
  
//FIM_DATA_&_HORA_______________________________________________________________________

//INICIO_DS18B20________________________________________________________________________

barramento.begin(); // Inicia o barramento
barramento.getAddress(sensor, 0); // Armazena o endereço no objeto sensor no indice 0

//FIM_DS18B20___________________________________________________________________________

//INICIO_ICONS__________________________________________________________________________

lcd.createChar(1,Termometro); // Criar o Vetor Char do Termometro
lcd.createChar(2,Gota);       // Criar o Vetor Char da Gota
lcd.createChar(3,setaCima);   // Criar o Vetor Char da Seta para Cima
lcd.createChar(4,setaBaixo);  // Criar o Vetor Char da Seta para Baixo

//FIM_ICONS_____________________________________________________________________________

//INICIO_DHT22__________________________________________________________________________

dht.begin(); // Inicia o sensor dht22

//FIM_DHT22_____________________________________________________________________________

//INICIO_BOTÕES_________________________________________________________________________

pinMode(pinBotao_Menu, INPUT_PULLUP);      // Inicializa o botão e ativa o resistor interno para impedir oscilação da porta.
pinMode(pinBotao_Escolha, INPUT_PULLUP);   // Inicializa o botão e ativa o resistor interno para impedir oscilação da porta.

//FIM_BOTÕES____________________________________________________________________________
}
//____________________________________FIM_SETUP________________________________________________________________________________________________________________________________________________________________________

//____________________________________INICIO_LOOP______________________________________________________________________________________________________________________________________________________________________
void loop() {


//INICIO_DATA_&_HORA____________________________________________________________________
 
  tempo = rtc.getTime();          // Obtem a data do DS3231
  lcd.setCursor(0,0);             // Configura a a posição de impressão da informação em coluna e linha
  lcd.print(rtc.getTimeStr());
  lcd.print(" - ");
  lcd.print(tempo.date, DEC);     // Imprime o dia do mês
  lcd.print("/");
  lcd.print(tempo.mon, DEC);      // Imprime o mês do ano
            
//FIM_DATA_&_HORA_______________________________________________________________________

//INICIO_DHT22__________________________________________________________________________

  lcd.setCursor(0,1);                  // Configura a a posição de impressão da informação em coluna e linha
  lcd.write(1);                        // Imprimi o termometro.
  lcd.print(dht.readTemperature(),1);  // Imprime a temperatura do sensor DHT22
  lcd.print((char)223);                // Imprimi o º
  lcd.print("C");
  lcd.print(" - ");
  lcd.write(2);                       // Imprimi a humidade.
  lcd.print(dht.readHumidity(),1);     // Imprime a humidade do sensor DHT22
  lcd.print("%");
  delay(1000);                         // Pausa o programa em 1 segundo
           
            
//FIM_DHT22_____________________________________________________________________________

//INICIO_BOTÕES_________________________________________________________________________

 valor_Botao_Menu = digitalRead(pinBotao_Menu);        // Botao menu tenta receber valor do botão
 valor_Botao_Escolha = digitalRead(pinBotao_Escolha);  // Botao escolha tenta receber valor do botão
//Serial.println(valu);

//FIM_BOTÕES____________________________________________________________________________

//INICIO_MENU______________________________________________________________________________________________________________________________________________________
if(valor_Botao_Menu == 0){   // Testa se o valor do botão é igual a 0 e se for ele entra na condição.
  do{                        // Inicio do While.
     switch(sair){           // Escolhe o menu.
        case 1:
          //INICIO_SENSOR_TEMPERATURA_DS18B20_____________________________________________________
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("Sensor DS18B20");
          lcd.setCursor(2,1);
          lcd.print("Iniciando...");
          delay(2000);
          lcd.clear();
          do{                                             // Inicio do While.
          barramento.requestTemperatures();               // Requisita a temperatura do sensor
          temperatura = barramento.getTempC(sensor);      // Copia o dado para a variável temperatura
          lcd.setCursor(0,0);                             // Configura a a posição de impressão da informação em coluna e linha
          lcd.print("Temperatura  Liq");
          lcd.setCursor(4,1);
          lcd.write(1);                                   // Imprimi o termometro.
          lcd.print(" ");
          lcd.print(temperatura,1);                       // Imprimi a temperatura com uma casa decimal (variavel, n de casas)
          lcd.print((char)223);                           // Imprimi o º
          lcd.print("C");
          valor_Botao_Menu = digitalRead(pinBotao_Menu);  // Botao menu tenta receber valor do botão
          }while(valor_Botao_Menu != 0);                  // Fim do While.
          //valor_Botao_Menu = 1;
          sair++;                                         // Variável sair recebe incremento para ir para o próximo case.
          //FIM_SENSOR_TEMPERATURA_DS18B20________________________________________________________
        //case 2:
          //INICIO_CRONÔMETRO_____________________________________________________________________
        case 2:
          lcd.clear();                                    // Limpa Tela
          lcd.setCursor(3,0);                             // Configura a a posição de impressão da informação em coluna e linha
          lcd.print("Cronometro");
          lcd.setCursor(2,1);
          lcd.print("Iniciando...");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);                             // Configura a a posição de impressão da informação em coluna e linha
          lcd.print("Iniciar: ?");
          lcd.setCursor(2,1);
          lcd.print("0:0:0");
          do{                                             // Inicio do While.
          if(valor_Botao_Escolha == 0){
            lcd.clear();
            delay(300);                        // Espera por 0,3 segundos para o dedo do usuário sair do botão físico.
            unsigned int centSec;              // Cria variável de números positivos em centésimo de segundos.
            unsigned int Sec;                  // Cria variável de números positivos em segundos.
            unsigned int Min;                  // Cria variável de números positivos em minutos.
            centSec = 2;                       // Configura variável de centésimo de segundos para 0,2 centésimos para compensar a Espera por 0,3 segundos para o dedo do usuário sair do botão físico.
            Sec = 0;                           // Configura variável de segundos em 0s.
            Min =0;                            // Configura variável de minutos em 0s.
              do{                                         // Inicio do While.
                 if(centSec >= 9){             // Testa se varável centésimo de segundos é igual ou maior que 9s.
                   Sec++;                      // Adiciona 1 segundo na variável segundo.
                   centSec = 0;                // Zera a variável centésimo de segundos.
                 }
                 if(Sec >= 59){                // Testa se varável segundo é igual ou maior que 59s.
                   Min++;                      // Adiciona 1 minuto na variável minuto.
                   Sec = 0;                    // Zera a variável segundos.
                 }
                 valor_Botao_Escolha = digitalRead(pinBotao_Escolha);
                 if(valor_Botao_Escolha == 0){
                    lcd.clear();
                    do{
                       lcd.setCursor(0,0);                                    // Configura a posição de impressão da informação em coluna e linha.
                       lcd.print("Pausado:");
                       lcd.setCursor(2,1);
                       lcd.print(Min);                                        // Imprime o valor da variável minuto.
                       lcd.print(":");
                       lcd.print(Sec);                                        // Imprime o valor da variável segundo.
                       lcd.print(":");
                       lcd.print(centSec);                                    // Imprime o valor da variável centésimo de segundo.
                       delay(200);                                            // Espera por 0,2 segundos para o dedo do usuário sair do botão físico.
                       valor_Botao_Escolha = digitalRead(pinBotao_Escolha);   // variável do botão escolha recebe o valor do botão físico.
                    }while(valor_Botao_Escolha != 0);                         // Testa se o valor da variável botão escolha é diferente de 0.
                    delay(200);                                               // Espera por 0,2 segundos para o dedo do usuário sair do botão físico.
                    centSec = centSec + 2;                                    // A variável centésimo de segundo recebe mais 2 segundos pelo atraso do Delay(200) do botão fisíco no comando acima.
                 }
              
                 centSec++;                                      // Soma-se 1 segundo a variável centésimo de segundo.
                 lcd.setCursor(0,0);                             // Configura a a posição de impressão da informação em coluna e linha.
                 lcd.print("Iniciado:");
                 lcd.setCursor(2,1);
                 lcd.print(Min);                                 // Imprime o valor da variável minuto.
                 lcd.print(":");
                 lcd.print(Sec);                                 // Imprime o valor da variável segundo.
                 lcd.print(":");
                 lcd.print(centSec);                             // Imprime o valor da variável centésimo de segundo.
                 valor_Botao_Menu = digitalRead(pinBotao_Menu);  // variável do botão menu recebe o valor do botão físico.
                 delay(100);                                     // Adiciona a lógica de contar de 0,101 em 0,101 segundos para funcionar como cronometro de precisão 0,1 segunds.
                 lcd.clear(); 
              }while(valor_Botao_Menu != 0);                     // Testa se o valor da variável botão menu é diferente de 0.
          }
          valor_Botao_Menu = digitalRead(pinBotao_Menu);         // Botao menu tenta receber valor do botão
          valor_Botao_Escolha = digitalRead(pinBotao_Escolha);   // Botao menu tenta receber valor do botão
          }while(valor_Botao_Menu != 0);                         // Fim do While.
          sair = 0;                                              // Variável sair recebe valor 0 para sair do Looping e retornar ao inicio.
          //FIM_CRONÔMETRO________________________________________________________________________________  
     }                // FIM_Switch
  }while(sair != 0);  // Fim do While.
}                     // Fim_IF
sair = 1;             // Variável sair recebe valor 1 para poder entrar novamente no Looping do primeiro while que é o menu.
//FIM_MENU__________________________________________________________________________________________________________________________________________________________


/*unsigned int tempp = millis();
if(tempp == 100000){
  lcd.clear();
  tempp = 0;
}*/
}


//____________________________________FIM_LOOP_________________________________________


//____________________________________FUNÇÕES_DO_LCD___________________________________
// void clear();                            LIMPA TELA
// void home();
// void noDisplay();                        
// void display();
// void noBlink();
// void blink();
// void noCursor();
// void cursor();
// void scrollDisplayLeft();
// void scrollDisplayRight();
// void printLeft();
// void printRight();
// void leftToRight();
// void rightToLeft();
// void shiftIncrement();
// void shiftDecrement();
// void noBacklight();                       LIGA O LED
// void backlight();                         DESLIGA O LED
// void autoscroll();
// void noAutoscroll(); 
// void createChar(uint8_t, uint8_t[]);
// void setCursor(uint8_t, uint8_t); 
//____________________________________FUNÇÕES_DO_LCD___________________________________

 
