#include "mbed.h"

BufferedSerial pc(PB_6, PA_10);
uint8_t buff[10];

uint8_t valueX;
uint8_t valueY;

DigitalOut LED_C(D3);
DigitalOut LED_XD(D4);
DigitalOut LED_XG(D5);
DigitalOut LED_YH(D6);
DigitalOut LED_YB(D7);

char startMarker[] = "#@+";
char endMarker[] = "?%";
char currentChar;

int main()
{
  pc.set_baud(115200);
  int buffindex = 0;
  while (1)
  {
    if (pc.readable())
    {

      pc.read(&currentChar, 1);

      if (currentChar == startMarker[buffindex % 3])
      {
        printf("Test1\r\n");
        buff[buffindex++] = currentChar;

        if (buffindex % 3 == 0)
        {
          printf("Test2\r\n");
          while (pc.readable() && buffindex < 10)
          {
            printf("Test3\r\n");
            pc.read(&currentChar, 1);
            buff[buffindex++] = currentChar;

            // Vérifie si le caractère actuel correspond à la fin de la trame
            if (currentChar == endMarker[(buffindex - 3) % 2])
            {
              printf("Test4\r\n");
              for(int i = 0; i<10; i++){
                printf("%d\r\n",buff[i]);
              }
              // Réinitialise l'index du buffer pour la prochaine trame
              buffindex = 0;
              break;
            }
          }
        }
      }

      if (buff[3] >= 85 && buff[3] < 170 && buff[4] >= 85 && buff[4] < 170)
      {
        LED_C = 1;
        LED_XD = 0;
        LED_XG = 0;
        LED_YH = 0;
        LED_YB = 0;
      }
      else if (buff[3] >= 0 && buff[3] < 85)
      {
        LED_C = 0;
        LED_XD = 1;
        LED_XG = 0;
        LED_YH = 0;
        LED_YB = 0;
      }
      else if (buff[3] >= 170 && buff[3] < 256)
      {
        LED_C = 0;
        LED_XD = 0;
        LED_XG = 1;
        LED_YH = 0;
        LED_YB = 0;
      }
      else if (buff[4] >= 0 && buff[4] < 85)
      {
        LED_C = 0;
        LED_XD = 0;
        LED_XG = 0;
        LED_YH = 0;
        LED_YB = 1;
      }
      else if (buff[4] >= 170 && buff[4] < 256)
      {
        LED_C = 0;
        LED_XD = 0;
        LED_XG = 0;
        LED_YH = 1;
        LED_YB = 0;
      }
    }
  }
}