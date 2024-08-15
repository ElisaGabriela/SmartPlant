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
![LDR](https://www.electricalelibrary.com/wp-content/uploads/2017/08/LDR-destaque-scaled.jpg)
*Figure 3: LDR.*
<p>
  The DHT11 is a common digital sensor used for measuring temperature and relative humidity. It is a single sensor module that contains a thermistor for temperature measurement and a capacitive humidity sensor for relative humidity. It provides very accurate readings through digital communication and is often used due to its ease of use and low cost. This sensor is very common in home automation projects, environmental control systems, and weather stations to monitor atmospheric conditions or in any system that can automatically adjust electronic devices based on the readings.
</p>
![DHT11](https://universal-solder.ca/wp-content/uploads/2020/03/1824_1c07a19c-cac8-4643-82a7-8386e17f3b880.jpg)
*Figure 4: DHT11*
<p>
  To indicate whether the temperature, humidity, and light levels are adequate, it was necessary to set up a system of 9 LEDs, consisting of 3 green, 3 yellow, and 3 red LEDs.
</p>
## METHODOLOGY
<p>
  The first step of the project was to prototype using the Tinkercad platform. Tinkercad is a free, online platform for creating and simulating electronic projects, 3D design, and programming. Ideal for students and educators, Tinkercad features an intuitive and user-friendly interface where users can design electronic circuits, program microcontrollers such as Arduino, and model 3D objects for printing. Thanks to its interactive tools, Tinkercad enhances learning and creation, quickly and practically turning ideas into reality, and thanks to the virtual environment, there is no need for hardware in the initial experience.

The first step was to add the sensors to test and begin developing the program logic. In Figure 5, you can see the assembly of the soil moisture sensor.
</p>
![soil moisture sensor](https://csg.tinkercad.com/things/gDBs7WkL1Rv/t725.png?rev=1723726053751000000&s=&v=1&type=circuits)
*Figure 5 - Assembly of the soil moisture sensor.*
<p>
  To determine if it was working correctly, it was necessary to print the values received from the sensor on the serial monitor. The values are displayed between 0 and 1023. To provide a better user experience, the map function was used. The map() function in Arduino is used to rescale a value from one input range to another output range. With the logic shown in Figure 6, it was possible to convert the value read by the sensor into a percentage for user visualization.
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

