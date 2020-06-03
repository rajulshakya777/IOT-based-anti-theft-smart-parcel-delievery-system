#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(17,16);
#include <String.h>
String number = "+917974193042"; // 
int c=0;
 void setup()
{
  pinMode(8,INPUT);
  gprsSerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  delay(500);
}
 
void loop()
{
      //float h = dht.readHumidity();
      //float t = dht.readTemperature();
      int t;
      int h;
      if(digitalRead(8))
      {
        t=8;
        h=8;
          if(c==0)
          {
            c=1;
            Serial.println("sending sms");
            SendMessage();
            delay(1000);
          } 
      }
      else 
      {
        t=75;
        h=75;
      }
      
      delay(500);   
         
      Serial.print("Temperature = ");
      Serial.print(t);
      Serial.println(" °C");
      Serial.print("Humidity = ");
      Serial.print(h);
      Serial.println(" %");    
      
   
 
  Serial.write(gprsSerial.read());

  gprsSerial.println("AT");
  delay(500);

  gprsSerial.println("AT+CPIN?");
  delay(500);

  gprsSerial.println("AT+CREG?");
  delay(500);

  gprsSerial.println("AT+CGATT?");
  delay(500);

  gprsSerial.println("AT+CIPSHUT");
  delay(500);

  gprsSerial.println("AT+CIPSTATUS");
  delay(700);

  gprsSerial.println("AT+CIPMUX=0");
  delay(700);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(500);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(900);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(700);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  delay(900);
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(950);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(900);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=5X842GVZ8EQ9XXOC&field1=" + String(t) +"&field2="+String(h);
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  
  delay(900);
  ShowSerialData();

  gprsSerial.println((char)26);//sending
  delay(900);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  //delay(100);
  ShowSerialData();
   
  
}
void SendMessage()
{
  gprsSerial.println("AT+CMGF=1");
  delay(1000);
  gprsSerial.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  String SMS = "your device has been accessed by someone";
  Serial.println(SMS);
  delay(100);
  gprsSerial.println((char)26);
  delay(1000);
} 
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(950); 
  
}
