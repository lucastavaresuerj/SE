#define Led_Red 10
#define Led_Green 11
 
void setup ()
{
  pinMode (Led_Red, OUTPUT); 
  pinMode (Led_Green, OUTPUT); 
}
 
void loop () // main program loop
{
  digitalWrite (Led_Red, HIGH); 
  digitalWrite (Led_Green, HIGH); 
  delay (1000); 
  digitalWrite (Led_Red, HIGH); 
  digitalWrite (Led_Green, LOW); 
  delay (1000); 
  digitalWrite (Led_Red, LOW); 
  digitalWrite (Led_Green, HIGH); 
  delay (1000); 
  digitalWrite (Led_Red, LOW); 
  digitalWrite (Led_Green, LOW);
  delay(1000);
}
