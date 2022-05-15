//for the beggining we will transfer all the characters into upperstrings to minimize our future work
#include <stdio.h>
#include <unistd.h>
#define MAX_SIZE 1024 // Maximum string size
#define DOT_DUR 2
#define DASH_DUR 4
#define PAUSE_DUR 100000

#include <string.h>
#include <ao/ao.h>
#include <math.h>
#define BUF_SIZE 8192

int play_sound(int dur)
{

        ao_device *device;
        ao_sample_format format;
        int default_driver;
        char *buffer;
        int buf_size;
        int sample;
        float freq = 440.0;
        int i;
        int duration = 8192;

        ao_initialize();

        default_driver = ao_default_driver_id();

        memset(&format, 0, sizeof(format));
        format.bits = 16;
        format.channels = 2;
        format.rate = 44100;
        format.byte_format = AO_FMT_LITTLE;

        device = ao_open_live(default_driver, &format, NULL /* no options */);
        if (device == NULL) {
                fprintf(stderr, "Error opening device.\n");
                return 1;
        }

        buf_size = format.bits/8 * format.channels * format.rate;
        buffer = calloc(buf_size,
                        sizeof(char));

        for (i = 0; i < format.rate; i++) {
                sample = (int)(0.75 * 32768.0 *
                        sin(2 * M_PI * freq * ((float) i/format.rate)));

                /* Put the same stuff in left and right channel */
                buffer[4*i] = buffer[4*i+2] = sample & 0xff;
                buffer[4*i+1] = buffer[4*i+3] = (sample >> 8) & 0xff;
        }

        ao_play(device, buffer, duration * dur);
        ao_close(device);
        ao_shutdown();

	return 0;
}

int dot(){
	play_sound(DOT_DUR); pause();
}

int dash(){
	play_sound(DASH_DUR); pause();
}

int pause(){
	usleep(PAUSE_DUR);
}

char conv_to_up(int x){
        /*
         * If current character is lowercase alphabet then
         * convert it to uppercase.
         */
        if(x>='a' && x<='z')
        {
            x = x - ('a'-'A');
        }

	return x;
}


//start of the morse convertion
char convert(char x) {
 switch(x) {
  case 'A':
   printf(".- "); pause(); dot(); dash();
   break;

  case 'B':
   printf("-... "); pause(); dash(); dot(); dot(); dot();
   break;

  case 'C':
   printf("-.-. "); pause(); dash(); dot(); dash(); dot();
   break;

  case 'D':
   printf("-.. "); pause(); dash(); dot(); dot(); 
   break;

  case 'E':
   printf(". "); pause(); dot();
   break;

  case 'F':
   printf("..-. "); pause(); dot(); dot(); dash(); dot();
   break;

  case 'G':
   printf("--. "); pause(); dash(); dash(); dot();
   break;

  case 'H':
   printf(".... "); pause(); dot(); dot(); dot(); dot();
   break;

  case 'I':
   printf(".. "); pause(); dot(); dot();
   break;

  case 'J':
   printf(".--- "); pause(); dot(); dash(); dash(); dash();
   break;

  case 'K':
   printf("-.- "); pause(); dash(); dot(); dash();
   break;

  case 'L':
   printf(".-.. "); pause(); dot(); dash(); dot(); dot();
   break;

  case 'M':
   printf("-- "); pause(); dash(); dash(); 
   break;

  case 'N':
   printf("-. "); pause(); dash(); dot();
   break;

  case 'O':
   printf("--- "); pause(); dash(); dash(); dash();
   break;

  case 'P':
   printf(".--. "); pause(); dot(); dash(); dash(); dot();
   break;

  case 'Q':
   printf("--.- "); pause(); dash(); dash(); dot(); dash();
   break;

  case 'R':
   printf(".-. "); pause(); dot(); dash(); dot();
   break;

  case 'S':
   printf("... "); pause(); dot(); dot(); dot();
   break;

  case 'T':
   printf("- "); pause(); dash();
   break;

  case 'U':
   printf("..- "); pause(); dot(); dot(); dash();
   break;

  case 'V':
   printf("...- "); pause(); dot(); dot(); dot(); dash();
   break;

  case 'W':
   printf(".-- "); pause(); dot(); dash(); dash();
   break;

  case 'X':
   printf("-..- "); pause(); dash(); dot(); dot(); dash();
   break;

  case 'Y':
   printf("-.-- "); pause(); dash(); dot(); dash(); dash();
   break;

  case 'Z':
   printf("--.. "); pause(); dash(); dash(); dot(); dot();
   break;

  case '0':
   printf("----- "); pause(); dash(); dash(); dash(); dash(); dash();
   break;

  case '1':
   printf(".---- "); pause(); dot(); dash(); dash(); dash(); dash();
   break;

  case '2':
   printf("..--- "); pause(); dot(); dot(); dash(); dash(); dash();
   break;

  case '3':
   printf("...-- "); pause(); dot(); dot(); dot(); dash(); dash();
   break;

  case '4':
   printf("....- "); pause(); dot(); dot(); dot(); dot(); dash();
   break;

  case '5':
   printf("..... "); pause(); dot(); dot(); dot(); dot(); dot();
   break;

  case '6':
   printf("-.... "); pause(); dash(); dot(); dot(); dot(); dot();
   break;

  case '7':
   printf("--... "); pause(); dash(); dash(); dot(); dot(); dot();
   break;

  case '8':
   printf("---.. "); pause(); dash(); dash(); dash(); dot(); dot();
   break;

  case '9':
   printf("----. "); pause(); dash(); dash(); dash(); dash(); dot();
   break;

  case ' ':
   printf("  "); pause(); pause(); pause(); pause();
   break;

  case '.':
   printf(".-.-.-"); pause(); dot(); dash(); dot(); dash(); dot(); dash();
   break;

  case ',':
   printf("--..--"); pause(); dash(); dash(); dot(); dot(); dash(); dash();
   break;

  case '?':
   printf("..--.."); pause(); dot(); dot(); dash(); dash(); dot(); dot();
   break;

  case '!':
   printf("..--."); pause(); dot(); dot(); dash(); dash(); dot();
   break;

  case ':':
   printf("---..."); pause(); dash(); dash(); dash(); dot(); dot(); dot();
   break;

   
//...

   default:
    printf("");
 }
}








int main()
{
    char str[MAX_SIZE];
    int i;

    /* Input string from user */
    printf("Enter your text : ");
    scanf("%[^\n]%*c", str);

    for(i=0; str[i]!='\0'; i++)
    {
	    str[i] = conv_to_up(str[i]);
            convert(str[i]);
    }
    printf("\n");
    return 0;
}
