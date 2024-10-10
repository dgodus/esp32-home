#define BLYNK_TEMPLATE_ID "el id"
#define BLYNK_TEMPLATE_NAME "Home esp32"
#define BLYNK_AUTH_TOKEN "nuevo token"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Tu configuración WiFi
char ssid[] = "nombre wifi";
char pass[] = "contraseña";

// Definimos el pin para el relé
#define relay_pin 7 

int relay_state = 0;  // Estado inicial del relé (apagado)

// Virtual pin para el botón en la app Blynk
#define button_vpin V1 

//--------------------------------------------------------------------------
// Esta función se llama cada vez que el dispositivo se conecta a Blynk.Cloud
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button_vpin);  // Sincroniza el estado del botón virtual
}

//--------------------------------------------------------------------------
// Esta función se llama cada vez que el estado del Pin Virtual cambia
BLYNK_WRITE(button_vpin) {
  relay_state = param.asInt();  // Lee el estado del botón virtual
  digitalWrite(relay_pin, relay_state);  // Actualiza el relé
  Serial.print("Relay state: ");
  Serial.println(relay_state ? "ON" : "OFF");
}

//--------------------------------------------------------------------------

void setup()
{
  // Consola de depuración
  Serial.begin(115200);

  // Configuramos el pin del relé como salida
  pinMode(relay_pin, OUTPUT);

  // Apagamos el relé al inicio
  digitalWrite(relay_pin, HIGH);

  // Conectamos al WiFi
  connectToWiFi();

  // Iniciamos la conexión a Blynk
  Blynk.begin(auth, ssid, pass);
}

//--------------------------------------------------------------------------

void loop()
{
  Blynk.run();  // Ejecuta las tareas de Blynk
}

//--------------------------------------------------------------------------

void connectToWiFi() {
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, pass);

  // Esperamos hasta 10 segundos para la conexión
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 100) {
    delay(100);  // 100ms por intento, 100 intentos -> 10 segundos
    attempts++;
    Serial.print(".");
  }

  // Verificamos si se conectó exitosamente
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nError al conectar WiFi");
  }
}