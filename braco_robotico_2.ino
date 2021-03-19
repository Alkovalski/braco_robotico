#include <Servo.h>

const int sw = A3;
const int y = A5; //sobe
const int x = A4; //gira
const int z = A2; //ombro
const int g = A1; //garra

Servo motores[4];                                           //sobe, ombro, garra e gira / 8, 9, 10, 11 / essa é a ordem dos motores
int pinosServ[4] = {8, 9, 10, 11};
float valor[4] = {90, 180, 90, 100};                        //angulos: y, z, garra e x

void setup() {
  int i = 0;
  while (i != 5) {                                          //declaração dos servos
    motores[i].attach(pinosServ[i]);
    i++;
  }
  Serial.begin(9600);
  pinMode(g, INPUT);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(z, INPUT);
}                                                           //coloca analógicos como INPUT

void dobras(int porta, int servo) {                         //função necessaria para funcionamento, porta é analogica e servo é seu numero na matrix motores
  int valorx = ((analogRead(porta) - 24) / 100) + 1;        //aqui temos aR(porta) - 24 por causa do valor maximo de 1024, /100 para cair pra decimal, +1 pra não cair como 10

  if (valorx < 5 || valorx > 5) {                           //se o valor do joystick é maior que 5 ou menor que 5
    valorx = (valorx - 5.5) / 1;                            // divisão por 1 para arredondar para numero inteiro
    valor[servo] -= valorx;
  }
  if (valor[servo] < 0) {                                   //se o novo valor da posição do servo for menor que zero, igualar a zero
    valor[servo] = 0;
  } else {
    if (valor[servo] > 180){                                //se o novo valor da posição do servo for maior que 180m igualar a 180
      valor[servo] = 180;
    }
  }
  Serial.println(valorx);                                   //printar valor final do joystick, para debugging
  motores[servo].write(valor[servo]);                       //move o servo para a nova posição
}

void loop() {//sobe, ombro, garra e gira
  dobras(x, 3);
  dobras(y, 0);
  dobras(z, 1);
  dobras(g, 2);
}
