#include <Arduino.h>
#include <cJSON.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

int a = 0;

// timer
#define pulPin 16 // 脉冲信号引脚
#define dirPin 17 // 方向信号引脚

#define ledchannel 0 // 定时器频道，分16路，高速可以随时改变频率或者定时器溢出，低速只能在定时器下一次溢出后才会改变
#define resolution 8 // 分辨率设置，8位即0-255，此时频率最大160KHz
#define duty 128     // 占空比设置 duty/(2^resolution) *100%
int freq = 800;      // 频率设置
bool dir = 1;        // 0->reversal 1->forward

// dht11
float temper = 0;
float humid = 0;

// wifi
const char *ssid = "*";     // wifi名字
const char *password = "*"; // wifi密码
WiFiClient wifiClient;             // wifi句柄

// mqtt
const char *mqttServer = "*";                                 // MQTT服务器网址
const char *clientId = "*";                                   // MQTT客户端id
const char *mqttUserName = "*";                               // MQTT账号用户名
const char *mqttPassword = "*";                               // MQTT账号密码
const char *pubTopic = "$oc/devices/*/sys/properties/report"; // 发布主题名
const char *subTopic = "$oc/devices/*/sys/commands/#";        // 订阅主题名
PubSubClient mqttClient(wifiClient);                          // mqtt句柄

// dht11
DHT dht(13, DHT11, 1);

// stepping
void stepping_timer_pwm_setup();
void stepping_duty_change(bool cat);

// wifi
void connectWifi();       // 连接wifi
void connectMQTTserver(); // 连接MQTT服务器并订阅信息

// mqtt
void sub_cmd();                                                        // 订阅命令
void receiveCallback(char *topic, byte *payload, unsigned int length); // 订阅回调函数
void pub_dht11();                                                      // 发布温湿度信息

void stepping_timer_pwm_setup()
{
  /*电机驱动引脚*/
  pinMode(pulPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, dir);

  /*PWM生成*/
  ledcSetup(ledchannel, freq, resolution);
  ledcAttachPin(pulPin, ledchannel);
  ledcWrite(ledchannel, 0);
}

void stepping_duty_change(bool cat)
{
  if (cat)
  {
    digitalWrite(dirPin, dir);
    // 0->reversal 1->forward
    if (dir)
    {
      Serial.printf("stepping:direction change,the direction is forward \r\n");
    }
    else
    {
      Serial.printf("stepping:direction change,the direction is reversal \r\n");
    }
  }
  else
  {
    if (freq != 0)
    {
      ledcWrite(ledchannel, duty);
      ledcSetup(ledchannel, freq, resolution);
    }
    else
    {
      ledcWrite(ledchannel, 0);
    }
    Serial.printf("stepping:pwm change,the frequency is 800*%0.3f \r\n", (float)freq / 800);
  }
}

void connectWifi() // ESP连接wifi
{
  WiFi.begin(ssid, password);
  // 等待WiFi连接,成功连接后输出成功信息
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");
  Serial.println("");
}

void connectMQTTserver() // 连接MQTT服务器并订阅信息
{

  if (mqttClient.connect(clientId, mqttUserName, mqttPassword))
  {
    Serial.print("MQTT Server Connected. ClientId: ");
    Serial.println(clientId);
    Serial.print("MQTT Server: ");
    Serial.println(mqttServer);
  }
  else
  {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(5000);
  }
}

void sub_cmd()
{
  if (mqttClient.subscribe(subTopic, 0))
  {
    Serial.print("Subscribed Topic: ");
    Serial.println(subTopic);
  }
  else
  {
    Serial.print("Subscribe Fail...");
  }
}

void receiveCallback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("Callback:deal with the command ==================================================>");

  cJSON *cjson_cmd_all = NULL;
  cJSON *cjson_cmd_paras = NULL;
  cJSON *cjson_cmd_name = NULL;
  cJSON *cjson_cmd_paras_speed = NULL;
  cJSON *cjson_cmd_paras_dir = NULL;
  char *speed = nullptr;
  bool dir_cmd = false;

  char payload_cmd[100];
  for (int i = 0; i < length; i++)
  {
    payload_cmd[i] = (char)payload[i];
  }
  Serial.printf("%s\r\n", payload_cmd);
  Serial.println("");

  cjson_cmd_all = cJSON_Parse(payload_cmd);
  cjson_cmd_name = cJSON_GetObjectItem(cjson_cmd_all, "command_name");
  cjson_cmd_paras = cJSON_GetObjectItem(cjson_cmd_all, "paras");

  if (*(cjson_cmd_name->valuestring) == 's')
  {
    cjson_cmd_paras_speed = cJSON_GetObjectItem(cjson_cmd_paras, "speed");
    speed = cjson_cmd_paras_speed->valuestring;
    Serial.printf("get the speed %s\r\n", speed);
    if (*speed == '0')
    {
      freq = 800 * 0;
      stepping_duty_change(0);
    }
    else if (*speed == '1')
    {
      freq = 800 * 1.000;
      stepping_duty_change(0);
    }
    else if (*speed == '2')
    {
      freq = 800 * 1.500;
      stepping_duty_change(0);
    }
    else if (*speed == '3')
    {
      freq = 800 * 2.000;
      stepping_duty_change(0);
    }
    else
    {
      Serial.println("error:can not set the duty");
    }
  }
  else if (*(cjson_cmd_name->valuestring) == 'd')
  {
    cjson_cmd_paras_dir = cJSON_GetObjectItem(cjson_cmd_paras, "dir");
    dir_cmd = cjson_cmd_paras_dir->valueint;
    dir = dir_cmd;
    // 1->reversal 0->forward
    if (dir)
    {
      Serial.println("get the direction reversal");
      stepping_duty_change(1);
    }
    else
    {
      Serial.println("get the direction forward");
      stepping_duty_change(1);
    }
  }
  else
  {
    char *test = cjson_cmd_name->valuestring;
    Serial.println(test);
    Serial.println("Callback:error,can not get the data");
  }
}

void pub_dht11()
{
  // get the data from dht11
  humid = dht.readHumidity();
  temper = dht.readTemperature();
  float humid_right = 999.99;
  float temper_right = 999.99;
  if (humid < 100 || humid > 0 || temper > 150 || temper < -50)
  {
    humid_right = humid;
    temper_right = temper;
  }
  char humid_str[10];
  char temper_str[10];
  sprintf(humid_str, "%0.2f", humid_right);
  sprintf(temper_str, "%0.2f", temper_right);

  // creat the json
  /* JSON格式为
  {
    "services":[
        {
            "service_id":"stepping",
            "properties":{
                "temper":*,
                "humid":*
            }
        }
    ]
  }
  */
  cJSON *cjson_message_all = NULL;
  cJSON *cjson_message_services_array = NULL;
  cJSON *cjson_message_services_object = NULL;
  cJSON *cjson_message_properties = NULL;
  cjson_message_all = cJSON_CreateObject();
  cjson_message_services_array = cJSON_CreateArray();
  cjson_message_services_object = cJSON_CreateObject();
  cjson_message_properties = cJSON_CreateObject();

  char *cjson_pub = NULL;

  // creat the Basic format of json
  cJSON_AddItemToObject(cjson_message_all, "services", cjson_message_services_array);
  cJSON_AddItemToArray(cjson_message_services_array, cjson_message_services_object);
  cJSON_AddStringToObject(cjson_message_services_object, "service_id", "stepping");
  cJSON_AddItemToObject(cjson_message_services_object, "properties", cjson_message_properties);

  // add the data
  cJSON_AddStringToObject(cjson_message_properties, "temper", temper_str);
  cJSON_AddStringToObject(cjson_message_properties, "humid", humid_str);

  // get the json
  cjson_pub = cJSON_Print(cjson_message_all);

  // 实现ESP向主题发布信息
  if (mqttClient.publish(pubTopic, cjson_pub))
  {
    Serial.println("Publish Topic:");
    Serial.println(pubTopic);
    Serial.println("Publish message:");
    Serial.println(cjson_pub);
  }
  else
  {
    Serial.println("Message Publish Failed.");
  }
}

void setup()
{
  Serial.begin(115200);

  // dht11
  dht.begin();

  // wifi
  WiFi.mode(WIFI_STA); // 设置ESP工作模式为无线终端模式
  connectWifi();       // 连接WiFi

  // MQTT
  mqttClient.setServer(mqttServer, 1883); // 设置MQTT服务器和端口号
  mqttClient.setKeepAlive(60);            // 心跳时间
  mqttClient.setCallback(receiveCallback);
  connectMQTTserver(); // 连接MQTT服务器

  sub_cmd();

  stepping_timer_pwm_setup();
}

void loop()
{

  if (!mqttClient.connected())
  {
    connectMQTTserver();
  }

  // 处理信息以及心跳
  mqttClient.loop();

  if (a == 9)
  {
    Serial.print("\r\n");
    pub_dht11();
    a = 0;
  }
  a++;
  Serial.print(".");
  delay(2000);
}
