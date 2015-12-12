/*

        R2D2HS
  (c) HIRUDI/SICNOVA3D
        GPL v3

 This programs controls remotely the printbot R2D2HS.
 It's derived from:

    + Alejandro Alijarde and Diego Jarauta

 */
// Library for working with servos

#include <Servo.h>


//Creamos dos variables para almacenar un caracter (char) y un numero (int)
char data;
int state;

int ledPin = 13;
//led for visualization (use 13 for built-in led)

int speakerPin = 12;
//speaker connected to one of the PWM ports



//Ahora creamos un par de objetos "servo" para que podamos trabajar con ellos.
Servo servoL;
Servo servoR;
Servo miniservo;
// DEFINE

    #define c 261
    #define d 294
    #define e 329
    #define f 349
    #define g 391
    #define gS 415
    #define a 440
    #define aS 455
    #define b 466
    #define cH 523
    #define cSH 554
    #define dH 587
    #define dSH 622
    #define eH 659
    #define fH 698
    #define fSH 740
    #define gH 784
    #define gSH 830
    #define aH 880
    //frequencies for the tones we're going to use
    //used http://home.mit.bme.hu/~bako/tonecalc/tonecalc.htm to get these





//Ahora preparamos nuestra placa freaduino
void setup() {
  Serial.begin(38400);
  disable();

    pinMode(ledPin, OUTPUT);
  // sets the ledPin to be an output
  pinMode(speakerPin, OUTPUT);
  //sets the speakerPin to be an output

}

// Indicamos los pines de los servos
void enable(){
  servoR.attach(9);
  servoL.attach(6);
  miniservo.attach(10);
}

void disable()
{
    servoR.detach();
    servoL.detach();
}

// Creamos la funcion para parar
void stop(){
  //digitalWrite (12, LOW);
  disable();
  delay(10);
}

// Creamos la funcion para avanzar
void forward(){
enable();
  digitalWrite (12, LOW);  //Ponemos en estado bajo el pin 12 para un posterior giro hacia adelante
  servoL.write(0);        //Con estos valores el robot avanzara
  servoR.write(180);
  delay(10);
}

// Creamos la funcion para retroceder
void backward(){
enable();
  servoL.write(180);          //Con estos valores el robot retrocedera
  servoR.write(0);
  digitalWrite (12, HIGH);    //Ponemos en estado alto el pin 12 para un posterior giro hacia atras
  delay(10);
}

// Creamos la funcion que girara a la derecha
void right(){
enable();
  if (digitalRead(12)){    //Leemos el estado del pin 12, si esta activo girara retrocediendo
    servoL.write(0);
    servoR.write(80);
    delay(10);
  }
  else{                   //Y si esta desactivado girara avanzando
    servoL.write(55);
    servoR.write(100);
    delay(10);
  }
}

//Creamos la funcion que girara a la izquierda
void left()
{
enable();
  if (digitalRead(12)) //Leemos el estado del pin 12, si esta activo girara retrocediendo
  {
    servoL.write(100);
    servoR.write(180);
    delay(10);
  }
  else
  {                  //Y si esta desactivado girara avanzando
    servoL.write(80);
    servoR.write(135);
    delay(10);
  }
}


void head_right()
{
  miniservo.write(0);
  delay(10);
}

void head_left()
{
  miniservo.write(180);
  delay(10);
}

void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{
    digitalWrite(ledPin, HIGH);
    //use led to visualize the notes being played

    int x;
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)
    {
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
    }

    digitalWrite(ledPin, LOW);
    //set led back to low

    delay(20);
    //a little delay to make all notes sound separate
}

void march()
{
//while(Serial.available() > 0){
    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used 500 ms for a quart note

    beep(speakerPin, a, 500);
    beep(speakerPin, a, 500);
    beep(speakerPin, a, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);

    beep(speakerPin, a, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
    beep(speakerPin, a, 1000);
    //first bit

    beep(speakerPin, eH, 500);
    beep(speakerPin, eH, 500);
    beep(speakerPin, eH, 500);
    beep(speakerPin, fH, 350);
    beep(speakerPin, cH, 150);

    beep(speakerPin, gS, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
    beep(speakerPin, a, 1000);
    /*
    //second bit...

    beep(speakerPin, aH, 500);
    beep(speakerPin, a, 350);
    beep(speakerPin, a, 150);
    beep(speakerPin, aH, 500);
    beep(speakerPin, gSH, 250);
    beep(speakerPin, gH, 250);

    beep(speakerPin, fSH, 125);
    beep(speakerPin, fH, 125);
    beep(speakerPin, fSH, 250);
    delay(250);
    beep(speakerPin, aS, 250);
    beep(speakerPin, dSH, 500);
    beep(speakerPin, dH, 250);
    beep(speakerPin, cSH, 250);
    //start of the interesting bit

    beep(speakerPin, cH, 125);
    beep(speakerPin, b, 125);
    beep(speakerPin, cH, 250);
    delay(250);
    beep(speakerPin, f, 125);
    beep(speakerPin, gS, 500);
    beep(speakerPin, f, 375);
    beep(speakerPin, a, 125);

    beep(speakerPin, cH, 500);
    beep(speakerPin, a, 375);
    beep(speakerPin, cH, 125);
    beep(speakerPin, eH, 1000);
    //more interesting stuff (this doesn't quite get it right somehow)
/*
    beep(speakerPin, aH, 500);
    beep(speakerPin, a, 350);
    beep(speakerPin, a, 150);
    beep(speakerPin, aH, 500);
    beep(speakerPin, gSH, 250);
    beep(speakerPin, gH, 250);

    beep(speakerPin, fSH, 125);
    beep(speakerPin, fH, 125);
    beep(speakerPin, fSH, 250);
    delay(250);
    beep(speakerPin, aS, 250);
    beep(speakerPin, dSH, 500);
    beep(speakerPin, dH, 250);
    beep(speakerPin, cSH, 250);
    //repeat... repeat

    beep(speakerPin, cH, 125);
    beep(speakerPin, b, 125);
    beep(speakerPin, cH, 250);
    delay(250);
    beep(speakerPin, f, 250);
    beep(speakerPin, gS, 500);
    beep(speakerPin, f, 375);
    beep(speakerPin, cH, 125);

    beep(speakerPin, a, 500);
    beep(speakerPin, f, 375);
    beep(speakerPin, c, 125);
    beep(speakerPin, a, 1000);
    */
    //and we're done \รณ/
 //   }
}






//Ahora entramos en el nucleo del programa, donde utilizamos las funciones anteriormente creadas
void loop() {
  data = Serial.read();  //Leemos el dato que nos envia el bluetooth y lo almacenamos en la variable
  switch (data){
  case 'a':              //Si en la variable tenemos una "g" ejecutaremos la funcion avanzar
    forward();
    break;
  case 'b':              //Si en la variable tenemos una "h" ejecutaremos la funcion girar izquierda
    left ();
    break;
  case 'c':              //Si en la variable tenemos una "i" ejecutaremos la funcion parar
    stop ();
    break;
  case 'd':              //Si en la variable tenemos una "j" ejecutaremos la funcion girar derecha
    right();
    break;
  case 'e':              //Si en la variable tenemos una "k" ejecutaremos la funcion retroceder
    backward();
    break;
  case 'f':              //Si en la variable tenemos una "k" ejecutaremos la funcion retroceder
    head_left();
    break;
  case 'g':              //Si en la variable tenemos una "k" ejecutaremos la funcion retroceder
    march();
    break;
  case 'h':              //Si en la variable tenemos una "k" ejecutaremos la funcion retroceder
    head_right();
    break;
  case 'i':              //Si en la variable tenemos una "n" en la variable "estado" grabaremos un "0" y saldra del bucle manual.
    state = 0;
    break;
}
}


