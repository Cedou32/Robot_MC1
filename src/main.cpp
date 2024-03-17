#include "mbed.h"

BufferedSerial pc(PB_6, PB_7); // USBTX et USBRX sont les broches de communication série sur la carte Nucleo STM32F072RB
uint8_t buff[10];

DigitalOut LED(PC_13);

char startMarker[] = "#@+";
char endMarker[] = "?%";
char currentChar;

int main()
{
  pc.set_baud(115200);
  int buffindex = 0;
  while (1)
  {
    LED = buff[7];
    pc.write(buff, sizeof(buff));
    
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
              for (int i = 0; i < 10; i++)
              {
                printf("%d\r\n", buff[i]);
              }
              // Réinitialise l'index du buffer pour la prochaine trame
              buffindex = 0;
              break;
            }
          }
        }
      }
    }
  }
}