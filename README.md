# SmartPlant
<p>
  In the Microcontroller Projects course, taught by Professor Marconi Rodrigues, it was possible to apply knowledge about circuit assembly and programming using microcontrollers such as Arduino and ESP32. As the final project for the course, students were allowed to choose a project to develop. This report describes the design, prototyping, and programming of a "SmartPlant." The main idea of the project is to monitor environmental characteristics through sensors to measure whether factors such as temperature, humidity, and lighting are suitable for the plant's growth and development. As actuators, the prototype should be capable of signaling to the user what the plant needs. Although this is a scaled-down example for the resources available in the course, the monitoring of crops through sensors is an increasingly present trend in various economic sectors. This resource brings various advantages, such as optimized cultivation, weather condition prediction, faster processes, among other utilities that positively impact the development of planting.</p>

## MATERIALS USED
<p>
  For the development of the prototype, the Arduino Uno was chosen. Arduino Uno is a type of microcontroller board widely used in electronics and for prototyping projects. The ATmega328P is the core of the Arduino Uno. The device features 14 digital input/output pins, 6 analog inputs, a 16 MHz crystal oscillator, a USB connection, a power jack, and a reset button. A program for the Arduino Uno is expected to be easy to use and program. It is practical for both beginners and future professionals, who can use it to prototype interactive systems, such as the creation of home automation, robotics, and monitoring systems.
</p>
<img src="https://tse4.mm.bing.net/th?id=OIP.Cy4SMThjodA5uqrw6XUVugHaGh&pid=Api&P=0&h=180" alt="Arduino uno">
<p>
  Sensors were also necessary for monitoring soil moisture, ambient temperature, and local light levels. The soil moisture sensor is a specific electronic device designed to measure the amount of moisture in the soil, allowing it to detect when the soil is dry or wet. The soil moisture sensor typically consists of two metal probes inserted into the soil as electrodes and measures the resistance between these probes. The sensor can determine the moisture level if the resistance is low. High moisture levels lower the resistance between the probes, allowing the sensor to provide accurate readings. The sensor can be systematically used with automated irrigation systems, smart gardens, and plant-oriented projects, ensuring that the plant has access to the necessary water.
</p>
<img src="https://http2.mlstatic.com/sensor-de-umidade-do-solo-higrmetro-ideal-arduino-pic-D_NQ_NP_438225-MLB25397788347_022017-F.jpg" alt="Soil moisture sensor used in the project">
<p>
  An LDR sensor is an electronic component that changes its resistance depending on the amount of light that hits it. The LDR is commonly referred to as a photoresistor, as its highly resistive material in the dark quickly becomes conductive with a reasonably small amount of light. The LDR is an easy-to-use component that can be very effective in detecting varying levels of light. The LDR is one of the most widely used sensors in various projects, such as automatic light control, solar power plants, security control, monitoring, and many others. Therefore, electronic devices can react to changes in ambient light, such as lights turning on at night or the dimming of a display.
</p>
<img src="https://www.electricalelibrary.com/wp-content/uploads/2017/08/LDR-destaque-scaled.jpg" alt="LDR">
<p>
  The DHT11 is a common digital sensor used for measuring temperature and relative humidity. It is a single sensor module that contains a thermistor for temperature measurement and a capacitive humidity sensor for relative humidity. It provides very accurate readings through digital communication and is often used due to its ease of use and low cost. This sensor is very common in home automation projects, environmental control systems, and weather stations to monitor atmospheric conditions or in any system that can automatically adjust electronic devices based on the readings.
</p>
<img src="https://universal-solder.ca/wp-content/uploads/2020/03/1824_1c07a19c-cac8-4643-82a7-8386e17f3b880.jpg" alt="DHT11">
<p>
  To indicate whether the temperature, humidity, and light levels are adequate, it was necessary to set up a system of 9 LEDs, consisting of 3 green, 3 yellow, and 3 red LEDs.
</p>

## METHODOLOGY

<p>
  The first step of the project was to prototype using the Tinkercad platform. Tinkercad is a free, online platform for creating and simulating electronic projects, 3D design, and programming. Ideal for students and educators, Tinkercad features an intuitive and user-friendly interface where users can design electronic circuits, program microcontrollers such as Arduino, and model 3D objects for printing. Thanks to its interactive tools, Tinkercad enhances learning and creation, quickly and practically turning ideas into reality, and thanks to the virtual environment, there is no need for hardware in the initial experience.

The first step was to add the sensors to test and begin developing the program logic. In the figure below, you can see the assembly of the soil moisture sensor.
</p>
<img src="https://i.imgur.com/LPB3nLL.png" alt="soil moisture sensor">
<p>
  To determine if it was working correctly, it was necessary to print the values received from the sensor on the serial monitor. The values are displayed between 0 and 1023. To provide a better user experience, the map function was used. The map() function in Arduino is used to rescale a value from one input range to another output range. With the logic shown below, it was possible to convert the value read by the sensor into a percentage for user visualization.
</p>

```C
int sensorUmidadeSoloPin = A0; // Pino analógico que o sensor está conectado
int sensorUmidadeSoloValue = 0; // Variável para armazenar a leitura do sensor
int umidadePercent = 0; // Variável para armazenar a umidade do solo em porcentagem

void setup() {
  Serial.begin(9600);  
}

void loop() {
  sensorUmidadeSoloValue = analogRead(sensorUmidadeSoloPin);  
  umidadePercent = map(sensorUmidadeSoloValue, 1023, 0, 0, 100);

  Serial.print("Umidade do solo: ");
  Serial.print(umidadePercent);
  Serial.print("%. ");

  delay(2000);  // Aguarda antes de ler novamente
}
```
<p>
  After confirming that the soil moisture sensor was working correctly, it was time to add the temperature sensor. The DHT11 sensor used in the project was not available for prototyping in Tinkercad, so it was necessary to use the sensor available on the platform (TMP). The only practical difference between the sensors is that the DHT11 is connected to a digital input while the TMP is connected to an analog input. Unlike analog sensors, which vary their output voltage proportionally to the reading and are read by analog pins, the DHT11 internally processes the temperature and humidity readings and sends the data already digitized as a sequence of bits. The Arduino receives this sequence through the digital pin, interpreting it to obtain the temperature and humidity values that can be used in the code.
</p>
<img src="https://i.imgur.com/d2tc0Zo.png" alt="soil moisture sensor and DHT11">

```C
#include <DHT.h>

int sensorUmidadeSoloPin = A0; 
int sensorUmidadeSoloValue = 0;
int umidadePercent = 0;
int ldrValue = 0; // Variável para armazenar a leitura do LDR

// ENTRADAS ANALÓGICAS
#define DHTPIN 2        // Pino digital onde o DHT11 está conectado
#define DHTTYPE DHT11   // Tipo do sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  
  dht.begin();          
}

void loop() {
  sensorUmidadeSoloValue = analogRead(sensorUmidadeSoloPin);  
  umidadePercent = map(sensorUmidadeSoloValue, 1023, 0, 0, 100);

  // Leitura do sensor DHT11
  float temperatura = dht.readTemperature();

  Serial.print("Umidade do solo: ");
  Serial.print(umidadePercent);
  Serial.print("%. ");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("°C. ");

  delay(2000);  // Aguarda antes de ler novamente
}

```
<p>
  Through the code above, it was possible to observe the readings from both sensors. After testing to confirm that the readings were being taken correctly, the final sensor, the light sensor, was added. The LDR also has an analog input, and its assembly can be seen in the figure below.
</p>

<img src="https://i.imgur.com/5YOT04G.png" alt="Sensor Assembly">

<p>
  Since all the sensors were already being read correctly through the serial monitor, the project was ready for the next step, which was to create a system to indicate to the user what was wrong with the plant. For this, a scale was established: adequate (green LED), moderate (yellow LED), and alarming (red LED).
</p>

| Condition                                      | Consequence                                          |
| ---------------------------------------------- | ---------------------------------------------------- |
| Soil moisture above 60%                       | Turns on the green LED corresponding to moisture     |
| Soil moisture below 40%                       | Turns on the red LED corresponding to moisture       |
| Soil moisture between 40% and 60%             | Turns on the yellow LED corresponding to moisture    |
| Temperature above 35 degrees or below 20 degrees | Turns on the red LED corresponding to temperature    |
| Temperature above 32 degrees and below 35 degrees | Turns on the green LED corresponding to temperature  |
| Temperature above 27 degrees and below 32 degrees | Turns on the yellow LED corresponding to temperature |
| Light level above 80% or below 30%            | Turns on the red LED corresponding to light          |
| Light level above 70% or below 40%            | Turns on the yellow LED corresponding to light       |
| Light level between 40% and 70%               | Turns on the green LED corresponding to light        |



| Light level above 70% or below 40%   | Turns on the yellow LED corresponding to light   |


| Light level between 40% and 70%   | Turns on the green LED corresponding to light   |

```C
#include <DHT.h>

int sensorUmidadeSoloPin = A0; 
int sensorUmidadeSoloValue = 0;
int umidadePercent = 0;
int ldrValue = 0; // Variável para armazenar a leitura do LDR

// ENTRADAS ANALÓGICAS
  // Controle dos LEDs baseado na luminosidade
  if (luminosidadePercent > 80 || luminosidadePercent < 30) {
    digitalWrite(LED_LUMINOSIDADE_VERMELHO_PIN, HIGH); // Acende o LED para luminosidade extrema
    digitalWrite(LED_LUMINOSIDADE_AMARELO_PIN, LOW);  // Apaga o LED para luminosidade média
    digitalWrite(LED_LUMINOSIDADE_VERDE_PIN, LOW);  // Apaga o LED para luminosidade ok
  } else if (luminosidadePercent > 70 || luminosidadePercent < 40) {
    digitalWrite(LED_LUMINOSIDADE_VERMELHO_PIN, LOW);  // Apaga o LED para luminosidade extrema
    digitalWrite(LED_LUMINOSIDADE_AMARELO_PIN, HIGH); // Acende o LED para luminosidade média
    digitalWrite(LED_LUMINOSIDADE_VERDE_PIN, LOW);  // Apaga o LED para luminosidade ok
  } else {
    digitalWrite(LED_LUMINOSIDADE_VERMELHO_PIN, LOW);  // Apaga o LED para luminosidade extrema
    digitalWrite(LED_LUMINOSIDADE_AMARELO_PIN, LOW);  // Apaga o LED para luminosidade média
    digitalWrite(LED_LUMINOSIDADE_VERDE_PIN, HIGH); // Acende o LED para luminosidade ok
  }

  // Controle dos LEDs baseado na umidade do solo
  if (umidadePercent > 60) {
    digitalWrite(LED_UMIDADE_VERDE_PIN, HIGH);  // Acende o LED umidade excelente
    digitalWrite(LED_UMIDADE_AMARELO_PIN, LOW); // Apaga o LED umidade ok
    digitalWrite(LED_UMIDADE_VERMELHO_PIN, LOW); // Apaga o LED umidade ruim
  } else if (umidadePercent > 39) {
    digitalWrite(LED_UMIDADE_VERDE_PIN, LOW);   // Apaga o LED umidade excelente
    digitalWrite(LED_UMIDADE_AMARELO_PIN, HIGH); // Acende o LED umidade ok
    digitalWrite(LED_UMIDADE_VERMELHO_PIN, LOW); // Apaga o LED umidade ruim
  } else {
    digitalWrite(LED_UMIDADE_VERDE_PIN, LOW);   // Apaga o LED umidade excelente
    digitalWrite(LED_UMIDADE_AMARELO_PIN, LOW); // Apaga o LED umidade ok
    digitalWrite(LED_UMIDADE_VERMELHO_PIN, HIGH); // Acende o LED umidade ruim
  }

  // Controle dos LEDs baseado na temperatura
  if (temperatura > 35 || temperatura < 20) {
    digitalWrite(LED_TEMP_VERMELHO_PIN, HIGH);  // Acende o LED para temperatura extrema
    digitalWrite(LED_TEMP_AMARELO_PIN, LOW);   // Apaga o LED para faixa de temperatura média
    digitalWrite(LED_TEMP_VERDE_PIN, LOW);   // Apaga o LED para faixa de temperatura normal
  } else if ((temperatura >= 32 && temperatura <= 35) || (temperatura >= 20 && temperatura <= 27)) {
    digitalWrite(LED_TEMP_VERMELHO_PIN, LOW);   // Apaga o LED para temperatura extrema
    digitalWrite(LED_TEMP_AMARELO_PIN, HIGH);  // Acende o LED para faixa de temperatura média
    digitalWrite(LED_TEMP_VERDE_PIN, LOW);   // Apaga o LED para faixa de temperatura normal
  } else if (temperatura >= 27 && temperatura <= 32) {
    digitalWrite(LED_TEMP_VERMELHO_PIN, LOW);   // Apaga o LED para temperatura extrema
    digitalWrite(LED_TEMP_AMARELO_PIN, LOW);   // Apaga o LED para faixa de temperatura média
    digitalWrite(LED_TEMP_VERDE_PIN, HIGH);  // Acende o LED para faixa de temperatura normal
  }
```

  The image below shows the final version of the project in Tinkercad. The project can be simulated at this
  [link](https://www.tinkercad.com/things/ilOe2AMdBC2-planta-inteligente?sharecode=Qh9qWKVs8dCI-wgPsy0qEZpM_bc3O0svbLCfrfQMFh0)
  . On the platform, it is possible to simulate all responses based on sensor readings.


<img src="https://i.imgur.com/MjGnKMg.png" alt="Final project">

<p>
  Finally, it was time to implement the warning messages on the serial monitor so that the user could understand what actions to take to help the plant reach the green LED, which indicates an adequate condition. It was necessary to create logic that generated customized messages for each situation.
</p>

| **Situation**                                                                                       | **Solution**                                             |
| --------------------------------------------------------------------------------------------------- | -------------------------------------------------------- |
| Hi, human! How are you? Everything is fine with me, not even thirsty. Soil moisture: 47%. Temperature: 24.70°C. Light level: 41%. | Nothing out of the adequate range                        |
| Hi, human! How are you? It’s too dark, please take me to the sunlight. Soil moisture: 47%. Temperature: 24.70°C. Light level: 25%. | Light level below desired. Increase local light.         |
| Hi, human! How are you? I’m thirsty. Soil moisture: 10%. Temperature: 24.70°C. Light level: 35%. | Soil moisture below desired. Water the plant.           |
| Hi, human! How are you? I’m thirsty. Also, it’s too bright, please take me to the shade. Soil moisture: 14%. Temperature: 24.78°C. Light level: 99%. | Soil moisture below desired and high light level. Water the plant and move it to the shade. |
| Hi, human! How are you? I’m TERRIBLE!!!! SO HOT. Also, it’s too bright, please take me to the shade. Soil moisture: 100%. Temperature: 124.98°C. Light level: 99%. | Temperature above adequate and high light level. Move the plant to a more ventilated location with less light. |
| Hi, human! How are you? I’m TERRIBLE!!!! SO HOT. And on top of that, I’m thirsty. Also, it’s too bright, please take me to the shade. Soil moisture: 14%. Temperature: 124.98°C. Light level: 99%. | Temperature and light level above adequate, soil moisture below desired. Move the plant to a more ventilated location with less light and water the plant. |

```C
 Serial.print("Oi, humano! Tudo bem com você? ");

  bool mensagemAdicional = false;
  bool condicoesFavoraveis = true;

  if (temperatura > 35) {
    Serial.print("Comigo está PÉSSIMO!!!! QUE CALOOOOOOOOOR. ");
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  } 

  if (temperatura < 20) {
    Serial.print("Estou congelando! Muito frio por aqui! ");
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  }

  if (umidadePercent < 30) {
    if (mensagemAdicional) {
      Serial.print("E além disso, ");
    }
    Serial.print("Eu estou com sede. ");
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  }

  if (luminosidadePercent > 80) {
    if (mensagemAdicional) {
      Serial.print("Ainda por cima está muito claro, me leve para a sombra. ");
    } else {
      Serial.print("Está muito claro, me leve para a sombra. ");
    }
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  } else if (luminosidadePercent < 30) {
    if (mensagemAdicional) {
      Serial.print("E além disso, está muito escuro, me leve para tomar um solzinho. ");
    } else {
      Serial.print("Está muito escuro, me leve para tomar um solzinho. ");
    }
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  }

  if (condicoesFavoraveis) {
    Serial.print("Tá tudo bem comigo, nem estou com sede. ");
  }

  Serial.print("Umidade do solo: ");
  Serial.print(umidadePercent);
  Serial.print("%. ");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("°C. ");

  Serial.print("Luminosidade: ");
  Serial.print(luminosidadePercent);
  Serial.print("%. ");
  Serial.println();
```

<p>
  After testing in Tinkercad, it was possible to replicate the project on a breadboard and test it with a real plant, achieving the desired results.
</p>

<img src="https://i.imgur.com/uG8aGb4.jpeg" alt="Final real project">

